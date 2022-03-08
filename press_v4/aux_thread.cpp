#include "pressapp.h"
#include "aux_thread.h"

aux_thread::aux_thread(PressApp *master, QWidget *parent) :
    QWidget(parent)
{
    pressApp = master;
    serial_port_setup();

    sender_timer = new QTimer(this);
    sender_timer->setInterval(18);

    connect(sender_timer, SIGNAL(timeout()), this,SLOT(fuzpid_thread_handler()));

//#ifdef CONFIG_ARM     // OPEN
//    QTimer::singleShot(10000,sender_timer,SLOT(start()));
//#else
//    QTimer::singleShot(5000,sender_timer,SLOT(start()));
//#endif
    hard_stop = 0;
    breaking_case = 0;
    max_load_value = 0;
    max_load_value_for_peak_detection = 0;
    test_finished = false;
    test_label_status = false;
    to_gui.hit = false;
    to_gui.test_finished = false;
    command_silencer = false;
    load_value = 0;
    ch1_value = 0;
    ch2_value = 0;
    ch3_value = 0;
    ch4_value = 0;
    max_load_error = true;
    run_pid = false;
    dac_value = 0;
    relay_auto_man = RELAY_ON;
    relay_start_stop = RELAY_OFF;
    current_pace_rate = 0;
    PID_first_in = true;
    communication_established = false;
}
void aux_thread::fuzpid_thread_handler(void){
    static bool switcher = true;
    static u8 counter = 0;
    static u8 bound = 5;

    if(command_silencer == false){
        counter++;
        if(counter > bound){
            counter = 0;
            if(switcher){
                always_send();
                bound = 2;
            }
            else{
                read_parameters();
                bound = 0;
            }
            switcher = !switcher;
        }
    }
}
void aux_thread::read_parameters(void){
    QByteArray data_array;
    data_array = serial->readAll();
    static u32 missed = 0;
    static u32 unread = 0;
    static u32 read = 0;
    static QTime pace_timer;
    u32 divide = 32;
    u32 fcrc;
    u8 crc_low,crc_high;
    s32 value[4];
    float calibrated[4];
    static float old_load = 0;
    static bool plot_graphics = false;
    float *channel_floats[4];
    u8 aux_char[4];
    double usart_pace_rate;

#ifdef MATLAB_RECORDINGS
    static u32 counter = 0;

    QTextStream time_log(&dcMotorPc->matlab_time_log);
    QTextStream raw_log(&dcMotorPc->matlab_raw_log);
    QTextStream data_log(&dcMotorPc->matlab_data_log);
    QTextStream pace_log(&dcMotorPc->matlab_pace_rate_log);
#endif
    qDebug() << "read parameters";

    if(read_data_order(data_array,"ANS",0,2)){
        fcrc = crc_chk((u8*)data_array.data(),35);
        crc_high = (fcrc)%256;
        crc_low = (fcrc)/256;
        if((crc_high == (u8)data_array[35])&&(crc_low == (u8)data_array[36])){
            communication_established = true;
            read++;
            for (u8 i = 0; i < 4; i++){
                value[i] = 256*256*(u8)data_array[3+8*i] + 256*(u8)data_array[4+8*i] + (u8)data_array[5+8*i];
                value[i] = value[i]/divide;
                to_gui.raw[i] = value[i];
                //channel_floats[i] = (float *)&data_array.data()[6+8*i];
                aux_char[0] = data_array[6+8*i];
                aux_char[1] = data_array[7+8*i];
                aux_char[2] = data_array[8+8*i];
                aux_char[3] = data_array[9+8*i];
                channel_floats[i] = (float *)&aux_char;

                calibrated[i] = *channel_floats[i];
                to_gui.calibrated[i] = calibrated[i];
                to_gui.gain[i] = ((u8)data_array[10+8*i] & 0x0F);
                to_gui.raw_sign[i] = ((((u8)data_array[10+8*i]) & 0x10) == 0x10) ? '+' : '-';

                //qDebug() << QString("channel_floats%1").arg(i) << *channel_floats[i];
            }
            pressApp->current_channel_data = value[pressApp->current_cal_channel];

            if(pressApp->current_frame == FRAME1){
                to_gui.calibrated[0] = calibrated[0];
                load_value = (float)calibrated[0];
            }
            else{
                to_gui.calibrated[0] = calibrated[1];
                load_value = (float)calibrated[1];
            }

            ch1_value = (float)calibrated[0];
            ch2_value = (float)calibrated[1];
            ch3_value = (float)calibrated[2];
            ch4_value = (float)calibrated[3];

            filtered_load_value = IIR_Filter_double_load(&load_value);

            usart_pace_rate = ((double)1000 * (load_value - old_load)) / (double)pace_timer.elapsed();
            pace_timer.restart();
            old_load = load_value;

            if(hard_stop){
                hard_stop = false;
                breaking_case = 0;
                max_load_value = 0;
                max_load_value_for_peak_detection = 0;
                test_finished = true;
            }
            current_pace_rate = IIR_Filter_double_pace_rate(&usart_pace_rate);
            //current_pace_rate = dcMotorPc->butterworth_filter(usart_pace_rate);

#ifdef MATLAB_RECORDINGS
            time_log << counter++ << "\n";
            raw_log << value[0] << "\n";
            data_log << filtered_load_value << "\n";
            pace_log << load_value << "\n";
#endif
            if(pressApp->test_status == TEST_RUNNING && relay_start_stop == RELAY_ON)
                    dac_value = pressApp->dac_voltage_to_raw((double)0.1 * pressApp->ui->spinBox_start_speed_percentage->value());
            if((pressApp->test_status == TEST_RUNNING)||(pressApp->test_status == TEST_PAUSED)){
                if(plot_graphics == false){
                    if(load_value >= pressApp->ui->doubleSpinBox_zero_suppression->value()){
                        run_pid = true;
                        pressApp->_time->start();
                        plot_graphics = true;
                    }
                }
                if(filtered_load_value > max_load_value){
                    max_load_value = filtered_load_value;
                }

                if(load_value > max_load_value_for_peak_detection){
                    max_load_value_for_peak_detection = load_value;
                }
                peak_load = max_load_value_for_peak_detection;

                if(pressApp->step_response_status == false){
                    switch (breaking_case) {
                    case 0:
                        pressApp->start_date = QDate::currentDate().toString("dd.MM.yyyy");
                        pressApp->start_time = QTime::currentTime().toString();
                        breaking_case++;
                        break;
                    case 1:
                        if(load_value > 0){
                            if(load_value >= pressApp->ui->doubleSpinBox_load_treshold->value()){ //load treshold
                                breaking_case++;
                                test_label_status = true;
                            }
                        }
                        break;
                    case 2:
                        if(filtered_load_value <= (max_load_value - (max_load_value * pressApp->ui->spinBox_break_percentage->value())/100)){ //break percentage
                            test_finished = true;
                        }
                        break;
                    }

                    if(pressApp->test_status == TEST_RUNNING){
                        if(run_pid) dac_value = discrete_PID_dac();
                    }
                    else{
                        dac_value = 0;
                    }
                }
                else{
                    step_response();
                }
            }
            else{   // if test_status is STOPPED
                breaking_case = 0;
                max_load_value = 0;
                max_load_value_for_peak_detection = 0;
            }

            if(test_finished){
                test_finished = false;
                run_pid = false;
                dac_value = 0;
                plot_graphics = false;
                relay_start_stop = RELAY_OFF;
                PID_first_in = true;

                if((pressApp->test_status == TEST_RUNNING)||(pressApp->test_status == TEST_PAUSED)){
                    pressApp->test_status = TEST_JUST_FINISHED;
                }
                else{
                    pressApp->test_status = TEST_STOPPED;
                }
                to_gui.test_finished = true;
            }
            to_gui.hit = true;
        }
        else{
            missed++;
        }
    }
    else{
        unread++;
    }

//    static QTime my_elapsed;
//    qDebug() << "elapsed" << my_elapsed.elapsed();
//    qDebug() << read << "read";
//    qDebug() << unread << "unread";
//    qDebug() << missed << "missed";
//    my_elapsed.restart();

}
u32 PressApp::crc_chk(u8* data, u8 length){
    int j;
    u32 reg_crc=0xFFFF;

    while( length-- ) {
        reg_crc^= *data++;
        for (j=0; j<8; j++ ) {
            if( reg_crc & 0x01 ) {
                reg_crc = (reg_crc >> 1)^0xA001;
            }
            else {
                reg_crc = (reg_crc>>1);
            }
        }
    }
    return reg_crc;
}
u32 aux_thread::crc_chk(u8* data, u8 length) {
    int j;
    u32 reg_crc=0xFFFF;

    while( length-- ) {
        reg_crc^= *data++;
        for (j=0; j<8; j++ ) {
            if( reg_crc & 0x01 ) {
                reg_crc = (reg_crc >> 1)^0xA001;
            }
            else {
                reg_crc = (reg_crc>>1);
            }
        }
    }
    return reg_crc;
}
void PressApp::EOL(char *base_array, u8 i){
    base_array[i] 	= 0x0D;
    base_array[i+1] = 0x0A;
}
void aux_thread::EOL(char *base_array, u8 i){
    base_array[i] 	= 0x0D;
    base_array[i+1] = 0x0A;
}
void PressApp::send_data_order(char *base_array, const char *array, u8 first_index, u8 last_index){
    u8 i;

    for(i = first_index; i < last_index+1; i++){
        base_array[i] = array[i];
    }
}
void aux_thread::send_data_order(char *base_array, const char *array, u8 first_index, u8 last_index){
    u8 i;

    for(i = first_index; i < last_index+1; i++){
        base_array[i] = array[i];
    }
}
void PressApp::command_sending_protection(void){
    static u8 tmp = 0;

    switch(tmp){
    case 0:
        auxthread->read_parameters();
        tmp++;
        break;
    case 1:
        if(usart_signalmapper_no < 44){
            send_gain(usart_signalmapper_no);
        }
        else if(usart_signalmapper_no < 48){
            tare_channel(usart_signalmapper_no - 44);
        }
        else if(usart_signalmapper_no == 48){       // sila
            send_calibration_values();
        }
        tmp++;
        break;
    case 2:
        auxthread->read_parameters();
        tmp++;
        break;
    case 3:
        command_send_protection_wait_timer->stop();
        auxthread->command_silencer = false;
        tmp = 0;
        break;
    }
}
void aux_thread::always_send(void){
    QByteArray data;
    data.resize(10);

    send_data_order(data.data(),"CONV",0,3);
    data[4] = relay_auto_man;
    data[5] = relay_start_stop;

    data[6] = (((u32)dac_value) / 256) % 256;
    data[7] = (((u32)dac_value) / 1) % 256;

    EOL(data.data(),8);

    serial->write(data);
    //qDebug() << "CONV is sent" << QString("Serial port status is %1").arg(serial->isOpen());
}
u8 aux_thread::read_data_order(QByteArray base_array, const char *array, u8 first_index, u8 last_index){
    u8 i;
    u8 condition;

    condition = 1;
    for(i = first_index; i < last_index+1; i++){
        condition = ((condition == 1)&&(base_array[i] == array[i])) ? 1 : 0;
    }
    return condition;
}
void aux_thread::serial_port_setup(void){

#ifdef CONFIG_x86
    serial = new QSerialPort("/dev/ttyUSB0");
#else
    serial = new QSerialPort("/dev/ttymxc0");
#endif
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadWrite);

    qDebug() << QString("Serial port status is %1").arg(serial->isOpen());
}

aux_thread::~aux_thread()
{
    delete ui;
}
