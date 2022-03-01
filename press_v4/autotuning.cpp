#include "pressapp.h"

void PressApp::step_response_handle(void){
    qDebug()<<"step_response_status"<<step_response_status;
    if(_start_com && ui->pushButton_step_response){
        if(step_response_status == false && test_status==TEST_STOPPED){
            step_response_status = true;
            auxthread->step_response_first_in = true;
            ui->pushButton_startTest->clicked();    // sila
            ui->pushButton_step_response->setText("Autotuning Durdur");
//            test_status = TEST_RUNNING;           // sila
//            _time->start();
//            PLOT_first_in = true;

        }
        else{
            //reset_plot();
//            if((test_status == TEST_RUNNING)||(test_status == TEST_PAUSED)){
//                auxthread->test_finished = true;
//            }
//            _time->stop();
        // sila :
            ui->pushButton_stopTest->clicked();
            ui->pushButton_refreshTest->clicked();
            step_response_status = false;
            ui->pushButton_step_response->setText("Autotuning Başla");
            auxthread->relay_start_stop = RELAY_OFF;
            record_results(real_time.test_no);    // TODO : autotune kaydetsin mi?
            ui->toolBox_app->setEnabled(1);
            ui->wdg_ReadWrite->setEnabled(1);
            // burda deney sonlanma sinyalini almıyor olablir !*
        }
    }
}
void aux_thread::step_response(void){
    static u8 step_tmp = 0;
    static QTime step_timer;
    static double first_step_values[5] = {0};
    static double last_step_values[17] = {0};
    static double average_first_step = 0;
    static double average_last_step = 0;
    static int meta_count = 0;
    static double meta_val[400] = {0};
    static int time_val[400] = {0};

    double y1 = 0;
    double y2 = 0;
    int x1 = 0;
    int x2 = 0;
    double x_dead = 0;
    double dead_time = 0;
    double slope_a = 0;
    double delta_p = 0;
    double a_star = 0;
    double K_halt = 0;
    double T_halt = 0;
    u8 checker;

    if(step_response_first_in){
        step_response_first_in = false;

        step_tmp = 0;
        average_first_step = 0;
        average_last_step = 0;
        meta_count = 0;
        for(u8 j = 0; j < 5; j++){
            first_step_values[j] = 0;
        }
        for(u8 j = 0; j < 17; j++){
            last_step_values[j] = 0;
        }
        for(u32 j = 0; j < 400; j++){
            meta_val[j] = 0;
            time_val[j] = 0;
        }
    }

    switch (step_tmp) {
    case 0:
        relay_start_stop = RELAY_ON;
//        dac_value = pressApp->dac_voltage_to_raw((double)0.1 * pressApp->ui->spinBox_start_speed_percentage->value());    // OPEN
        step_tmp++;
        break;
    case 1:
        if(load_value >= pressApp->ui->doubleSpinBox_zero_suppression->value()){
            dac_value = 0;
            step_tmp++;
        }
        break;
    case 2:
        dac_value = pressApp->dac_voltage_to_raw((double)0.1 * pressApp->ui->spinBox_autotuning_first_speed->value());
        step_tmp++;
        break;
    case 3:
        pressApp->channel[1].max_value_x = 0;
        pressApp->channel[1].min_value_x = 0xFFFFFF;
        pressApp->channel[1].max_value_y = 0;
        pressApp->channel[1].min_value_y = 0xFFFFFF;
        pressApp->channel[1].counter = 0;
        for(u32 j = 0; j < 1200; j++){
            pressApp->channel[1].xval[j] = 0;
            pressApp->channel[1].yval[j] = 0;
        }
        step_tmp++;
        break;
    case 4:
        step_timer.restart();
        step_tmp++;
        meta_count = 0;
        break;
    case 5:
        for(u8 i = 0; i < 4 ; i++){
            first_step_values[i] = first_step_values[i+1];
        }
        first_step_values[4] = current_pace_rate;

        if(step_timer.elapsed() >= pressApp->ui->spinBox_step_transition_time->value()*1000){
            dac_value = pressApp->dac_voltage_to_raw((double)0.1 * pressApp->ui->spinBox_autotuning_second_speed->value());

            step_tmp++;
            average_first_step = (first_step_values[0] + first_step_values[1] +
                    first_step_values[2] + first_step_values[3] + first_step_values[4]) / 5;
            time_val[meta_count] = step_timer.elapsed();
            meta_val[meta_count++] = average_first_step;
        }
        break;
    case 6:
        average_last_step = current_pace_rate;
        for(u8 i = 0; i < 16 ; i++){
            last_step_values[i] = last_step_values[i+1];
            average_last_step += last_step_values[i];
        }
        last_step_values[16] = current_pace_rate;

        average_last_step = average_last_step / 17;

        if(meta_count < 399){
            time_val[meta_count] = step_timer.elapsed();
            meta_val[meta_count++] = current_pace_rate;
        }
        checker = 0;
        for(u8 i = 0; i < 17 ; i++){
            if((qFabs(average_last_step - last_step_values[i])) <= 0.01*average_last_step){
                checker++;
            }
        }
        if(checker == 17){
            step_tmp++;
        }
        break;
    case 7:
        y1 = 0.632 * (meta_val[meta_count-1] - meta_val[0]) + meta_val[0]; //y1 tespit edildi
        y2 = 0.283 * (meta_val[meta_count-1] - meta_val[0]) + meta_val[0]; //y2 tespit edildi
        x1 = 0;
        x2 = 0;

        for (int i = 0; i < meta_count; i++){
            if(y1 >= meta_val[i]){
                x1 = i; //x1 tespit edildi, y1'in bulunduğu nokta
            }
            if(y2 >= meta_val[i]){
                x2 = i; //x2 tespit edildi, y2'nin bulunduğu nokta
            }
        }

        x_dead = ((meta_val[0] - y1)*(time_val[x1] - time_val[x2]))/(y1 -y2) + time_val[x1];
        dead_time = (x_dead - time_val[0]);

        //qDebug() << "estimated dead_time :" << (time_val[x1] - 1.5*(time_val[x1] - time_val[x2]));
        //dead_time = ((time_val[x1]-time_val[0]) - 1.5*(time_val[x1] - time_val[x2]));

        slope_a = (y2 - y1)/(time_val[x2] - time_val[x1]);
        //delta_p = (pressApp->ui->doubleSpinBox_step_second_speed->value() - pressApp->ui->doubleSpinBox_step_first_speed->value());
        delta_p = pressApp->dac_voltage_to_raw((double)0.1 * pressApp->ui->spinBox_autotuning_second_speed->value()) -
                pressApp->dac_voltage_to_raw((double)0.1 * pressApp->ui->spinBox_autotuning_first_speed->value());
        //delta_p = ((double)100.0*delta_p)/((double)65535);
        a_star = slope_a / delta_p;

        K_halt = (meta_val[meta_count-1] - meta_val[0]) / delta_p;
        T_halt = time_val[x1] - time_val[x2];

#ifdef CONFIG_x86
        qDebug() << "first_value" << meta_val[0];
        qDebug() << "last_value" << meta_val[meta_count-1];
        qDebug() << "y1 = 0.632*A : " << y1;
        qDebug() << "y2 = 0.283*A : " << y2;
        qDebug() << "x1 :" << x1 << " time(x1) :" << time_val[x1];
        qDebug() << "x2 :" << x2 << " time(x2) :" << time_val[x2];
        qDebug() << "x_dead :" << x_dead;
        qDebug() << "dead_time :" << dead_time;
        qDebug() << "K_HaLT" << K_halt << "T_HALT" << T_halt;
        qDebug() << "slope_a :" << slope_a << "delta_p : " << delta_p << "a_star : " << a_star;

        qDebug() << "**************************************************************";
        qDebug() << "Ziegler - Nichols Closed Loop";
        qDebug() << "**************************************************************";
        qDebug() << "Kc : " << ((1.2*T_halt) / (K_halt*dead_time));
        qDebug() << "Ki : " << ((1.2*T_halt) / (K_halt*dead_time)) / (2*dead_time);
        qDebug() << "Kd : " << ((1.2*T_halt) / (K_halt*dead_time)) * (0.5*dead_time);
        qDebug() << "**************************************************************";
        qDebug() << "Cohen Coon";
        qDebug() << "**************************************************************";
        qDebug() << "Kc : " << ((T_halt/(K_halt*dead_time))*(dead_time/(4*T_halt) + 4/3));
        qDebug() << "Ki : " << ((T_halt/(K_halt*dead_time))*(dead_time/(4*T_halt) + 4/3)) / (dead_time*((32*T_halt + 6*dead_time)/(13*T_halt + 8*dead_time)));
        qDebug() << "Kd : " << ((T_halt/(K_halt*dead_time))*(dead_time/(4*T_halt) + 4/3)) * (dead_time*(4*T_halt / (2*dead_time + 11*T_halt)));
        qDebug() << "**************************************************************";
        qDebug() << "ITEA-Load";
        qDebug() << "**************************************************************";
        qDebug() << "Kc : " << ((1.357/K_halt)*(pow((dead_time/T_halt),-0.947)));
        qDebug() << "Ki : " << (((1.357/K_halt)*(pow((dead_time/T_halt),-0.947)))/((T_halt/0.842)*(pow((dead_time/T_halt),0.738))));
        qDebug() << "Kd : " << (((1.357/K_halt)*(pow((dead_time/T_halt),-0.947)))*((T_halt*0.381)*(pow((dead_time/T_halt),0.995))));
#endif
        emit cohen_coon_kp(QString::number(((T_halt/(K_halt*dead_time))*(dead_time/(4*T_halt) + 4/3)),'f',3));
        emit cohen_coon_ki(QString::number(((T_halt/(K_halt*dead_time))*(dead_time/(4*T_halt) + 4/3)) / (dead_time*((32*T_halt + 6*dead_time)/(13*T_halt + 8*dead_time))),'f',3));
        emit cohen_coon_kd(QString::number(((T_halt/(K_halt*dead_time))*(dead_time/(4*T_halt) + 4/3)) * (dead_time*(4*T_halt / (2*dead_time + 11*T_halt))),'f',3));
        emit let_step_response();
        step_tmp++;
        break;
    default:
        break;
    }
}
