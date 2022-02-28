#include "pressapp.h".h"

void PressApp::send_gain(int gain){
    QByteArray data;
    data.resize(10);

    send_data_order(data.data(),"GAIN",0,3);
    if(gain <= 10){         //load ch
        data[4] = 0x30 + (u8)(gain);
        data[5] = 0x30 ;
        parameters[current_frame].gain[0] = (u8)(gain);
    }
    else if(gain <= 21){    //ch2
        data[4] = 0x30 + (u8)(gain - 11);
        data[5] = 0x31 ;
        parameters[current_frame].gain[1] = (u8)(gain - 11);
    }
    else if(gain <= 32){    //ch3
        data[4] = 0x30 + (u8)(gain - 22);
        data[5] = 0x32 ;
        parameters[current_frame].gain[2] = (u8)(gain - 22);
    }
    else if(gain <= 43){    //ch4
        data[4] = 0x30 + (u8)(gain - 33);
        data[5] = 0x33 ;
        parameters[current_frame].gain[3] = (u8)(gain - 33);
    }

    EOL(data.data(),6);

    //auxthread->serial->write(data);  BURDA      // TODO : unexpectedly finshed : ORJ HALİ YAZ
}
void PressApp::send_gains_and_cals(void){
    static u8 tmp = 0;

    switch(tmp){
    case 0:
        send_gain(parameters[current_frame].gain[0]);    //gain_load
        tmp++;
        break;
    case 1:
        send_gain(11 + parameters[current_frame].gain[1]);    //gain_ch2
        tmp++;
        break;
    case 2:
        send_gain(22 + parameters[current_frame].gain[2]);    //gain_ch3
        tmp++;
        break;
    case 3:
        send_gain(33 + parameters[current_frame].gain[3]);    //gain_ch4
        tmp++;
        break;
    case 4:
        send_new_calibration_values(0);
        tmp++;
        break;
    case 5:
        send_new_calibration_values(1);
        tmp++;
        break;
    case 6:
        send_new_calibration_values(2);
        tmp++;
        break;
    case 7:
        send_new_calibration_values(3);
        tmp++;
        break;
    case 8:
        if(bad_calibration_file == false){
            record_results(test_no);
        }
        tmp++;
        break;
    case 9:
        tmp = 0;
        gain_cal_send_timer->stop();
        command_silencer = false;
        device_opening = false;
        break;
    }
}
void PressApp::cal_assignment(int index){

    if(cal_tab_raw_sign == '+'){
        spinBox_cal_raw_value[index-1]->setValue(current_channel_data);
    }
    else{
        if(index == 1){
            if(cal_tab_raw_sign == '-'){
                spinBox_cal_raw_value[index-1]->setValue(-current_channel_data);
            }
            else{
                spinBox_cal_raw_value[index-1]->setValue(current_channel_data);
            }
        }
        else{
            spinBox_cal_raw_value[index-1]->setValue(current_channel_data);
        }
    }
}
void PressApp::cal_channel_change(int channel){     // sila : int
    channel = ui->comboBox_channel_no->currentIndex();
    if(channel == CH_1){
        current_cal_channel = 0;
        ui->doubleSpinBox_cal_point_value_1->setDecimals(ui->spinBox_dp_load->value());
        ui->doubleSpinBox_cal_point_value_2->setDecimals(ui->spinBox_dp_load->value());
        ui->doubleSpinBox_cal_point_value_3->setDecimals(ui->spinBox_dp_load->value());
        ui->doubleSpinBox_cal_point_value_4->setDecimals(ui->spinBox_dp_load->value());
        ui->doubleSpinBox_cal_point_value_5->setDecimals(ui->spinBox_dp_load->value());
        ui->doubleSpinBox_cal_point_value_6->setDecimals(ui->spinBox_dp_load->value());
        ui->doubleSpinBox_cal_point_value_7->setDecimals(ui->spinBox_dp_load->value());
        ui->doubleSpinBox_cal_point_value_8->setDecimals(ui->spinBox_dp_load->value());
    }
    if(channel == CH_2){
        current_cal_channel = 1;
        ui->doubleSpinBox_cal_point_value_1->setDecimals(ui->spinBox_dp_ch2->value());
        ui->doubleSpinBox_cal_point_value_2->setDecimals(ui->spinBox_dp_ch2->value());
        ui->doubleSpinBox_cal_point_value_3->setDecimals(ui->spinBox_dp_ch2->value());
        ui->doubleSpinBox_cal_point_value_4->setDecimals(ui->spinBox_dp_ch2->value());
        ui->doubleSpinBox_cal_point_value_5->setDecimals(ui->spinBox_dp_ch2->value());
        ui->doubleSpinBox_cal_point_value_6->setDecimals(ui->spinBox_dp_ch2->value());
        ui->doubleSpinBox_cal_point_value_7->setDecimals(ui->spinBox_dp_ch2->value());
        ui->doubleSpinBox_cal_point_value_8->setDecimals(ui->spinBox_dp_ch2->value());
    }
    if(channel == CH_3){
        current_cal_channel = 2;
        ui->doubleSpinBox_cal_point_value_1->setDecimals(ui->spinBox_dp_ch3->value());
        ui->doubleSpinBox_cal_point_value_2->setDecimals(ui->spinBox_dp_ch3->value());
        ui->doubleSpinBox_cal_point_value_3->setDecimals(ui->spinBox_dp_ch3->value());
        ui->doubleSpinBox_cal_point_value_4->setDecimals(ui->spinBox_dp_ch3->value());
        ui->doubleSpinBox_cal_point_value_5->setDecimals(ui->spinBox_dp_ch3->value());
        ui->doubleSpinBox_cal_point_value_6->setDecimals(ui->spinBox_dp_ch3->value());
        ui->doubleSpinBox_cal_point_value_7->setDecimals(ui->spinBox_dp_ch3->value());
        ui->doubleSpinBox_cal_point_value_8->setDecimals(ui->spinBox_dp_ch3->value());
    }
    if(channel == CH_4){
        current_cal_channel = 3;
        ui->doubleSpinBox_cal_point_value_1->setDecimals(ui->spinBox_dp_ch4->value());
        ui->doubleSpinBox_cal_point_value_2->setDecimals(ui->spinBox_dp_ch4->value());
        ui->doubleSpinBox_cal_point_value_3->setDecimals(ui->spinBox_dp_ch4->value());
        ui->doubleSpinBox_cal_point_value_4->setDecimals(ui->spinBox_dp_ch4->value());
        ui->doubleSpinBox_cal_point_value_5->setDecimals(ui->spinBox_dp_ch4->value());
        ui->doubleSpinBox_cal_point_value_6->setDecimals(ui->spinBox_dp_ch4->value());
        ui->doubleSpinBox_cal_point_value_7->setDecimals(ui->spinBox_dp_ch4->value());
        ui->doubleSpinBox_cal_point_value_8->setDecimals(ui->spinBox_dp_ch4->value());
    }
    for(u8 i = 0; i < 8; i++){      // TODO : unexpectedly finished
//        spinBox_cal_raw_value[i]->setValue(parameters[current_frame].cal[current_cal_channel].real_val[i]);     // TODO : unexpectedly finished
//        doubleSpinBox_cal_point_value[i]->setValue(parameters[current_frame].cal[current_cal_channel].assigned_val[i]);
    }
    ui->comboBox_cal_point_number->setCurrentIndex(parameters[current_frame].cal[current_cal_channel].point_no - 2);

// sila :
//    ui->doubleSpinBox_cal_point_value_9->setValue(spinBox_cal_raw_value[0]->value());     // TODO : unexpectedly finished
//    ui->doubleSpinBox_cal_point_value_10->setValue(spinBox_cal_raw_value[1]->value());
//    ui->doubleSpinBox_cal_point_value_11->setValue(spinBox_cal_raw_value[2]->value());
//    ui->doubleSpinBox_cal_point_value_12->setValue(spinBox_cal_raw_value[3]->value());
//    ui->doubleSpinBox_cal_point_value_13->setValue(spinBox_cal_raw_value[4]->value());
//    ui->doubleSpinBox_cal_point_value_14->setValue(spinBox_cal_raw_value[5]->value());
//    ui->doubleSpinBox_cal_point_value_15->setValue(spinBox_cal_raw_value[6]->value());
//    ui->doubleSpinBox_cal_point_value_16->setValue(spinBox_cal_raw_value[7]->value());

#ifdef CONFIG_x86
    qDebug() << "current cal channel is" << current_cal_channel;pushButton_save_all_cal_data
#endif
}
void PressApp::send_calibration_values(void){
    QByteArray data;
    data.resize(78);
    u32 fcrc;
    u8 crc_low,crc_high;
    u32 raw_value_sender;
    u8 *calibrated;
    float calibrated_float;

    send_data_order(data.data(),"CALSEND",0,6);
    data[7] = current_cal_channel;
    data[8] = 2 + ui->comboBox_cal_point_number->currentIndex();
    data[9] = (ui->doubleSpinBox_cal_point_value_10->value() < 0) ? '-' : '+';
    for(u8 i = 0; i < 8; i++){
        raw_value_sender = abs(spinBox_cal_raw_value[i]->value());

        data[10+i*4] = (u8)(32*raw_value_sender/(256*256*256)) %256; //because raw data are divided by 32
        data[11+i*4] = (u8)(32*raw_value_sender/(256*256))    %256;
        data[12+i*4] = (u8)(32*raw_value_sender/(256))        %256;
        data[13+i*4] = (u8)(32*raw_value_sender)              %256;
        parameters[current_frame].cal[current_cal_channel].real_val[i] = spinBox_cal_raw_value[i]->value();
    }
    for(u8 i = 0; i < 8; i++){
        calibrated_float = doubleSpinBox_cal_point_value[i]->value();
        calibrated = (u8 *)&calibrated_float;
        data[42+i*4] = calibrated[0];
        data[43+i*4] = calibrated[1];
        data[44+i*4] = calibrated[2];
        data[45+i*4] = calibrated[3];
//        data[42+i*4] = (u8)	((u32)(POWER_of_10(decimal_point)*doubleSpinBox_cal_point_value[i]->value())/(256*256*256)	%256);
//        data[43+i*4] = (u8)	((u32)(POWER_of_10(decimal_point)*doubleSpinBox_cal_point_value[i]->value())/(256*256)		%256);
//        data[44+i*4] = (u8)	((u32)(POWER_of_10(decimal_point)*doubleSpinBox_cal_point_value[i]->value())/(256)			%256);
//        data[45+i*4] = (u8)	((u32)(POWER_of_10(decimal_point)*doubleSpinBox_cal_point_value[i]->value())				%256);
        parameters[current_frame].cal[current_cal_channel].assigned_val[i] = doubleSpinBox_cal_point_value[i]->value();
    }
    parameters[current_frame].cal[current_cal_channel].point_no = ui->comboBox_cal_point_number->currentIndex() + 2;

    fcrc = crc_chk((u8*)data.data(),74);
    crc_high = (fcrc)%256;
    crc_low = (fcrc)/256;

    data[74] = crc_high;
    data[75] = crc_low;
    EOL(data.data(),76);

    auxthread->serial->write(data);
#ifdef CONFIG_x86
    qDebug(__FUNCTION__);
#endif
    record_results(test_no);
}
void PressApp::send_new_calibration_values(u8 chan){
    QByteArray data;
    data.resize(78);
    u32 fcrc;
    u8 crc_low,crc_high;
    u32 raw_value_sender;
    u8 *calibrated;

    send_data_order(data.data(),"CALSEND",0,6);
    data[7] = chan;
    data[8] = parameters[current_frame].cal[chan].point_no;
    if(parameters[current_frame].cal[chan].real_val[0] < 0){
        data[9] = '-';
    }
    else{
        data[9] = '+';
    }
    for(u8 i = 0; i < 8; i++){
        raw_value_sender = abs(parameters[current_frame].cal[chan].real_val[i]);

        data[10+i*4] = (u8)(32*raw_value_sender/(256*256*256)) %256; //because raw data are divided by 32
        data[11+i*4] = (u8)(32*raw_value_sender/(256*256))    %256;
        data[12+i*4] = (u8)(32*raw_value_sender/(256))        %256;
        data[13+i*4] = (u8)(32*raw_value_sender)              %256;
    }
    for(u8 i = 0; i < 8; i++){
        calibrated = (u8 *)&parameters[current_frame].cal[chan].assigned_val[i];
        data[42+i*4] = calibrated[0];
        data[43+i*4] = calibrated[1];
        data[44+i*4] = calibrated[2];
        data[45+i*4] = calibrated[3];
//        data[42+i*4] = (u8)	((u32)(POWER_of_10(decimal_point)*parameters[current_frame].cal[chan].assigned_val[i])/(256*256*256)	%256);
//        data[43+i*4] = (u8)	((u32)(POWER_of_10(decimal_point)*parameters[current_frame].cal[chan].assigned_val[i])/(256*256)		%256);
//        data[44+i*4] = (u8)	((u32)(POWER_of_10(decimal_point)*parameters[current_frame].cal[chan].assigned_val[i])/(256)			%256);
//        data[45+i*4] = (u8)	((u32)(POWER_of_10(decimal_point)*parameters[current_frame].cal[chan].assigned_val[i])%256);
    }

    fcrc = crc_chk((u8*)data.data(),74);
    crc_high = (fcrc)%256;
    crc_low = (fcrc)/256;

    data[74] = crc_high;
    data[75] = crc_low;
    EOL(data.data(),76);

    auxthread->serial->write(data);

}
