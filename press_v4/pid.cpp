#include "pressapp.h"

void PressApp::save_pid_values_to_all(){
    for(u8 i = 0; i < 13; i++){
        parameters[current_frame].pid[i].Kp = ui->doubleSpinBox_kp_pace->value();
        parameters[current_frame].pid[i].Ki = ui->doubleSpinBox_ki_pace->value();
        parameters[current_frame].pid[i].Kd = ui->doubleSpinBox_kd_pace->value();
    }
    data_changed = true;
}
void PressApp::save_pid_values(){
    parameters[current_frame].pid[ui->comboBox_pid->currentIndex()].Kp = ui->doubleSpinBox_kp_pace->value();
    parameters[current_frame].pid[ui->comboBox_pid->currentIndex()].Ki = ui->doubleSpinBox_ki_pace->value();
    parameters[current_frame].pid[ui->comboBox_pid->currentIndex()].Kd = ui->doubleSpinBox_kd_pace->value();
    data_changed = true;
}
void PressApp::pid_combobox_handle(int val){
    ui->doubleSpinBox_kp_pace->setValue(parameters[current_frame].pid[val].Kp);
    ui->doubleSpinBox_ki_pace->setValue(parameters[current_frame].pid[val].Ki);
    ui->doubleSpinBox_kd_pace->setValue(parameters[current_frame].pid[val].Kd);
}
double aux_thread::discrete_PID_dac(){
    static double last_error[3] = {0};
    static double output = 0;

    float error = 0;
    double a,b,c;
    double Ts = pid_delta_t_dac.elapsed();
    static double kp,ki,kd;
    //static double sse = 0;

    if(PID_first_in){
        PID_first_in = false;
        output = pressApp->dac_voltage_to_raw((double)0.1 * pressApp->ui->spinBox_start_speed_percentage->value());
        last_error[0] = 0;
        last_error[1] = 0;
        last_error[2] = 0;

        switch (pressApp->parameters[pressApp->current_frame].test_type) {
        case COMPRESSION:
            kp = pressApp->parameters[pressApp->current_frame].pid[pressApp->parameters[pressApp->current_frame].speciment_type_index_compression].Kp;
            ki = pressApp->parameters[pressApp->current_frame].pid[pressApp->parameters[pressApp->current_frame].speciment_type_index_compression].Ki;
            kd = pressApp->parameters[pressApp->current_frame].pid[pressApp->parameters[pressApp->current_frame].speciment_type_index_compression].Kd;
            break;
        case FLEXURAL:
            kp = pressApp->parameters[pressApp->current_frame].pid[4 + pressApp->parameters[pressApp->current_frame].speciment_type_index_flexural].Kp;
            ki = pressApp->parameters[pressApp->current_frame].pid[4 + pressApp->parameters[pressApp->current_frame].speciment_type_index_flexural].Ki;
            kd = pressApp->parameters[pressApp->current_frame].pid[4 + pressApp->parameters[pressApp->current_frame].speciment_type_index_flexural].Kd;
            break;
        case SPLIT_TENSILE:
            kp = pressApp->parameters[pressApp->current_frame].pid[9 + pressApp->parameters[pressApp->current_frame].speciment_type_index_split_tensile].Kp;
            ki = pressApp->parameters[pressApp->current_frame].pid[9 + pressApp->parameters[pressApp->current_frame].speciment_type_index_split_tensile].Ki;
            kd = pressApp->parameters[pressApp->current_frame].pid[9 + pressApp->parameters[pressApp->current_frame].speciment_type_index_split_tensile].Kd;
            break;
        default:
            break;
        }
    }
    else{
        error = pressApp->ui->doubleSpinBox_pace_rate->value() - current_pace_rate;

        last_error[2] = last_error[1];
        last_error[1] = last_error[0];
        last_error[0] = error;
//        sse +=(error*error);
//        qDebug() << "sse : " << sse;

        a = kp + kd/Ts; //bu daha iyi, birkaç kaynakta da bu yazıyor zaten
        b = -kp + (ki*Ts) - (2*kd)/Ts;
        c = kd/Ts;

        output = output + (a*last_error[0] + b*last_error[1] + c*last_error[2]);

        if(output > 65535) output = 65535; // TODO: change this with a max speed limit
        if(output < 0) output = 0;
    }
    pid_delta_t_dac.restart();
    return output;
}
