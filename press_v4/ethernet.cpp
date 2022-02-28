#include "pressapp.h"
#include "ui_pressapp.h"
#include <QProcess>
#include <QtNetwork>

void PressApp::start_comm(void)
{
    qDebug(__FUNCTION__);

    remote->set("device_settings_liya.stream.enable", "1");
}
void PressApp::end_comm(void)
{
    qDebug(__FUNCTION__);

    remote->set("device_settings_liya.stream.enable", "0");
}
void PressApp::set_test_status()
{
    static u8 tmp = 0;

    switch(tmp ){
    case 1:
        remote->set("main.tare.ch2",QString::number(1));
        tmp++;
        break;
    case 2:
        remote->set("main.tare.ch3",QString::number(1));
        tmp++;
        break;
    case 3:
        remote->set("main.tare.ch4",QString::number(1));
        tmp++;
        break;
   }
}
void PressApp::periodic_response_handler(QByteArray datagram)
{
    eth_timer->start();
    union _my_resp{
        int _integer;
        float _float;
    };
    _my_resp my_resp;
    int start_stream = 0;
    start_stream = (unsigned char)datagram[0] + ((unsigned char)datagram[1] << 8) + ((unsigned char)datagram[2] << 16) + ((unsigned char)datagram[3] << 24);

    if(start_stream == 0x11223344){
        _start_com = true;
        ui->label_connection->setText("Bağlantı kuruldu");
        ui->label_connection->setStyleSheet({"border: none; color: white; background-color: rgb(0,130,0);"});
//        ui->label_connection->setTextFormat(Qt::RichText);
//        ui->label_connection->setText("<img src= :/icons/green_ball.png>""   Bağlantı kuruldu!");

        real_time.test_no = (unsigned char)datagram[4] + ((unsigned char)datagram[5] << 8) + ((unsigned char)datagram[6] << 16) + ((unsigned char)datagram[7] << 24);

        statu = (unsigned char)datagram[8] + ((unsigned char)datagram[9] << 8);
        if(statu == 0){
            real_time.status = "Deney Durumu  : ";
            statu_device = 0;
        }
        else if(statu == 1){
            real_time.status = "Deney Durumu  : BAŞLADI";
            statu_device = 1;
            }
        else if(statu == 2){
            real_time.status = "Deney Durumu  : DURAKLADI";
            statu_device = 2;
        }
        else if(statu == 3){
            real_time.status = "Deney Durumu  : SONLANDI";
            statu_device = 3;
        }
        my_resp._integer = ((unsigned char)datagram[10] + ((unsigned char)datagram[11] << 8) + ((unsigned char)datagram[12] << 16) + ((unsigned char)datagram[13] << 24));
        real_time.area = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[15] + ((unsigned char)datagram[16] << 8) + ((unsigned char)datagram[17] << 16) + ((unsigned char)datagram[18] << 24));
        real_time.load = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[20] + ((unsigned char)datagram[21] << 8) + ((unsigned char)datagram[22] << 16) + ((unsigned char)datagram[23] << 24));
        real_time.ch2 = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[25] + ((unsigned char)datagram[26] << 8) + ((unsigned char)datagram[27] << 16) + ((unsigned char)datagram[28] << 24));
        real_time.ch3 = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[30] + ((unsigned char)datagram[31] << 8) + ((unsigned char)datagram[32] << 16) + ((unsigned char)datagram[33] << 24));
        real_time.ch4 = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[35] + ((unsigned char)datagram[36] << 8) + ((unsigned char)datagram[37] << 16) + ((unsigned char)datagram[38] << 24));
        real_time.stress = my_resp._float;

        ui->label_test_status->setText(real_time.status);
        ui->label_load->setText(QString("Yük : %1%2").arg(real_time.load).arg(load_unit));// + QString::number(real_time.load,'f',3) + QString(" %1").arg(load_unit));
        ui->spinBox_load_invisible->setValue(real_time.load);
        ui->label_stress->setText("Gerilme : " + QString::number(real_time.stress,'f',3) + QString(" %1").arg(stress_unit));

    }
    else{
        ui->label_connection->setText("Bağlantı yok");
        ui->label_connection->setStyleSheet({"border: none; color: white; background-color: rgb(230,0,0);;"});

        ui->label_calculated_area->setText("Alan : " + QString::number(real_time.area,'f',3) + QString(" %1").arg(length_unit) + "2");
        ui->label_current_test_no_2->setText("Deney No : " + QString::number(real_time.test_no,10));

        QString str = datagram;
        QString first_section = str.section(":",0,0);
        QString second_section = str.section(":",1,1);
        QString third_section = str.section(":",2,2);

        if(first_section == "get"){
            if(second_section == "param.pace_rate"){
                ui->doubleSpinBox_pace_rate->setValue(third_section.toDouble());
                ui->label_pace_rate->setText("Yükleme Hızı : " + QString::number(third_section.toDouble(),2,2) + QString("%1 %2/s").arg(ui->doubleSpinBox_pace_rate->value()).arg(load_unit));
            }
            else if(second_section == "param.start_speed")
                ui->spinBox_start_speed_percentage->setValue(third_section.toInt());
            else if(second_section == "param.max_load")
                ui->doubleSpinBox_max_load->setValue(third_section.toDouble());
            else if(second_section == "param.failure_treshold")
                ui->doubleSpinBox_load_treshold->setValue(third_section.toDouble());
            else if(second_section == "param.zero_suppression")
                ui->doubleSpinBox_zero_suppression->setValue(third_section.toDouble());
            else if(second_section == "param.break_percentage")
                ui->spinBox_break_percentage->setValue(third_section.toInt());
            else if(second_section == "param.load_tare_limit");
                //ui->spinBox_break_percentage->setValue(third_section.toInt());    // TODO
            else if(second_section == "param.dp.load")
                ui->spinBox_dp_load->setValue(third_section.toInt());
            else if(second_section == "param.dp.stress")
                ui->spinBox_dp_stress->setValue(third_section.toInt());
            else if(second_section == "param.dp.ch2")
                ui->spinBox_dp_ch2->setValue(third_section.toInt());
            else if(second_section == "param.dp.ch3")
                ui->spinBox_dp_ch3->setValue(third_section.toInt());
            else if(second_section == "param.dp.ch4")
                ui->spinBox_dp_ch4->setValue(third_section.toInt());
            else if(second_section == "param.dp.record_raw.interval")
                ui->doubleSpinBox_record_interval->setValue(third_section.toInt());
            else if(second_section == "param.record_raw.select"){
                if(third_section.toInt() == 1) ui->radioButton_record_raw_data_off->setChecked(1);         // OFF
                else if(third_section.toInt() == 0) ui->radioButton_record_raw_data_on->setChecked(1);     // ON
            }
            else if(second_section == "test.frame"){
                if(third_section.toInt() == 0) ui->radioButton_frame1->setChecked(1);
                else if(third_section.toInt() == 1) ui->radioButton_frame2->setChecked(1);
                assign_frame();
            }
            else if(second_section == "test.control"){
                if(third_section.toInt() == 0) ui->radioButton_auto->setChecked(1);
                else if(third_section.toInt() == 1) ui->radioButton_man->setChecked(1);
            }
            else if(second_section == "test.type"){
                if(third_section.toInt() == 0) ui->combo_testType->setCurrentIndex(0);          // press
                else if(third_section.toInt() == 1) ui->combo_testType->setCurrentIndex(1);     // flex
                else if(third_section.toInt() == 2) ui->combo_testType->setCurrentIndex(2);     // split
            }
            else if(second_section == "main.plot.type"){
                if(third_section.toInt() == 1) ui->comboBox_graphChoice->setCurrentIndex(0);
                else if(third_section.toInt() == 2) ui->comboBox_graphChoice->setCurrentIndex(1);
            }
            else if(second_section == "test.specimen_name"){        // TODO - paket iletilmiyo
                specimen_name;
//                if(ui->combo_testType->currentIndex() == COMPRESSION){
//                    if (third_section.toInt() == 0 )    ui->comboBox_specimen->setCurrentIndex(0);
//                    else if (third_section.toInt() == 1 )    ui->comboBox_specimen->setCurrentIndex(1);
//                    else if (third_section.toInt() == 2 )    ui->comboBox_specimen->setCurrentIndex(2);
//                }
            }
            else if(second_section == "specimen.cube.l")
                ui->doubleSpinBox_specimen_cube_w->setValue(third_section.toDouble());          // FIX w to l
            else if(second_section == "specimen.cube.w")
                ui->doubleSpinBox_specimen_cube_w->setValue(third_section.toDouble());
            else if(second_section == "specimen.cylinder.d")
                ui->doubleSpinBox_specimen_cyl_d->setValue(third_section.toDouble());
            else if(second_section == "specimen.masonry.l")
                ui->doubleSpinBox_specimen_cyl_l->setValue(third_section.toDouble());
            else if(second_section == "specimen.cylinder.l")
                ui->doubleSpinBox_specimen_masonry_unit_l->setValue(third_section.toDouble());
            else if(second_section == "specimen.cylinder.w")
                ui->doubleSpinBox_specimen_masonry_unit_w->setValue(third_section.toDouble());
            else if(second_section == "specimen.beam.l"){
                ui->doubleSpinBox_specimen_beam4_l->setValue(third_section.toDouble());
                ui->doubleSpinBox_specimen_beam3_l->setValue(third_section.toDouble());
            }
            else if(second_section == "specimen.beam.b"){
                ui->doubleSpinBox_specimen_beam4_b->setValue(third_section.toDouble());
                ui->doubleSpinBox_specimen_beam3_b->setValue(third_section.toDouble());
            }
            else if(second_section == "specimen.beam.d"){
                ui->doubleSpinBox_specimen_beam4_d->setValue(third_section.toDouble());
                ui->doubleSpinBox_specimen_beam3_d->setValue(third_section.toDouble());
            }
            else if(second_section == "specimen.beam.s")
                ui->doubleSpinBox_specimen_beam4_s->setValue(third_section.toDouble());
            else if(second_section == "specimen.kerb.a")
                ui->doubleSpinBox_specimen_kerb_a->setValue(third_section.toDouble());
            else if(second_section == "specimen.kerb.b")
                ui->doubleSpinBox_specimen_kerb_b->setValue(third_section.toDouble());
            else if(second_section == "specimen.kerb.c")
                ui->doubleSpinBox_specimen_kerb_c->setValue(third_section.toDouble());
            else if(second_section == "specimen.kerb.d")
                ui->doubleSpinBox_specimen_kerb_d->setValue(third_section.toDouble());
            else if(second_section == "specimen.kerb.l")
                ui->doubleSpinBox_specimen_kerb_l->setValue(third_section.toDouble());
            else if(second_section == "specimen.flagstone.l")
                ui->doubleSpinBox_specimen_flagstone_l->setValue(third_section.toDouble());
            else if(second_section == "specimen.flagstone.s")
                ui->doubleSpinBox_specimen_flagstone_s->setValue(third_section.toDouble());
            else if(second_section == "specimen.flagstone.b")
                ui->doubleSpinBox_specimen_flagstone_b->setValue(third_section.toDouble());
            else if(second_section == "specimen.flagstone.d")
                ui->doubleSpinBox_specimen_flagstone_d->setValue(third_section.toDouble());
            else if(second_section == "specimen.split_cube.l")
                ui->doubleSpinBox_specimen_split_cube_w->setValue(third_section.toDouble());
            else if(second_section == "specimen.split_cylinder.l")
                ui->doubleSpinBox_specimen_split_cylinder_l->setValue(third_section.toDouble());
            else if(second_section == "specimen.split_cylinder.l")
                ui->doubleSpinBox_specimen_split_cylinder_l->setValue(third_section.toDouble());
            else if(second_section == "specimen.paving_stone.l")
                ui->doubleSpinBox_specimen_split_paving_stone_l->setValue(third_section.toDouble());
            else if(second_section == "specimen.paving_stone.d")
                ui->doubleSpinBox_specimen_split_paving_stone_d->setValue(third_section.toDouble());
        }
    }
    static QTime time(QTime::currentTime());
    if(statu_device == 0){
        //qDebug () << "deney TEMİZLENDİ" << statu ;
        time.restart();
        ui->pushButton_refreshTest->hide();
        ui->pushButton_startTest->show();
        ui->pushButton_startTest->setEnabled(true);
        ui->pushButton_startTest->setStyleSheet("image: url(:/icons/media_play.png); ");
        ui->pushButton_stopTest->setDisabled(true);
        ui->pushButton_stopTest->setStyleSheet("image: url(:/icons/media_stop_dis.png); ");
        ui->pushButton_pauseTest->setDisabled(true);
        ui->pushButton_pauseTest->setStyleSheet("image: url(:/icons/media_pause_dis.png); ");
        ui->label_test_date_time_main->setText(QString("Deney Tarihi : %1").arg(start_date));
    }
    else if (statu_device == 1){
        //qDebug () << "deney BAŞLADI" << statu ;
        ui->pushButton_startTest->show();
        ui->pushButton_startTest->setDisabled(true);
        ui->pushButton_startTest->setStyleSheet("image: url(:/icons/media_play_dis.png); ");
        ui->pushButton_pauseTest->setEnabled(true);
        ui->pushButton_pauseTest->setStyleSheet({"image: url(:/icons/media_pause.png);"});
        ui->pushButton_stopTest->setEnabled(true);
        ui->pushButton_stopTest->setStyleSheet({"image: url(:/icons/media_stop.png);"});
    }
    else if (statu_device == 3){
        //qDebug () << "deney SONLANDI" << statu ;
        _time->stop();
        ui->pushButton_refreshTest->show();
        ui->pushButton_refreshTest->setEnabled(true);
        ui->pushButton_startTest->setDisabled(true);
        ui->pushButton_startTest->hide();
        ui->pushButton_stopTest->setDisabled(true);
        ui->pushButton_stopTest->setStyleSheet("image: url(:/icons/media_stop_dis.png); ");
        ui->pushButton_pauseTest->setDisabled(true);
        ui->pushButton_pauseTest->setStyleSheet("image: url(:/icons/media_pause_dis.png); ");
        ui->toolBox_app->setEnabled(1);
        ui->wdg_ReadWrite->setEnabled(1);
        ui->btn_expand->setEnabled(1);
        ui->btn_expand->setStyleSheet("image: url(:/icons/fit_to_size.png);");
        ui->pushButton_printPlot->setEnabled(1);
        ui->pushButton_printPlot->setStyleSheet("image: url(:/icons/document_chart.png);");
        ui->comboBox_graphChoice->setEnabled(1);
        finish_time = QTime::currentTime().toString();      // added to print results
        test_status = TEST_STOPPED;
        step_response_status = false;
        ui->pushButton_step_response->setText("Autotuning Başla");
        record_results(real_time.test_no);
    }
    static char current_status = statu;
    static char old_status = statu;
    current_status = statu;

    if((current_status == device_running)&&(old_status == device_stopped)) on_pushButton_startTest_clicked();
    old_status = current_status;
}
///////////// ***** GET-SET PARAM ************* /////////////
void PressApp::read_parameters_from_the_device(void)
{
    static u8 tmp = 0;

    switch(tmp){
    case 0:
       // qDebug()<<"read"<<tmp;
        remote->get("param.pace_rate");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 1:
        remote->get("param.start_speed");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 2:
        remote->get("param.max_load");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 3:
        remote->get("param.failure_treshold");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 4:
        remote->get("param.zero_suppression");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 5:
        remote->get("param.break_percentage");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 6:
        remote->get("param.load_tare_limit");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 7:
        remote->get("param.dp.load");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 8:
        remote->get("param.dp.ch2");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 9:
        remote->get("param.dp.ch3");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 10:
        remote->get("param.dp.ch4");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 11:
        remote->get("param.dp.record_raw.interval");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 12:
        remote->get("param.record_raw.select");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 13:
        remote->get("param.dp.stress");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 14:
        remote->get("test.frame");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 15:
        remote->get("test.control");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 16:
        remote->get("test.type");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp ++;
        break;
    case 17:
        remote->get("main.plot.type");
        QTimer::singleShot(10,this,SLOT(read_parameters_from_the_device()));
        tmp ++;
        break;
    case 18 :
        remote->get("test.specimen_name");
        tmp = 0;
        break;
    }
}
void PressApp::write_parameters_to_the_device(void)
{
    static u8 tmp = 0;

    switch(tmp){
    case 0:
        remote->set("param.pace_rate", QString::number(ui->doubleSpinBox_pace_rate->value()));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 1:
        remote->set("param.start_speed", QString::number(ui->spinBox_start_speed_percentage->value()));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 2:
        remote->set("param.max_load", QString::number(ui->doubleSpinBox_max_load->value()));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 3:
        remote->set("param.failure_treshold", QString::number(ui->doubleSpinBox_load_treshold->value()));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 4:
        remote->set("param.zero_suppression", QString::number(ui->doubleSpinBox_zero_suppression->value()));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 5:
        remote->set("param.break_percentage", QString::number(ui->spinBox_break_percentage->value()));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 6:
    //    remote->set("param.load_tare_limit", QString::number(ui->spinBox_load_tare_limit->value()));      // TODO
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 7:
        remote->set("param.dp.load", QString::number(ui->spinBox_dp_load->value()));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 8:
        remote->set("param.dp.ch2", QString::number(ui->spinBox_dp_ch2->value()));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 9:
        remote->set("param.dp.ch3", QString::number(ui->spinBox_dp_ch3->value()));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 10:
        remote->set("param.dp.ch4", QString::number(ui->spinBox_dp_ch4->value()));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 11:        // TODO - paket iletilmiyo
        remote->set("param.dp.record_raw.interval", QString::number(ui->doubleSpinBox_record_interval->value()));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 12:
        if(ui->radioButton_record_raw_data_on->isChecked())            // ON = 0
            remote->set("param.record_raw.select", QString::number(0));
        else if(ui->radioButton_record_raw_data_off->isChecked())      // OFF = 1
            remote->set("param.record_raw.select", QString::number(1));
        tmp++;
        break;
    case 13:
        remote->set("param.dp.stress", QString::number(ui->spinBox_dp_stress->value()));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 14:
        if(ui->radioButton_frame1->isChecked())
            remote->set("test.frame", QString::number(0));
        else if(ui->radioButton_frame2->isChecked())
            remote->set("test.frame", QString::number(1));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 15:
        if(ui->radioButton_auto->isChecked())
            remote->set("test.control", QString::number(0));
        else if(ui->radioButton_man->isChecked())
            remote->set("test.control", QString::number(1));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp++;
        break;
    case 16:
        if(ui->combo_testType->currentIndex() == COMPRESSION)
            remote->set("test.type", QString::number(0));
        else if(ui->combo_testType->currentIndex() == FLEXURAL)
            remote->set("test.type", QString::number(1));
        else if(ui->combo_testType->currentIndex() == SPLIT_TENSILE)
            remote->set("test.type", QString::number(2));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp = 0;
        break;
    case 17:        // TODO - paket iletilmiyo
        if(ui->comboBox_graphChoice->currentIndex() == 0)
            remote->set("main.plot.type", QString::number(1));
        else if(ui->comboBox_graphChoice->currentIndex() == 1)
            remote->set("main.plot.type", QString::number(2));
        QTimer::singleShot(10,this,SLOT(write_parameters_to_the_device()));
        tmp ++;
        break;
    case 18 :       // TODO - paket iletilmiyo
        if(ui->combo_testType->currentIndex() == COMPRESSION){
            if (ui->comboBox_specimen->currentIndex() == 0)    remote->set("test.specimen_name",QString::number(0));
            else if (ui->comboBox_specimen->currentIndex() == 1)    remote->set("test.specimen_name",QString::number(1));
            else if (ui->comboBox_specimen->currentIndex() == 2)    remote->set("test.specimen_name",QString::number(2));
        }
        tmp = 0;
        break;
    }
}
void PressApp::write_specimens_to_the_device(void)
{
    static u8 tmp = 0;

    switch(tmp ){
    case 0:
        remote->set("specimen.cube.w", QString::number(ui->doubleSpinBox_specimen_cube_w->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp ++;
        break;
    case 1:
        remote->set("specimen.cylinder.d", QString::number(ui->doubleSpinBox_specimen_cyl_d->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp ++;
        break;
    case 2:
        remote->set("specimen.cylinder.l", QString::number(ui->doubleSpinBox_specimen_cyl_l->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp ++;
        break;
    case 3:
        remote->set("specimen.masonry.l", QString::number(ui->doubleSpinBox_specimen_masonry_unit_l->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 4:
        remote->set("specimen.masonry.w", QString::number(ui->doubleSpinBox_specimen_masonry_unit_w->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 5:
        remote->set("specimen.beam.l", QString::number(ui->doubleSpinBox_specimen_beam4_l->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 6:
        remote->set("specimen.beam.s", QString::number(ui->doubleSpinBox_specimen_beam4_s->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 7:
        remote->set("specimen.beam.b", QString::number(ui->doubleSpinBox_specimen_beam4_b->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 8:
        remote->set("specimen.beam.d", QString::number(ui->doubleSpinBox_specimen_beam4_d->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 9:
        remote->set("specimen.beam.l", QString::number(ui->doubleSpinBox_specimen_beam3_l->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 10:
        remote->set("specimen.beam.b", QString::number(ui->doubleSpinBox_specimen_beam3_b->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 11:
        remote->set("specimen.beam.d", QString::number(ui->doubleSpinBox_specimen_beam3_d->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 12:
        remote->set("specimen.kerb.a", QString::number(ui->doubleSpinBox_specimen_kerb_a->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 13:
        remote->set("specimen.kerb.b", QString::number(ui->doubleSpinBox_specimen_kerb_b->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 14:
        remote->set("specimen.kerb.c", QString::number(ui->doubleSpinBox_specimen_kerb_c->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 15:
        remote->set("specimen.kerb.d", QString::number(ui->doubleSpinBox_specimen_kerb_d->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 16:
        remote->set("specimen.kerb.l", QString::number(ui->doubleSpinBox_specimen_kerb_l->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 17:
        remote->set("specimen.flagstone.l", QString::number(ui->doubleSpinBox_specimen_flagstone_l->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 18:
        remote->set("specimen.flagstone.s", QString::number(ui->doubleSpinBox_specimen_flagstone_s->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 19:
        remote->set("specimen.flagstone.b", QString::number(ui->doubleSpinBox_specimen_flagstone_b->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 20:
        remote->set("specimen.flagstone.d", QString::number(ui->doubleSpinBox_specimen_flagstone_d->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 21:
        remote->set("specimen.split_cube.l", QString::number(ui->doubleSpinBox_specimen_split_cube_w->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 22:
        remote->set("specimen.split_cylinder.l", QString::number(ui->doubleSpinBox_specimen_split_cylinder_l->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 23:
        remote->set("specimen.split_cylinder.d", QString::number(ui->doubleSpinBox_specimen_split_cylinder_d->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 24:
        remote->set("specimen.paving_stone.l", QString::number(ui->doubleSpinBox_specimen_split_paving_stone_l->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 25:
        remote->set("specimen.paving_stone.d", QString::number(ui->doubleSpinBox_specimen_split_paving_stone_d->value()));
        QTimer::singleShot(10,this,SLOT(write_specimens_to_the_device()));
        tmp++;
        break;
    case 26:
        if(ui->combo_testType->currentIndex() == COMPRESSION)  remote->set("test.type", QString::number(0));
        else if(ui->combo_testType->currentIndex() == FLEXURAL) remote->set("test.type", QString::number(1));
        if(ui->combo_testType->currentIndex() == SPLIT_TENSILE) remote->set("test.type", QString::number(2));
        tmp = 0;
        break;
    }
}
void PressApp::read_specimens_from_the_device()
{
    static u8 tmp = 0;

    switch(tmp ){
    case 0:
        remote->get("specimen.cube.l");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 1:
        remote->get("specimen.cube.w");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 2:
        remote->get("specimen.cylinder.d");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 3:
        remote->get("specimen.cylinder.l");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 4:
        remote->get("specimen.masonry.l");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 5:
        remote->get("specimen.masonry.w");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 6:
        remote->get("specimen.beam.l");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 7:
        remote->get("specimen.beam.s");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 8:
        remote->get("specimen.beam.b");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 9:
        remote->get("specimen.beam.d");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 10:
        remote->get("specimen.kerb.a");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 11:
        remote->get("specimen.kerb.b");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 12:
        remote->get("specimen.kerb.c");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 13:
        remote->get("specimen.kerb.d");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 14:
        remote->get("specimen.kerb.l");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 15:
        remote->get("specimen.flagstone.l");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 16:
        remote->get("specimen.flagstone.s");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 17:
        remote->get("specimen.flagstone.b");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 18:
        remote->get("specimen.flagstone.d");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 19:
        remote->get("specimen.split_cube.l");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 20:
        remote->get("specimen.split_cube.d");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 21:
        remote->get("specimen.split_cylinder.l");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 22:
        remote->get("specimen.split_cylinder.d");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 23:
        remote->get("specimen.paving_stone.l");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 24:
        remote->get("specimen.paving_stone.d");
        QTimer::singleShot(10,this,SLOT(read_specimens_from_the_device()));
        tmp ++;
        break;
    case 25:
        remote->get("test.type");
        tmp = 0;
        break;
    }
}
// Keep Record :
void PressApp::saveParameters(QString file_name)
{
    QSettings myRecord(file_name, QSettings::IniFormat);
    myRecord.beginGroup("Parametereler");
    myRecord.setValue(QString("KULANICI"),ui->lineEdit_user->text());
    myRecord.setValue(QString("YUK"),real_time.load);      // changed
    myRecord.setValue(QString("YUKLEME_HIZI"),ui->doubleSpinBox_pace_rate->value());
    myRecord.setValue(QString("GERILME"),real_time.stress);      // changed
    myRecord.setValue(QString("GERILME_HIZI"),ui->doubleSpinBox_pace_rate_mpa->value());
    myRecord.setValue(QString("BASLANGIC_HIZI"),ui->spinBox_start_speed_percentage->value());
    myRecord.setValue(QString("KIRILMA_ALT_LIMITI"),ui->doubleSpinBox_load_treshold->value());
    myRecord.setValue(QString("KIRILMA_YUZDESI"),ui->spinBox_break_percentage->value());
    myRecord.setValue(QString("MAKSIMUM_YUK"),ui->doubleSpinBox_max_load->value());
    myRecord.setValue(QString("SIFIR_BASKILAMA"),ui->doubleSpinBox_zero_suppression->value());
//    myRecord.setValue(QString("KANAL-2"),ui->spinBox_dp_ch2->value());        // TODO : decimal point yerine gercek degerleri gorunecek
//    myRecord.setValue(QString("KANAL-3"),ui->spinBox_dp_ch3->value());
//    myRecord.setValue(QString("KANAL-4"),ui->spinBox_dp_ch4->value());
    myRecord.endGroup();
    myRecord.sync();
    QProcess::execute("sync");
}
void PressApp::readParameters(QString file_name)
{
    QSettings myRecord(file_name, QSettings::IniFormat);
    ui->label_load->setText("Yük ("+ load_unit + ") : " + QString::number(myRecord.value("Parametereler/YUK").toDouble()));  // changed
    ui->doubleSpinBox_pace_rate->setValue(myRecord.value("Parametereler/YUKLEME_HIZI").toDouble());
    ui->label_stress->setText("Gerilme ("+ stress_unit + ") : " + QString::number(myRecord.value("Parametreler/GERILME").toDouble()));          // changed
    ui->doubleSpinBox_pace_rate_mpa->setValue(myRecord.value("Parametereler/GERILME_HIZI").toDouble());
    ui->spinBox_start_speed_percentage->setValue(myRecord.value("Parametereler/BASLANGIC_HIZI").toDouble());
    ui->doubleSpinBox_load_treshold->setValue(myRecord.value("Parametereler/KIRILMA_ALT_LIMITI").toDouble());
    ui->spinBox_break_percentage->setValue(myRecord.value("Parametereler/KIRILMA_YUZDESI").toDouble());
    ui->doubleSpinBox_max_load->setValue(myRecord.value("Parametereler/MAKSIMUM_YUK").toDouble());
    ui->doubleSpinBox_zero_suppression->setValue(myRecord.value("Parametereler/SIFIR_BASKILAMA").toDouble());
//    ui->spinBox_dp_ch2->setValue(myRecord.value("Parametereler/KANAL-2").toDouble());        // TODO : decimal point yerine gercek degerleri gorunecek
//    ui->spinBox_dp_ch3->setValue(myRecord.value("Parametereler/KANAL-3").toDouble());
//    ui->spinBox_dp_ch4->setValue(myRecord.value("Parametereler/KANAL-4").toDouble());
}
