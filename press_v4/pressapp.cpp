#include "pressapp.h"
#include "ui_pressapp.h"
#include <QTimer>
#include <QFile>
#include <QFileDialog>

PressApp::PressApp(QWidget *parent) :
    QMainWindow(parent),
    editReport(new EditReport),
    auxthread (new aux_thread(this)),
    ui(new Ui::PressApp)
{
    ui->setupUi(this);
    remote          = new RemoteConnection(8945,this);
    grid_plotArea   = new QGridLayout(ui->wdg_plotArea);
    customPlot      = new QCustomPlot(ui->wdg_plotArea);
    resizer         = new QTimer(this);
    _100_msec_timer = new QTimer(this);
    _time           = new QTimer(this);
    eth_timer       = new QTimer;
    _time           ->setInterval(100);
    _100_msec_timer ->setInterval(100);
    eth_timer       ->setInterval(100);
    global_running_timer.restart();
    _100_msec_timer ->start();
    show_graph = 0;
    qDebug()<<"tt"<<editReport->templ_type;

    QFont Font1("Times New Roman", Fontsize);
    hr = PressApp::GetScreenHRes(0);    //750
    vr = PressApp::GetScreenVRes(0);    //748
    pr = 1000;
    Fontsize = 13;
    if (ScreenWidth < 1680){
        AppW = hr*1010/pr;
        AppH = vr*630/pr;
        TabW = hr*195/pr;
        TabH = vr*28/pr;
        Fontsize = 11;
        qDebug()<<"SW < 1920";
    }
    if (ScreenWidth >= 1680){
        AppW = hr*1450/pr;
        AppH = vr*1020/pr;
        TabW = hr*300/pr;
        TabH = vr*40/pr;
        BtnH = vr*40/pr;
        Fontsize = 12;
        qDebug()<<"SW >= 1680";
    }
    if (ScreenWidth >= 3840){
        pr = pr/2;
        AppW = hr*1340/pr;
        AppH = vr*750/pr;
        TabW = hr*235/pr;
        TabH = vr*25/pr;
        Fontsize = 13;
        qDebug()<<"SW >= 3840";
    }
    if (ScreenWidth <= 1280){
        pr = 1500;
        AppW = hr*1530/pr;
        AppH = vr*790/pr;
        TabW = hr*290/pr;
        TabH = vr*40/pr;
        Fontsize = 9;
        qDebug()<<"SW <= 1280";
    }
    if (ScreenHeight < 720){
        pr = 1500;
//        AppW = hr*1500/pr;
//        AppH = vr*730/pr;
//        TabW = hr*270/pr;
//        TabH = vr*40/pr;
        Fontsize = 8;
        qDebug()<<"SH < 720";
    }
    qDebug()<<"Scr Width"<<ScreenWidth<<"ScreenHeight"<<ScreenHeight<<"| AppW :"<<AppW<<"App H :"<<AppH;
    resize(AppW,AppH);
    set_declaration();
    setup_GUI();
    get_password();

    connect(resizer,SIGNAL(timeout()),this,SLOT(resize_window()));
    connect(_time,SIGNAL(timeout()),this,SLOT(plot_graph()));
    connect(_100_msec_timer, SIGNAL(timeout()),this,SLOT(_100_msec_handler()));     //
    connect(remote,SIGNAL(periodic_response_handler(QByteArray)),this,SLOT(periodic_response_handler(QByteArray)));
    connect(ui->radioButton_frame1, SIGNAL(clicked()), this, SLOT(assign_frame()));
    connect(ui->radioButton_frame2, SIGNAL(clicked()), this, SLOT(assign_frame()));
    connect(ui->radioButton_automatic_print_on, SIGNAL(clicked()),this,SLOT(assign_printMode()));
    connect(ui->radioButton_automatic_print_off, SIGNAL(clicked()),this,SLOT(assign_printMode()));
    connect(ui->pushButton_connect, SIGNAL(clicked(bool)),this,SLOT(start_comm()));
    connect(ui->doubleSpinBox_pace_rate,SIGNAL(valueChanged(double)),this,SLOT(pace_rate_handler_kn()));
    connect(ui->doubleSpinBox_pace_rate_mpa,SIGNAL(valueChanged(double)),this,SLOT(pace_rate_handler_mpa()));

    userDir = ui->lineEdit_user->text();
    setup_PLOT();
// // GUI'den ///////////////////////////////////////////
    device_opening = true;
    command_send_protection_wait_timer= new QTimer(this);
    command_send_protection_wait_timer->setInterval(100);
    connect(command_send_protection_wait_timer, SIGNAL(timeout()),this,SLOT(command_sending_protection()));     //
    usart_signalmapper();
    connect(ui->comboBox_channel_no,SIGNAL(currentIndexChanged(int)),this,SLOT(cal_channel_change(int)));    // sila
    connect(ui->pushButton_start, SIGNAL(pressed()),this, SLOT (relay_on()));     //
    connect(ui->pushButton_stop, SIGNAL(pressed()),this, SLOT (relay_off()));     //
    connect(ui->comboBox_pid,SIGNAL(currentIndexChanged( int )),this,SLOT(pid_combobox_handle(int))); //
    connect(ui->pushButton_save_pid,SIGNAL(clicked()),this,SLOT(save_pid_values()));  //
    connect(ui->pushButton_save_pid_to_all,SIGNAL(clicked()),this,SLOT(save_pid_values_to_all()));        //
    connect(ui->pushButton_step_response,SIGNAL(released()),this,SLOT(step_response_handle()));     //
    connect(auxthread, SIGNAL(cohen_coon_kp(QString)), this->ui->label_step_resp_CC_KP, SLOT(setText(QString)));
    connect(auxthread, SIGNAL(cohen_coon_ki(QString)), this->ui->label_step_resp_CC_Ki, SLOT(setText(QString)));
    connect(auxthread, SIGNAL(cohen_coon_kd(QString)), this->ui->label_step_resp_CC_Kd, SLOT(setText(QString)));
    connect(auxthread, SIGNAL(let_step_response()),    this, SLOT(step_response_handle()));
}
void PressApp::set_declaration()
{
// GUI'den ////////////////////
    doubleSpinBox_load_tare_limit = new QDoubleSpinBox;
// ///////////////////////////

    grid_dialogPsw = new QGridLayout;
    dialog_psw    = new QDialog;
    wdg_dialogPsw = new QWidget;
    lbl_psw       = new QLabel("\nErişim için şifreyi girin !\n");
    btn_newPsw    = new QPushButton("Tamam");
    password      = new QLineEdit;
    cube     = "Küp";
    cylinder = "Silindir";
    beam3    = "Kiriş 3N";
    beam4    = "Kiriş 4N";
    kerb     = "Bordür";
    masonry  = "Briket";
    pavingstone = "Parke Taşı";
    flagstone   = "Karo";
    concrete    = "BETON";
    concrete_floor  = "BETON DÖŞEME";
    cement      = "ÇİMENTO";
    terrazzo    = "TERRAZZO";
    kagir       = "KAGIR";

    compression_list    = (QStringList() << "Küp" << "Silindir" << "Briket");
    flexural_list       = (QStringList() << "Kiriş-3N" << "Kiriş-4N" << "Bordür" << "Karo");
    splitTensile_list   = (QStringList() << "Küp" << "Silindir" << "Parke Taşı");

    format_type = ui->comboBox_formatFile->currentIndex();

    ui->combo_testType  ->addItem("Basma",0);
    ui->combo_testType  ->addItem("Eğilme",1);
    ui->combo_testType  ->addItem("Yarmada Çekme",2);
    ui->combo_testType  ->setCurrentIndex(0);
    ui->comboBox_graphChoice->addItem("Yük - Zaman"),0;
    ui->comboBox_graphChoice->addItem("Gerilme - Zaman",1);
    ui->comboBox_graphChoice->setCurrentIndex(0);
    ui->comboBox_unit   ->addItem("kN", 0);
    ui->comboBox_unit   ->addItem("lbf", 1);
    ui->comboBox_unit   ->addItem("kgf", 2);
    ui->comboBox_unit   ->setCurrentIndex(0);
    ui->comboBox_unit_ch  ->addItem("kN", 0);
    ui->comboBox_unit_ch  ->addItem("mm", 1);
    ui->comboBox_unit_ch  ->addItem("unitless",2);
    ui->comboBox_unit_ch  ->setCurrentIndex(0);
    ui->comboBox_channel_no ->addItem("CH1",0);
    ui->comboBox_channel_no ->addItem("CH2",1);
    ui->comboBox_channel_no ->addItem("CH3",2);
    ui->comboBox_channel_no ->addItem("CH4",3);
    ui->comboBox_channel_no ->setCurrentIndex(0);
    ui->comboBox_cal_point_number->addItem("2",0);
    ui->comboBox_cal_point_number->addItem("3",1);
    ui->comboBox_cal_point_number->addItem("4",2);
    ui->comboBox_cal_point_number->addItem("5",3);
    ui->comboBox_cal_point_number->addItem("6",4);
    ui->comboBox_cal_point_number->addItem("7",5);
    ui->comboBox_cal_point_number->addItem("8",6);
    ui->comboBox_pid    ->addItem("Küp",0);
    ui->comboBox_pid    ->addItem("Silindir",1);
    ui->comboBox_pid    ->addItem("Briket",2);
    ui->comboBox_pid    ->addItem("Kiriş-3N",3);
    ui->comboBox_pid    ->addItem("Kiriş-4N",4);
    ui->comboBox_pid    ->addItem("Bordür",5);
    ui->comboBox_pid    ->addItem("Karo",6);
    ui->comboBox_pid    ->addItem("Küp - Yarma",7);
    ui->comboBox_pid    ->addItem("Silindir - Yarma",8);
    ui->comboBox_pid    ->addItem("Parke Taşı - Yarma",9);
    ui->comboBox_pid    ->setCurrentIndex(0);
    ui->combo_voltageSet    ->addItem("+/- 10V" ,0);
    ui->combo_voltageSet    ->addItem("+/- 5V"  ,1);
    ui->combo_voltageSet    ->addItem("+/- 2.5V",2);
    ui->combo_voltageSet    ->addItem("+/- 1V"  ,3);
    ui->combo_voltageSet    ->addItem("+/- 500V",4);
    ui->combo_voltageSet    ->addItem("+/- 250mV",5);
    ui->combo_voltageSet    ->addItem("+/- 125mV",6);
    ui->combo_voltageSet    ->addItem("+/- 50mV",7);
    ui->combo_voltageSet    ->addItem("+/- 25mV",8);
    ui->combo_voltageSet    ->addItem("+/- 10mV",9);
    ui->combo_voltageSet    ->addItem("+/- 5mV",10);
    ui->combo_channelsSet   ->addItem("KANAL 1",0);
    ui->combo_channelsSet   ->addItem("KANAL 2",1);
    ui->combo_channelsSet   ->addItem("KANAL 3",2);
    ui->combo_channelsSet   ->addItem("KANAL 4",3);
    ui->combo_lang      ->addItem("Türkçe",0);
    ui->combo_lang      ->addItem("English",1);
    ui->combo_lang      ->setCurrentIndex(0);
    ui->combo_scrRes    ->addItem("16:9",0);
    ui->combo_scrRes    ->addItem("16:10",1);
    ui->combo_scrRes    ->setCurrentIndex(0);
    ui->doubleSpinBox_cal_point_value_1->setDecimals(ui->spinBox_dp_load->value());
    ui->doubleSpinBox_cal_point_value_2->setDecimals(ui->spinBox_dp_load->value());
    ui->doubleSpinBox_cal_point_value_3->setDecimals(ui->spinBox_dp_load->value());
    ui->doubleSpinBox_cal_point_value_4->setDecimals(ui->spinBox_dp_load->value());
    ui->doubleSpinBox_cal_point_value_5->setDecimals(ui->spinBox_dp_load->value());
    ui->doubleSpinBox_cal_point_value_6->setDecimals(ui->spinBox_dp_load->value());
    ui->doubleSpinBox_cal_point_value_7->setDecimals(ui->spinBox_dp_load->value());
    ui->doubleSpinBox_cal_point_value_8->setDecimals(ui->spinBox_dp_load->value());
}
void PressApp::setup_GUI()
{
    resizer->start(10);
    ui->page_app->hide();
    ui->page_main->show();

    step_response_status = false;

    ui->stackedWidget->setStyleSheet(QString("QLabel, QPushButton, QComboBox, QLineEdit, QToolBox, QTabWidget, QRadioButton, QSpinBox, QDoubleSpinBox, QToolButton, QScrollArea, QTimeEdit, QDateEdit, QDialog {font-size: %1pt}").arg(Fontsize));
    ui->tabWidget_app->setStyleSheet(QString("QTabBar::tab {width: %1px; height: %2px; font-size: %3pt} QPushButton, QComboBox {height: %4px}").arg(TabW).arg(TabH).arg(Fontsize).arg(BtnH));
    ui->tabWidget_app->setMinimumSize(AppW/1.2,AppH/1.2);
    ui->widget_plotArea->setMinimumWidth(AppW/4);
    ui->wdg_paramArea->setMinimumWidth(AppW/3.7);
    ui->wdg_paramArea->setMaximumWidth(AppW/2.7);
    ui->btn_okSpecimen->setMaximumSize(BtnH,BtnH);
    ui->btn_okGain->setMaximumSize(BtnH,BtnH);
    ui->btn_expand->setMaximumSize(BtnH*1.1,BtnH*1.1);
    ui->pushButton_printPlot->setMaximumSize(BtnH*1.1,BtnH*1.1);
    ui->img_specimen->setMinimumSize(TabW*1.05/2.3,TabW/1.5);
    ui->img_specimen->setMaximumSize(TabW*1.2,TabW/1.05);

    ui->pushButton_saveFile->setIcon(QIcon(":/icons/floppy_disk.png"));
    ui->pushButton_openFile->setIcon(QIcon(":/icons/folder_out.png"));

    ui->tabWidget_app->setCurrentIndex(0);
    ui->toolBox_app->setCurrentIndex(0);

    ui->combo_channelsSet->setCurrentIndex(0);
    ui->combo_voltageSet ->setCurrentIndex(0);

    ui->lineEdit_user->setClearButtonEnabled(1);
    ui->lineEdit_ip->setText("192.168.1.177");
    ui->lineEdit_ip->setInputMask("000.000.0.000;0");

    ui->pushButton_pauseTest->setDisabled(1);
    ui->pushButton_stopTest->setDisabled(1);
    ui->pushButton_refreshTest->hide();
    ui->pushButton_printPlot->setDisabled(1);
    ui->pushButton_quitFile->setDisabled(1);
    ui->page_specimen->setEnabled(1);
    ui->page_param->setEnabled(1);
    ui->page_channels->setEnabled(1);
    ui->page_calib->setEnabled(0);
    ui->page_pid->setEnabled(0);
    ui->page_gain->setEnabled(0);
    ui->wdg_adminSetting->setDisabled(1);
    ui->spinBox_load_invisible->hide();
    ui->label_read_write->hide();
    ui->pushButton_step_response->hide();

    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());
}
// process :
void PressApp::setup_users()
{
    QString path = QDir::currentPath();
    QFile users_file(path + "/user_list.txt");
    users_file.open(QIODevice::ReadWrite| QIODevice::Text);
    QTextStream line(&users_file);
    str_users = line.readAll().split("\n");
    str_users = str_users.toSet().toList();     // avoid to duplicate items
    if(!userDir.isEmpty())
        line<<userDir<<"\n";
    ui->comboBox_user->addItems(str_users);
}
void PressApp::resize_window()
{
    ui->page_main->setGeometry(0,0,this->width(),this->height());
}
bool PressApp::removeDir(const QString & dirName)
{
    bool result = true;
    QDir dir = QDir::currentPath() + "/" + dirName;
    if (dir.exists()) {
        qDebug()<<dirName<<"folder removed";
//        Q_FOREACH(QFileInfo info,
//                  dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {      // to delete directory's content
//            if (info.isDir())
//                result = removeDir(info.absoluteFilePath());
//            else
//                result = QFile::remove(info.absoluteFilePath());
//
//            if (!result)   return result;
//        }
        result = dir.rmdir(dirName);
        dir.removeRecursively();    // to completely delete directory
    }
    else
        qDebug()<<dirName<<"no such folder";
//    return result;
}
bool PressApp::label_name_compare(QLabel *p1, QLabel *p2)
{
    if ( p1 && p2 )
        return p1->objectName() < p2->objectName();
    return false;
}
void PressApp::calculate_area()
{
    switch (test_type) {
    case COMPRESSION:
        switch (specimen_type) {
        case COMPRESSION_CUBE:
            calc_area = ui->doubleSpinBox_specimen_cube_w->value() * ui->doubleSpinBox_specimen_cube_w->value();
            break;
        case COMPRESSION_CYLINDER:
            calc_area = M_PI * (ui->doubleSpinBox_specimen_cyl_d->value() * ui->doubleSpinBox_specimen_cyl_l->value())/4.0;
            break;
        case COMPRESSION_MASONRY_UNIT:
            calc_area = (ui->doubleSpinBox_specimen_masonry_unit_l->value() * ui->doubleSpinBox_specimen_masonry_unit_w->value());
            break;
        }
        break;
    case FLEXURAL:
        switch (specimen_type) {
        case FLEXURAL_BEAM3:
            calc_area = 2 * ui->doubleSpinBox_specimen_beam3_b->value() * ui->doubleSpinBox_specimen_beam3_d->value() * ui->doubleSpinBox_specimen_beam3_d->value();
            calc_area = calc_area/ (3.0 * (ui->doubleSpinBox_specimen_beam3_l->value()));
            break;
        case FLEXURAL_BEAM4:
            calc_area = 2 * ui->doubleSpinBox_specimen_beam4_b->value() * ui->doubleSpinBox_specimen_beam4_d->value() * ui->doubleSpinBox_specimen_beam4_d->value();
            calc_area = calc_area / (3.0 * (ui->doubleSpinBox_specimen_beam4_l->value() - ui->doubleSpinBox_specimen_beam4_s->value()));
            break;
        case FLEXURAL_FLAGSTONE:
            calc_area = 2 * ui->doubleSpinBox_specimen_flagstone_b->value() * ui->doubleSpinBox_specimen_flagstone_d->value() * ui->doubleSpinBox_specimen_flagstone_d->value();
            calc_area = calc_area / (3.0 * (ui->doubleSpinBox_specimen_flagstone_l->value() - ui->doubleSpinBox_specimen_flagstone_s->value()));
            break;
        case FLEXURAL_KERB:
            double A1, A2, A3, T, M, I, I1, I2, I3, Z;
            double a = ui->doubleSpinBox_specimen_kerb_a->value();
            double b = ui->doubleSpinBox_specimen_kerb_b->value();
            double c = ui->doubleSpinBox_specimen_kerb_c->value();
            double d = ui->doubleSpinBox_specimen_kerb_d->value();
            double l = ui->doubleSpinBox_specimen_kerb_l->value();

            A1 = (a * d) / 2;
            A2 = a * (c - d);
            A3 = b * c;

            T = A1 * (c - d + (d / 3)) + A2 * ((c - d) / 2) + A3 * c / 2;

            M = T / (A1 + A2 + A3);

            double d1, d2, d3;
            d1 = A1 * (c - d + (d / 3) - M) * (c - d + (d / 3) - M);
            d2 = A2 * ((c / 2) - (d / 2) - M) * ((c / 2) - (d / 2) - M);
            d3 = A3* ((c / 2) - M) * ((c / 2) - M);
            I = d1 + d2 + d3;

            I1 = a * d * d * d / 36;
            I2 = a * (c - d) * (c - d) * (c - d) / 12;
            I3 = b * c * c * c / 12;
            Z = (I + I1 + I2 + I3) / M;
            Z = Z * 4 / l;
            calc_area = Z;
            break;
        }
        break;
    case SPLIT_TENSILE:
        switch (specimen_type) {
        case SPLIT_TENSILE_CUBE:
            calc_area = M_PI * (ui->doubleSpinBox_specimen_split_cube_w->value() * ui->doubleSpinBox_specimen_split_cube_w->value())/2.0;
            break;
        case SPLIT_TENSILE_CYLINDER:
            calc_area = M_PI * (ui->doubleSpinBox_specimen_split_cylinder_d->value() * ui->doubleSpinBox_specimen_split_cylinder_l->value())/2.0;
            break;
        case SPLIT_TENSILE_PAVING_STONE:
            calc_area = (ui->doubleSpinBox_specimen_split_paving_stone_d->value() * ui->doubleSpinBox_specimen_split_paving_stone_l->value());
            break;
        }
        break;
    }
    ui->label_calculated_area->setText(QString("Alan : %1 %2").arg(calc_area).arg(length_unit) + "2");
    //ui->label_calculated_area->setText("Alan : " + QString::number(real_time.area,'f',3));
}
int PressApp::dac_voltage_to_raw(double val){
    return ((val*6467.8) + 22.363);
}
void PressApp::tare_channel(int chan){
    QByteArray data;
    data.resize(7);
    u8 chan_no = 255;

    switch (chan) {
    case 0:
        tared_val = tared_val + real_time.load;
        if((tared_val < doubleSpinBox_load_tare_limit->value())&&(tared_val > -doubleSpinBox_load_tare_limit->value()))
            chan_no = 0;
        else
            tared_val = tared_val - real_time.load;
        //ui->groupBox_main_load->setTitle(QString("LOAD (t:%1)").arg(tared_val));
        break;
    case 1:
        chan_no = 1;
        break;
    case 2:
        chan_no = 2;
        break;
    case 3:
        chan_no = 3;
        break;
    }
    send_data_order(data.data(),"TARE",0,3);
    data[4] = chan_no;
    EOL(data.data(),5);
    auxthread->serial->write(data);
#ifdef CONFIG_x86
    qDebug(__FUNCTION__);
#endif
}
void PressApp::tare_in_calibration(void){
    tare_channel(ui->comboBox_channel_no->currentIndex());
}
void PressApp::relay_on(void){
    auxthread->relay_start_stop = RELAY_ON;
    ui->pushButton_start->setDisabled(1);
    ui->pushButton_stop->setEnabled(1);
    qDebug()<<"relay_on";
#ifdef CONFIG_x86
    qDebug(__FUNCTION__);
#endif
}
void PressApp::relay_off(void){
    auxthread->relay_start_stop = RELAY_OFF;
    ui->pushButton_start->setEnabled(1);
    ui->pushButton_stop->setDisabled(1);
    qDebug()<<"relay_off";
#ifdef CONFIG_x86
    qDebug(__FUNCTION__);
#endif
}
void PressApp::usart_gain_signalmapper()      // sila
{
    int voltage = ui->combo_voltageSet->currentIndex();
    int channel = ui->combo_channelsSet->currentIndex();

    if(channel == CH_1){
        switch (voltage) {
        case _10V   :   signal_id = 0; break;
        case _5V    :   signal_id = 1; break;
        case _2_5V  :   signal_id = 2; break;
        case _1V    :   signal_id = 3; break;
        case _500V  :   signal_id = 4; break;
        case _250mV :   signal_id = 5; break;
        case _125mV :   signal_id = 6; break;
        case _50mV  :   signal_id = 7; break;
        case _25mV  :   signal_id = 8; break;
        case _10mV  :   signal_id = 9; break;
        case _5mV   :   signal_id = 10;break;
        }
    }
    else if(channel == CH_2){
        switch (voltage) {
        case _10V   :   signal_id = 11; break;
        case _5V    :   signal_id = 12; break;
        case _2_5V  :   signal_id = 13; break;
        case _1V    :   signal_id = 14; break;
        case _500V  :   signal_id = 15; break;
        case _250mV :   signal_id = 16; break;
        case _125mV :   signal_id = 17; break;
        case _50mV  :   signal_id = 18; break;
        case _25mV  :   signal_id = 19; break;
        case _10mV  :   signal_id = 20; break;
        case _5mV   :   signal_id = 21; break;
        }
    }
    else if(channel == CH_3){
        switch (voltage) {
        case _10V   :   signal_id = 22; break;
        case _5V    :   signal_id = 23; break;
        case _2_5V  :   signal_id = 24; break;
        case _1V    :   signal_id = 25; break;
        case _500V  :   signal_id = 26; break;
        case _250mV :   signal_id = 27; break;
        case _125mV :   signal_id = 28; break;
        case _50mV  :   signal_id = 29; break;
        case _25mV  :   signal_id = 30; break;
        case _10mV  :   signal_id = 31; break;
        case _5mV   :   signal_id = 32; break;
        }
    }
    else if(channel == CH_4){
        switch (voltage) {
        case _10V   :   signal_id = 33; break;
        case _5V    :   signal_id = 34; break;
        case _2_5V  :   signal_id = 35; break;
        case _1V    :   signal_id = 36; break;
        case _500V  :   signal_id = 37; break;
        case _250mV :   signal_id = 38; break;
        case _125mV :   signal_id = 39; break;
        case _50mV  :   signal_id = 40; break;
        case _25mV  :   signal_id = 41; break;
        case _10mV  :   signal_id = 42; break;
        case _5mV   :   signal_id = 43; break;
        }
    }
    signalMapper_usart->setMapping(this->ui->btn_okGain,  signal_id);
}
void PressApp::usart_signalmapper(void){
    signalMapper_usart = new QSignalMapper(this);
    signalMapper_usart->setMapping(this->ui->pushButton_tare_load,          44);
    signalMapper_usart->setMapping(this->ui->pushButton_tare_ch2,           45);
    signalMapper_usart->setMapping(this->ui->pushButton_tare_ch3,           46);
    signalMapper_usart->setMapping(this->ui->pushButton_tare_ch4,           47);
    signalMapper_usart->setMapping(this->ui->pushButton_save_all_cal_data,  50);

    connect(this->ui->btn_okGain,                    SIGNAL(clicked()), this, SLOT (usart_gain_signalmapper()));        // sila
    connect(this->ui->btn_okGain,                    SIGNAL(clicked()), signalMapper_usart, SLOT (map()));
    connect(this->ui->pushButton_tare_load,          SIGNAL(clicked()), signalMapper_usart, SLOT (map()));
    connect(this->ui->pushButton_tare_ch2,           SIGNAL(clicked()), signalMapper_usart, SLOT (map()));
    connect(this->ui->pushButton_tare_ch3,           SIGNAL(clicked()), signalMapper_usart, SLOT (map()));
    connect(this->ui->pushButton_tare_ch4,           SIGNAL(clicked()), signalMapper_usart, SLOT (map()));
    connect(this->ui->pushButton_save_all_cal_data,  SIGNAL(clicked()), signalMapper_usart, SLOT (map()));
    connect(this->signalMapper_usart,SIGNAL(mapped(int)), this, SLOT(usart_signalmapper_handler(int)));
}
void PressApp::usart_signalmapper_handler(int id){
    usart_signalmapper_no = id;
    command_send_protection_wait_timer->start();
    auxthread->command_silencer = true;
    qDebug()<<"usart signalmapper no"<<usart_signalmapper_no ;
}
void PressApp::print_test_results(){
    QByteArray data;
    data.resize(39);
    u8 tmp = 0;
    tmp++;
    if(tmp == 1) {
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("TEST RESULTS"))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("TEST NO : ")+ ui->label_test_no->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("START DATE : ")+ui->label_test_start_date->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("START TIME : ")+ui->label_test_start_time->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("FINISH TIME : ")+ui->label_test_finish_time->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("NUMERATOR : ")+(ui->label_test_no->text())+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("FILE : ")+ui->lineEdit_fileName->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("COMPANY : ")+ui->lineEdit_company->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("TEST NAME : ")+ui->lineEdit_testName->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+(ui->lineEdit_addInfo->text())+ui->lineEdit_addInfo2->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("USER : ")+ui->lineEdit_user->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("TEST TYPE : ")+ui->label_test_test_type->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("SPECIMEN : ")+ui->label_test_specimen_type->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("DIMENSIONS (%1) : ").arg(length_unit)+ui->label_test_dimensions->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("AGE : ") + ui->label_specAge->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("AREA (%1%2) : ").arg(length_unit,"2")+ui->label_test_area->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("PEAK LOAD (%1) : ").arg(load_unit)+ui->label_test_peak_load->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("PEAK STRESS (%1) : ").arg(stress_unit)+ui->label_test_peak_stress->text()+QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("                   ") + QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("                   ") + QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("                   ") + QString("                         "))).toLatin1().data(),0,35);
        send_data_order(data.data(),QString((QString("PRINT")+trUtf8("                   ") + QString("                         "))).toLatin1().data(),0,35);
        tmp=0;
    }
    data[35] = ' ';
    data[36] = 0x0A;
    EOL(data.data(),37);
    //fuzpid->pSerial->write(data);
    auxthread->serial->write(data);
    qDebug()<<"print test res";
}
void PressApp::_100_msec_handler(){
    static u32 local_counter = 0;
    //static u8 latest_graphic_draw_counter = 0;
    QTextStream datum(&excel_file);
    static QTime record_elapsed;
    static double time_counter = 0;
    static bool do_at_the_opening = true;

    local_counter++;

    if(do_at_the_opening){
        if(auxthread->communication_established){
            gain_cal_send_timer->start();
            auxthread->command_silencer = true;
            do_at_the_opening = false;
        }
    }
    if(auxthread->to_gui.hit){
        auxthread->to_gui.hit = false;

        for(u8 i = 0; i < 4; i++){
            if(i == 0){
                if(test_status == TEST_JUST_FINISHED){
                    //label_adc_cal_channel[i]->setText(QString::number(auxthread->peak_load,'f',precision[i]));
                    ui->label_load->setText("Yük :" + QString::number(auxthread->peak_load,'f',precision[0]) + load_unit);
                    ui->label_adc_cal_channel_2->setText(QString::number(auxthread->peak_load,'f',precision[1]));
                    ui->label_adc_cal_channel_3->setText(QString::number(auxthread->peak_load,'f',precision[2]));
                    ui->label_adc_cal_channel_4->setText(QString::number(auxthread->peak_load,'f',precision[3]));
                }
                else{
                    //label_adc_cal_channel[i]->setText(QString::number(((1.0*auxthread->to_gui.calibrated[i])),'f',precision[i]));
                    ui->label_load->setText("Yük :" + QString::number(1.0*auxthread->to_gui.calibrated[0],'f',precision[0]) + load_unit);
                    ui->label_adc_cal_channel_2->setText(QString::number(1.0*auxthread->to_gui.calibrated[1],'f',precision[1]));
                    ui->label_adc_cal_channel_3->setText(QString::number(1.0*auxthread->to_gui.calibrated[2],'f',precision[2]));
                    ui->label_adc_cal_channel_4->setText(QString::number(1.0*auxthread->to_gui.calibrated[3],'f',precision[3]));
                }
            }
            else{
                //label_adc_cal_channel[i]->setText(QString::number(((1.0*auxthread->to_gui.calibrated[i])),'f',precision[i]));
                ui->label_load->setText("Yük :" + QString::number((1.0*auxthread->to_gui.calibrated[0]),'f',precision[0]) + load_unit);
                ui->label_adc_cal_channel_2->setText(QString::number(1.0*auxthread->to_gui.calibrated[1],'f',precision[1]));
                ui->label_adc_cal_channel_3->setText(QString::number(1.0*auxthread->to_gui.calibrated[2],'f',precision[2]));
                ui->label_adc_cal_channel_4->setText(QString::number(1.0*auxthread->to_gui.calibrated[3],'f',precision[3]));
            }
            //label_adc_channel[i]->setText(QString::number(auxthread->to_gui.raw[i]));
            ui->label_adc_channel_1->setText(QString::number(auxthread->to_gui.raw[0]));
            ui->label_adc_channel_2->setText(QString::number(auxthread->to_gui.raw[1]));
            ui->label_adc_channel_3->setText(QString::number(auxthread->to_gui.raw[2]));
            ui->label_adc_channel_4->setText(QString::number(auxthread->to_gui.raw[3]));

            switch(auxthread->to_gui.gain[i]){
            case 0:
                ui->label_gain_0->setText("+/- 10 V");
                ui->label_gain_1->setText("+/- 10 V");
                ui->label_gain_2->setText("+/- 10 V");
                ui->label_gain_3->setText("+/- 10 V");
                break;
            case 1:
                ui->label_gain_0->setText("+/- 5 V");
                ui->label_gain_1->setText("+/- 5 V");
                ui->label_gain_2->setText("+/- 5 V");
                ui->label_gain_3->setText("+/- 5 V");
                break;
            case 2:
                ui->label_gain_0->setText("+/- 2.5 V");
                ui->label_gain_1->setText("+/- 2.5 V");
                ui->label_gain_2->setText("+/- 2.5 V");
                ui->label_gain_3->setText("+/- 2.5 V");
                break;
            case 3:
                ui->label_gain_0->setText("+/- 1 V");
                ui->label_gain_1->setText("+/- 1 V");
                ui->label_gain_2->setText("+/- 1 V");
                ui->label_gain_3->setText("+/- 1 V");
                break;
            case 4:
                ui->label_gain_0->setText("+/- 500 mV");
                ui->label_gain_1->setText("+/- 500 mV");
                ui->label_gain_2->setText("+/- 500 mV");
                ui->label_gain_3->setText("+/- 500 mV");
                break;
            case 5:
                ui->label_gain_0->setText("+/- 250 mV");
                ui->label_gain_1->setText("+/- 250 mV");
                ui->label_gain_2->setText("+/- 250 mV");
                ui->label_gain_3->setText("+/- 250 mV");
                break;
            case 6:
                ui->label_gain_0->setText("+/- 125 mV");
                ui->label_gain_1->setText("+/- 125 mV");
                ui->label_gain_2->setText("+/- 125 mV");
                ui->label_gain_3->setText("+/- 125 mV");
                break;
            case 7:
                ui->label_gain_0->setText("+/- 50 mV");
                ui->label_gain_1->setText("+/- 50 mV");
                ui->label_gain_2->setText("+/- 50 mV");
                ui->label_gain_3->setText("+/- 50 mV");
                break;
            case 8:
                ui->label_gain_0->setText("+/- 25 mV");
                ui->label_gain_1->setText("+/- 25 mV");
                ui->label_gain_2->setText("+/- 25 mV");
                ui->label_gain_3->setText("+/- 25 mV");
                break;
            case 9:
                ui->label_gain_0->setText("+/- 10 mV");
                ui->label_gain_1->setText("+/- 10 mV");
                ui->label_gain_2->setText("+/- 10 mV");
                ui->label_gain_3->setText("+/- 10 mV");
                break;
            case 10:
                ui->label_gain_0->setText("+/- 5 mV");
                ui->label_gain_1->setText("+/- 5 mV");
                ui->label_gain_2->setText("+/- 5 mV");
                ui->label_gain_3->setText("+/- 5 mV");
                break;
            }
        }
        ui->label_raw_sign_0->setText(QString(auxthread->to_gui.raw_sign[0]));
        ui->label_raw_sign_1->setText(QString(auxthread->to_gui.raw_sign[1]));
        ui->label_raw_sign_2->setText(QString(auxthread->to_gui.raw_sign[2]));
        ui->label_raw_sign_3->setText(QString(auxthread->to_gui.raw_sign[3]));


        float cal_val = 0;
        switch (current_cal_channel) {  //TODO:assign calculated values
            case 0:
                cal_val = auxthread->ch1_value;
                break;
            case 1:
                cal_val = auxthread->ch2_value;
                break;
            case 2:
                cal_val = auxthread->ch3_value;
                break;
            case 3:
                cal_val = auxthread->ch4_value;
                break;
            default:
                break;
        }
        ui->label_calibrated->setText(QString::number(cal_val,'f',precision[current_cal_channel]));
        cal_tab_raw_sign = auxthread->to_gui.raw_sign[current_cal_channel];
        if(cal_tab_raw_sign == '+'){
            ui->label_adc_channel_raw_data->setText(QString::number(current_channel_data));
        }
        else{
            ui->label_adc_channel_raw_data->setText(QString::number((s32)-current_channel_data));
        }

        if(auxthread->test_label_status){
            auxthread->test_label_status = false;
            ui->label_test_status->setText(trUtf8("Eşik Aşıldı"));
        }
        double d_val = ui->doubleSpinBox_specimen_split_paving_stone_d->value();
        switch(parameters[current_frame].test_type){
        case COMPRESSION:
            switch (parameters[current_frame].speciment_type_index_compression) {
            case COMPRESSION_CUBE:
                auxthread->stress  = (auxthread->load_value * 1000) / (real_time.area); // Pa = N/m^2, kPa = kN/m^2 => mPa = (kN/m^2)*(1/1000)
                break;
            case COMPRESSION_CYLINDER:
                auxthread->stress  = (auxthread->load_value * 1000) / (real_time.area);
                break;
            case COMPRESSION_MASONRY_UNIT:
                auxthread->stress  = (auxthread->load_value * 1000) / (real_time.area);
                break;
            }
            break;
        case FLEXURAL:
            switch (parameters[current_frame].speciment_type_index_flexural) {
            case FLEXURAL_BEAM3:
                auxthread->stress  = (auxthread->load_value * 1000) / (real_time.area);
                break;
            case FLEXURAL_BEAM4:
                auxthread->stress  = (auxthread->load_value * 1000) / (real_time.area);
                break;
            case FLEXURAL_KERB:
                auxthread->stress  = (auxthread->load_value * 1000) / (real_time.area);
                break;
            case FLEXURAL_FLAGSTONE:
                auxthread->stress  = (auxthread->load_value * 1000) / (real_time.area);
                break;
            }
            break;
        case SPLIT_TENSILE:
            switch (parameters[current_frame].speciment_type_index_split_tensile) {
            case SPLIT_TENSILE_CUBE:
                auxthread->stress  = (auxthread->load_value * 1000) / (real_time.area);
                break;
            case SPLIT_TENSILE_CYLINDER:
                auxthread->stress  = (auxthread->load_value * 1000) / (real_time.area);
                break;
            case SPLIT_TENSILE_PAVING_STONE:
                paving_stone_k = 0.01;
                if( d_val > 180){
                    paving_stone_k = (double)1.3;
                }
                else if(d_val > 140){
                    paving_stone_k = (double)1.3 - 30.0*((double)0.18 - (d_val / 1000))*((double)0.18 - (d_val / 1000));
                }
                else if(d_val > 130){
                    paving_stone_k = (double)1.23 + (double)0.002 * d_val;
                }
                else if(d_val > 100){
                    paving_stone_k = (double)1.11 + (double)0.004 * (d_val - 100);
                }
                else if(d_val > 90){
                    paving_stone_k = (double)1.06 + (double)0.005 * (d_val - 90);
                }
                else if(d_val > 70){
                    paving_stone_k = (double)0.94 + (double)0.006 * (d_val - 70);
                }
                else if(d_val > 60){
                    paving_stone_k = (double)0.87 + (double)0.007 * (d_val - 60);
                }
                else if(d_val > 40){
                    paving_stone_k = (double)0.71 + (double)0.008 * (d_val - 40);
                }

                auxthread->stress  = (auxthread->load_value *paving_stone_k * (double)637.0) / (real_time.area);
                break;
            }
            break;
        }
        if(unit_index != KN_MM){
            auxthread->stress = auxthread->stress / 1000;
        }

        if(auxthread->stress < 0) auxthread->stress = 0;

        if((test_status == TEST_RUNNING)||(test_status == TEST_PAUSED)){
            if(auxthread->stress > auxthread->peak_stress){
                auxthread->peak_stress = auxthread->stress;
            }
        }

        if(test_status == TEST_JUST_FINISHED){
            ui->label_stress->setText(QString::number((auxthread->peak_stress),'f',ui->spinBox_dp_stress->value()));
        }
        else{
            ui->label_stress->setText(QString::number((auxthread->stress),'f',ui->spinBox_dp_stress->value()));
        }

        if(auxthread->max_load_error == false){
            if(auxthread->load_value >= (ui->doubleSpinBox_max_load->value())){
                auxthread->hard_stop = true;
                auxthread->max_load_error = true;
                ui->label_alert_status->setText(trUtf8("Max Yük Hatası"));
            }
        }
        else{
            if(auxthread->load_value < (ui->doubleSpinBox_max_load->value())){
                auxthread->max_load_error = false;
                ui->label_alert_status->setText(trUtf8("Alarm Yok"));
            }
        }

        if(auxthread->to_gui.test_finished){
            auxthread->to_gui.test_finished = false;
            _time->stop();
            step_response_status = false;
            ui->pushButton_step_response->setText("Autotuning Başla");
            ui->label_test_status->setText("Deney Durumu : SONLANDI");
            finish_time = QTime::currentTime().toString();
            excel_file.close();

            ui->pushButton_pauseTest->setStyleSheet("border-image: url(:/icons/media_pause_dis.png)");
            ui->pushButton_pauseTest->setDisabled(1);
            ui->pushButton_stopTest->setStyleSheet("border-image: url(:/icons/media_stop_dis.png)");
            ui->pushButton_stopTest->setDisabled(1);
            finish_time = QTime::currentTime().toString();
            switch(parameters[current_frame].test_type){
            case COMPRESSION:
                switch (parameters[current_frame].speciment_type_index_compression) {
                case COMPRESSION_CUBE:
                    dimensions = QString::number(ui->doubleSpinBox_specimen_cube_w->value())+"x" + QString::number(ui->doubleSpinBox_specimen_cube_w->value()) +
                            "x" + QString::number(ui->doubleSpinBox_specimen_cube_w->value());
                    break;
                case COMPRESSION_CYLINDER:
                    dimensions = QString::number(ui->doubleSpinBox_specimen_cyl_d->value())+"x" + QString::number(ui->doubleSpinBox_specimen_cyl_l->value());
                    break;
                case COMPRESSION_MASONRY_UNIT:
                    dimensions = QString::number(ui->doubleSpinBox_specimen_masonry_unit_l->value())+"x" + QString::number(ui->doubleSpinBox_specimen_masonry_unit_w->value());
                    break;
                }
                break;
            case FLEXURAL:
                switch (parameters[current_frame].speciment_type_index_flexural) {
                case FLEXURAL_BEAM3:
                    dimensions = QString::number(ui->doubleSpinBox_specimen_beam3_l->value()) +
                            "x" + QString::number(ui->doubleSpinBox_specimen_beam3_b->value()) + "x" + QString::number(ui->doubleSpinBox_specimen_beam3_d->value());
                    break;
                case FLEXURAL_BEAM4:
                    dimensions = QString::number(ui->doubleSpinBox_specimen_beam4_l->value()) + "x" + QString::number(ui->doubleSpinBox_specimen_beam4_s->value()) +
                            "x" + QString::number(ui->doubleSpinBox_specimen_beam4_b->value()) + "x" + QString::number(ui->doubleSpinBox_specimen_beam4_d->value());
                    break;
                case FLEXURAL_KERB:
                    dimensions = QString::number(ui->doubleSpinBox_specimen_kerb_a->value()) + "x" + QString::number(ui->doubleSpinBox_specimen_kerb_b->value()) +
                            "x" + QString::number(ui->doubleSpinBox_specimen_kerb_c->value()) + "x" + QString::number(ui->doubleSpinBox_specimen_kerb_d->value()) +
                            "x" + QString::number(ui->doubleSpinBox_specimen_kerb_l->value());
                    break;
                case FLEXURAL_FLAGSTONE:
                    dimensions = QString::number(ui->doubleSpinBox_specimen_flagstone_l->value()) + "x" + QString::number(ui->doubleSpinBox_specimen_flagstone_s->value()) +
                            "x" + QString::number(ui->doubleSpinBox_specimen_flagstone_b->value()) + "x" + QString::number(ui->doubleSpinBox_specimen_flagstone_d->value());
                    break;
                }
                break;
            case SPLIT_TENSILE:
                switch (parameters[current_frame].speciment_type_index_split_tensile) {
                case SPLIT_TENSILE_CUBE:
                    dimensions = QString::number(ui->doubleSpinBox_specimen_split_cube_w->value())+"x" + QString::number(ui->doubleSpinBox_specimen_split_cube_w->value());
                    break;
                case SPLIT_TENSILE_CYLINDER:
                    dimensions = QString::number(ui->doubleSpinBox_specimen_split_cylinder_l->value())+"x" + QString::number(ui->doubleSpinBox_specimen_split_cylinder_d->value());
                    break;
                case SPLIT_TENSILE_PAVING_STONE:
                    dimensions = QString::number(ui->doubleSpinBox_specimen_split_paving_stone_l->value())+"x" + QString::number(ui->doubleSpinBox_specimen_split_paving_stone_d->value());
                    break;
                }
                break;
            }
            if(test_status == TEST_JUST_FINISHED){
                ui->pushButton_refreshTest->show();
                ui->pushButton_startTest->hide();
                if(automatic_print == 1){
                    QTimer::singleShot(1000,this,SLOT(print_test_results()));
                }
            }
            qDebug() << "girdi to_gui.test_finished";
        }
    }
    if((test_status == TEST_RUNNING)||(test_status == TEST_PAUSED)){
        if(auxthread->run_pid){
            time_counter = time_counter + record_elapsed.elapsed();
            record_elapsed.restart();
            if(ui->radioButton_record_raw_data_on->isChecked()){
                if(local_counter % ((u32)(10*ui->doubleSpinBox_record_interval->value())) == 0){
                    datum << QString::number((time_counter/1000),'f',1) << "," << real_time.load << "," << real_time.stress << "\n";
                }
            }
        }
        else{
            time_counter = 0;
            record_elapsed.restart();
        }
    }
}
// comboboxes :
void PressApp::on_comboBox_standard_currentIndexChanged(int index)
{
    standard_change = true;
    switch (index) {
    case 0:
        test_type = COMPRESSION;
        parameters[current_frame].test_type = COMPRESSION;
        ui->combo_testType ->setCurrentIndex(COMPRESSION);
        ui->comboBox_specimen -> clear();
        ui->comboBox_specimen ->addItem(cube, 0);
        ui->comboBox_specimen ->addItem(cylinder, 1);
        if(editReport->lang_file == 0) material_type = concrete;
        break;
    case 1:
        test_type = FLEXURAL;
        parameters[current_frame].test_type = FLEXURAL;
        ui->combo_testType->setCurrentIndex(FLEXURAL);
        ui->comboBox_specimen -> clear();
        ui->comboBox_specimen->addItem(beam3, 0);
        ui->comboBox_specimen->addItem(beam4, 1);
        if(editReport->lang_file == 0) material_type = concrete;
        break;
    case 2:
        test_type = FLEXURAL;
        parameters[current_frame].test_type = FLEXURAL;
        ui->combo_testType->setCurrentIndex(FLEXURAL);
        ui->comboBox_specimen -> clear();
        ui->comboBox_specimen ->addItem(kerb, 0);
        if(editReport->lang_file == 0) material_type = concrete;
        break;
    case 3:
        test_type = SPLIT_TENSILE;
        parameters[current_frame].test_type = SPLIT_TENSILE;
        ui->combo_testType->setCurrentIndex(SPLIT_TENSILE);
        ui->comboBox_specimen -> clear();
        ui->comboBox_specimen ->addItem(pavingstone, 0);
        if(editReport->lang_file == 0) material_type = concrete;
        break;
    case 4:
        test_type = SPLIT_TENSILE;
        parameters[current_frame].test_type = SPLIT_TENSILE;
        ui->combo_testType->setCurrentIndex(SPLIT_TENSILE);
        ui->comboBox_specimen -> clear();
        ui->comboBox_specimen ->addItem(cube, 0);
        ui->comboBox_specimen ->addItem(cylinder, 1);
        if(editReport->lang_file == 0) material_type = concrete;
        break;
    case 5:
        test_type = COMPRESSION;
        parameters[current_frame].test_type = COMPRESSION;
        ui->combo_testType->setCurrentIndex(COMPRESSION);
        ui->comboBox_specimen -> clear();
        ui->comboBox_specimen ->addItem(masonry, 0);
        material_type = kagir;
        break;
    case 6:
        test_type = FLEXURAL;
        parameters[current_frame].test_type = FLEXURAL;
        ui->combo_testType->setCurrentIndex(FLEXURAL);
        ui->comboBox_specimen -> clear();
        ui->comboBox_specimen ->addItem(masonry, 0);   // numune dogru mu? TODO
        if(editReport->lang_file == 0) material_type = concrete_floor;
        break;
    case 7:
        test_type = FLEXURAL;
        parameters[current_frame].test_type = FLEXURAL;
        ui->combo_testType->setCurrentIndex(FLEXURAL);  // test tipi dogru mu? TODO
        ui->comboBox_specimen -> clear();
        ui->comboBox_specimen ->addItem(flagstone, 0);
        material_type = terrazzo;
        break;
    case 8:
        test_type = COMPRESSION;
        parameters[current_frame].test_type = COMPRESSION;
        ui->combo_testType->setCurrentIndex(COMPRESSION);
        ui->comboBox_specimen -> clear();
        ui->comboBox_specimen ->addItem(cube, 0);          // numuneler dogru mu? TODO
        ui->comboBox_specimen ->addItem(cylinder, 1);
        ui->comboBox_specimen ->addItem(masonry, 2);
        material_type = cement;
        break;
    case 9:
        test_type = FLEXURAL;
        parameters[current_frame].test_type = FLEXURAL;
        ui->combo_testType->setCurrentIndex(FLEXURAL);
        ui->comboBox_specimen -> clear();
        ui->comboBox_specimen->addItem(beam3, 0);
        ui->comboBox_specimen->addItem(beam4, 1);
        ui->comboBox_specimen ->addItem(kerb, 0);
        ui->comboBox_specimen ->addItem(flagstone, 0);
        material_type = cement;
        break;
    case 10:
        test_type = COMPRESSION;
        parameters[current_frame].test_type = COMPRESSION;
        ui->combo_testType->setCurrentIndex(COMPRESSION);
        ui->comboBox_specimen -> clear();
        ui->comboBox_specimen ->addItem(flagstone, 0);
        material_type = concrete;
        break;
    }
    ui->combo_testType ->setDisabled(1);
    ui->label_test_type_specimen->setText("Deney : " + test_type_name); // + " - " + specimen_name);
}
void PressApp::on_combo_testType_currentIndexChanged(int index)
{
// UNLESS STANDARD COMBOBOX IS ENABLE :
    ui->txt_paving_stone_fpl->hide();           // TODO
    ui->label_test_paving_stone_fpl->hide();    // TODO
    current_frame = 0; // del
    test_type_name = ui->combo_testType->currentText();
    if(!standard_change){
        switch (index) {
        case 0:
            test_type = COMPRESSION;
            parameters[current_frame].test_type = COMPRESSION;
            ui->comboBox_specimen -> clear();
            ui->comboBox_specimen -> addItems(compression_list);
            break;
        case 1:
            test_type = FLEXURAL;
            parameters[current_frame].test_type = FLEXURAL;
            ui->comboBox_specimen -> clear();
            ui->comboBox_specimen -> addItems(flexural_list);
            break;
        case 2:
            test_type = SPLIT_TENSILE;
            parameters[current_frame].test_type = SPLIT_TENSILE;
            ui->comboBox_specimen -> clear();
            ui->comboBox_specimen -> addItems(splitTensile_list);
            break;
        }
    }
    ui->label_test_type_specimen->setText("Deney : " + test_type_name); // + " - " + specimen_name);
}
void PressApp::on_comboBox_specimen_currentIndexChanged(int index)
{
    ui->label_calculated_area->setText("Alan :");
    int std_no = ui->comboBox_standard->currentIndex();
    if(standard_change){
        switch (std_no) {
        case 0:
            switch (index) {
            case COMPRESSION_CUBE:
                specimen_type = COMPRESSION_CUBE;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/cube.png)");
                ui->stack_cube_press-> show();
                ui->stack_cube_press-> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();
                dimensions = QString::number(ui->doubleSpinBox_specimen_cube_w->value())+" x "
                        + QString::number(ui->doubleSpinBox_specimen_cube_w->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_cube_w->value());
                break;
            case COMPRESSION_CYLINDER:
                specimen_type = COMPRESSION_CYLINDER;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/cylinder.png)");
                ui->stack_cyl_press -> show();
                ui->stack_cyl_press -> adjustSize();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_cyl_d->value())+" x "
                        + QString::number(ui->doubleSpinBox_specimen_cyl_l->value());
                break;
            }
            break;
        case 1:
            switch (index) {
            case FLEXURAL_BEAM3:
                specimen_type = FLEXURAL_BEAM3;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/beam3n.png)");
                ui->stack_beam3n    -> show();
                ui->stack_beam3n    -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_beam3_l->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam3_b->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam3_d->value());
                break;
            case FLEXURAL_BEAM4:
                specimen_type = FLEXURAL_BEAM4;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/beam4n.png)");
                ui->stack_beam4n    -> show();
                ui->stack_beam4n    -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_beam4_l->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam4_s->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam4_b->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam4_d->value());
                break;
            }
            break;
        case 2:
            specimen_type = FLEXURAL_KERB;
            ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/kerb.png)");
            ui->stack_kerb      -> show();
            ui->stack_kerb      -> adjustSize();
            ui->stack_cyl_press -> hide();
            ui->stack_cube_press-> hide();
            ui->stack_cyl_split -> hide();
            ui->stack_beam3n    -> hide();
            ui->stack_beam4n    -> hide();
            ui->stack_cube_split-> hide();
            ui->stack_flagstone -> hide();
            ui->stack_masonary  -> hide();
            ui->stack_pavingStone->hide();

            dimensions = QString::number(ui->doubleSpinBox_specimen_kerb_a->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_kerb_b->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_kerb_c->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_kerb_d->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_kerb_l->value());
            break;
        case 3:
            specimen_type = SPLIT_TENSILE_PAVING_STONE;
            ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/pavingstone.png)");
            ui->stack_pavingStone->show();
            ui->stack_pavingStone->adjustSize();
            ui->stack_cyl_press -> hide();
            ui->stack_cube_press-> hide();
            ui->stack_cyl_split -> hide();
            ui->stack_beam3n    -> hide();
            ui->stack_beam4n    -> hide();
            ui->stack_cube_split-> hide();
            ui->stack_flagstone -> hide();
            ui->stack_kerb      -> hide();
            ui->stack_masonary  -> hide();

            dimensions = QString::number(ui->doubleSpinBox_specimen_split_paving_stone_l->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_split_paving_stone_d->value());
            break;
        case 4:
            switch (index) {
            case SPLIT_TENSILE_CUBE:
                specimen_type = SPLIT_TENSILE_CUBE;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/cube.png)");
                ui->stack_cube_split-> show();
                ui->stack_cube_split-> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_split_cube_w->value())+" x "
                        + QString::number(ui->doubleSpinBox_specimen_split_cube_w->value());
                break;
            case SPLIT_TENSILE_CYLINDER:
                specimen_type = SPLIT_TENSILE_CYLINDER;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/cylinder-split.png)");
                ui->stack_cyl_split -> show();
                ui->stack_cyl_split -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_split_cylinder_l->value())+" x "
                        + QString::number(ui->doubleSpinBox_specimen_split_cylinder_d->value());
                break;
            }
            break;
        case 5:
            specimen_type = COMPRESSION_MASONRY_UNIT;
            ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/masonary.png)");
            ui->stack_masonary  -> show();
            ui->stack_masonary  -> adjustSize();
            ui->stack_cyl_press -> hide();
            ui->stack_cube_press-> hide();
            ui->stack_cyl_split -> hide();
            ui->stack_beam3n    -> hide();
            ui->stack_beam4n    -> hide();
            ui->stack_cube_split-> hide();
            ui->stack_flagstone -> hide();
            ui->stack_kerb      -> hide();
            ui->stack_pavingStone->hide();

            dimensions = QString::number(ui->doubleSpinBox_specimen_masonry_unit_l->value())+" x "
                    + QString::number(ui->doubleSpinBox_specimen_masonry_unit_w->value());
            break;
        case 6:
            specimen_type = COMPRESSION_MASONRY_UNIT;       // TODO
            ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/masonary.png)");
            ui->stack_masonary  -> show();
            ui->stack_masonary  -> adjustSize();
            ui->stack_cyl_press -> hide();
            ui->stack_cube_press-> hide();
            ui->stack_cyl_split -> hide();
            ui->stack_beam3n    -> hide();
            ui->stack_beam4n    -> hide();
            ui->stack_cube_split-> hide();
            ui->stack_flagstone -> hide();
            ui->stack_kerb      -> hide();
            ui->stack_pavingStone->hide();

            dimensions = QString::number(ui->doubleSpinBox_specimen_masonry_unit_l->value())+" x "
                    + QString::number(ui->doubleSpinBox_specimen_masonry_unit_w->value());
            break;
        case 7:
            specimen_type = FLEXURAL_FLAGSTONE;
            ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/flagstone.png)");
            ui->stack_flagstone -> show();
            ui->stack_flagstone -> adjustSize();
            ui->stack_cyl_press -> hide();
            ui->stack_cube_press-> hide();
            ui->stack_cyl_split -> hide();
            ui->stack_beam3n    -> hide();
            ui->stack_beam4n    -> hide();
            ui->stack_cube_split-> hide();
            ui->stack_kerb      -> hide();
            ui->stack_masonary  -> hide();
            ui->stack_pavingStone->hide();

            dimensions = QString::number(ui->doubleSpinBox_specimen_flagstone_l->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_flagstone_s->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_flagstone_b->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_flagstone_d->value());
            break;
        case 8:
            switch (index) {
            case COMPRESSION_CUBE:
                specimen_type = COMPRESSION_CUBE;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/cube.png)");
                ui->stack_cube_press-> show();
                ui->stack_cube_press-> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_cube_w->value())+" x "
                        + QString::number(ui->doubleSpinBox_specimen_cube_w->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_cube_w->value());
                break;
            case COMPRESSION_CYLINDER:
                specimen_type = COMPRESSION_CYLINDER;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/cylinder.png)");
                ui->stack_cyl_press -> show();
                ui->stack_cyl_press -> adjustSize();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_cyl_d->value())+" x "
                        + QString::number(ui->doubleSpinBox_specimen_cyl_l->value());
                break;
            case COMPRESSION_MASONRY_UNIT:
                specimen_type = COMPRESSION_MASONRY_UNIT;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/masonary.png)");
                ui->stack_masonary  -> show();
                ui->stack_masonary  -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_masonry_unit_l->value())+" x "
                        + QString::number(ui->doubleSpinBox_specimen_masonry_unit_w->value());
                break;
            }
            break;
        case 9:
            switch(index) {
            case FLEXURAL_BEAM3:
                specimen_type = FLEXURAL_BEAM3;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/beam3n.png)");
                ui->stack_beam3n    -> show();
                ui->stack_beam3n    -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_beam3_l->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam3_b->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam3_d->value());
                break;
            case FLEXURAL_BEAM4:
                specimen_type = FLEXURAL_BEAM4;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/beam4n.png)");
                ui->stack_beam4n    -> show();
                ui->stack_beam4n    -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_beam4_l->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam4_s->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam4_b->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam4_d->value());
                break;
            case FLEXURAL_KERB:
                specimen_type = FLEXURAL_KERB;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/kerb.png)");
                ui->stack_kerb      -> show();
                ui->stack_kerb      -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_kerb_a->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_kerb_b->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_kerb_c->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_kerb_d->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_kerb_l->value());
                break;
            case FLEXURAL_FLAGSTONE:
                specimen_type = FLEXURAL_FLAGSTONE;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/flagstone.png)");
                ui->stack_flagstone -> show();
                ui->stack_flagstone -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_flagstone_l->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_flagstone_s->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_flagstone_b->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_flagstone_d->value());
                break;
            }
            break;
        case 10:
            specimen_type = FLEXURAL_FLAGSTONE;
            ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/flagstone.png)");
            ui->stack_flagstone -> show();
            ui->stack_flagstone -> adjustSize();
            ui->stack_cyl_press -> hide();
            ui->stack_cube_press-> hide();
            ui->stack_cyl_split -> hide();
            ui->stack_beam3n    -> hide();
            ui->stack_beam4n    -> hide();
            ui->stack_cube_split-> hide();
            ui->stack_kerb      -> hide();
            ui->stack_masonary  -> hide();
            ui->stack_pavingStone->hide();

            dimensions = QString::number(ui->doubleSpinBox_specimen_flagstone_l->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_flagstone_s->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_flagstone_b->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_flagstone_d->value());
            break;
       }
    }
    if (!standard_change){         // unless standard combobox is enable :
        if(test_type == COMPRESSION){
            switch (index) {
            case COMPRESSION_CUBE:
                specimen_type = COMPRESSION_CUBE;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/cube.png)");
                ui->stack_cube_press-> show();
                ui->stack_cube_press-> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_cube_w->value())+" x "
                        + QString::number(ui->doubleSpinBox_specimen_cube_w->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_cube_w->value());
                break;
            case COMPRESSION_CYLINDER:
                specimen_type = COMPRESSION_CYLINDER;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/cylinder.png)");
                ui->stack_cyl_press -> show();
                ui->stack_cyl_press -> adjustSize();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_cyl_d->value())+" x "
                        + QString::number(ui->doubleSpinBox_specimen_cyl_l->value());
                break;
            case COMPRESSION_MASONRY_UNIT:
                specimen_type = COMPRESSION_MASONRY_UNIT;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/masonary.png)");
                ui->stack_masonary  -> show();
                ui->stack_masonary  -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_masonry_unit_l->value())+" x "
                        + QString::number(ui->doubleSpinBox_specimen_masonry_unit_w->value());
                break;
            }
            parameters[current_frame].speciment_type_index_compression = specimen_type;
        }
        else if(test_type == FLEXURAL){
            switch(index) {
            case FLEXURAL_BEAM3:
                specimen_type = FLEXURAL_BEAM3;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/beam3n.png)");
                ui->stack_beam3n    -> show();
                ui->stack_beam3n    -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_beam3_l->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam3_b->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam3_d->value());
                break;
            case FLEXURAL_BEAM4:
                specimen_type = FLEXURAL_BEAM4;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/beam4n.png)");
                ui->stack_beam4n    -> show();
                ui->stack_beam4n    -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_beam4_l->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam4_s->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam4_b->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_beam4_d->value());
                break;
            case FLEXURAL_KERB:
                specimen_type = FLEXURAL_KERB;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/kerb.png)");
                ui->stack_kerb      -> show();
                ui->stack_kerb      -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_kerb_a->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_kerb_b->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_kerb_c->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_kerb_d->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_kerb_l->value());
                break;
            case FLEXURAL_FLAGSTONE:
                specimen_type = FLEXURAL_FLAGSTONE;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/flagstone.png)");
                ui->stack_flagstone -> show();
                ui->stack_flagstone -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_flagstone_l->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_flagstone_s->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_flagstone_b->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_flagstone_d->value());
                break;
            }
            parameters[current_frame].speciment_type_index_flexural = specimen_type;
        }
        else if(test_type == SPLIT_TENSILE){
            switch(index) {
            case SPLIT_TENSILE_CUBE:
                specimen_type = SPLIT_TENSILE_CUBE;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/cube.png)");
                ui->stack_cube_split-> show();
                ui->stack_cube_split-> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_split_cube_w->value())+" x "
                        + QString::number(ui->doubleSpinBox_specimen_split_cube_w->value());
                break;
            case SPLIT_TENSILE_CYLINDER:
                specimen_type = SPLIT_TENSILE_CYLINDER;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/cylinder-split.png)");
                ui->stack_cyl_split -> show();
                ui->stack_cyl_split -> adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();
                ui->stack_pavingStone->hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_split_cylinder_l->value())+" x "
                        + QString::number(ui->doubleSpinBox_specimen_split_cylinder_d->value());
                break;
            case SPLIT_TENSILE_PAVING_STONE:
                specimen_type = SPLIT_TENSILE_PAVING_STONE;
                ui->img_specimen    -> setStyleSheet("border-image: url(:/specimen_img/pavingstone.png)");
                ui->stack_pavingStone->show();
                ui->stack_pavingStone->adjustSize();
                ui->stack_cyl_press -> hide();
                ui->stack_cube_press-> hide();
                ui->stack_cyl_split -> hide();
                ui->stack_beam3n    -> hide();
                ui->stack_beam4n    -> hide();
                ui->stack_cube_split-> hide();
                ui->stack_flagstone -> hide();
                ui->stack_kerb      -> hide();
                ui->stack_masonary  -> hide();

                dimensions = QString::number(ui->doubleSpinBox_specimen_split_paving_stone_l->value()) + " x "
                        + QString::number(ui->doubleSpinBox_specimen_split_paving_stone_d->value());
                break;
            }
            parameters[current_frame].speciment_type_index_split_tensile = specimen_type;
        }
    }
    specimen_name = ui->comboBox_specimen->currentText();
    ui->label_specimen->setText("Numune : " + specimen_name);
}
void PressApp::on_comboBox_unit_currentIndexChanged(int index)
{
    u8 old_index = unit_index;
    load_unit_multiplier = 1;
    length_unit_multiplier = 1;
    area_unit_multiplier = 1;

    switch (index) {
    case 0:
        unit_index = KN_MM;
        load_unit = QString("kN");
        stress_unit = QString("MPa");
        length_unit = QString("mm");
        break;
    case 1:
        unit_index = LBF_IN;
        load_unit = QString("lbf");
        stress_unit = QString("psi");
        length_unit = QString("in");
        break;
    case 2:
        unit_index = KGF_CM;
        load_unit = QString("kgf");
        stress_unit = QString("kgf/cm2");
        length_unit = QString("cm");
        break;
    }

    ui->comboBox_unit_ch->setItemText(0,load_unit);
    ui->comboBox_unit_ch->setItemText(1,length_unit);
    ui->label_ch2_unit->setText(ui->comboBox_unit_ch->currentText());
    ui->label_ch3_unit->setText(ui->comboBox_unit_ch->currentText());
    ui->label_ch4_unit->setText(ui->comboBox_unit_ch->currentText());

    ui->label_load->setText(QString("Yük (%1) :").arg(load_unit));
    ui->label_stress->setText(QString("Gerilme (%1) :").arg(stress_unit));
    ui->label_calculated_area->setText(QString("Alan : %1 %2").arg(calc_area).arg(length_unit) + "2");
    ui->label_unit_max_load->setText(load_unit);
    ui->label_unit_failure_threshold->setText(load_unit);
    ui->label_unit_zero_suppression->setText(load_unit);
    ui->label_unit_pace_load->setText(QString("%1/s").arg(load_unit));
    ui->label_unit_pace_stress->setText(QString("%1/s").arg(stress_unit));
    ui->txt_peak_load->setText(QString("Tepe Yük (%1) : ").arg(load_unit));
    ui->txt_peak_stress->setText(QString("Tepe Gerilim (%1) : ").arg(stress_unit));
    ui->txt_test_dimensions->setText(QString("Boyutlar (%1) : ").arg(length_unit));
    ui->txt_test_area->setText(QString("Alan (%1%2) : ").arg(length_unit,"2"));
    ui->txt_paving_stone_fpl->setText(QString("P/L (%1/%2) : ").arg(load_unit).arg(length_unit));
    ui->txt_value->setText(QString("Değer (%1) : ").arg(load_unit));

    QList<QLabel*> label_unit_specimen = this->findChildren<QLabel*>(QRegExp("label_unit_specimen"));
    qSort(label_unit_specimen.begin(),label_unit_specimen.end(),label_name_compare);

    for(u8 i = 0; i < label_unit_specimen.length(); i++){
        label_unit_specimen[i]->setText(length_unit);
    }

//    graphic_axes_handler(index);        // open

    switch (old_index) {
    case KN_MM:
        if(unit_index == LBF_IN){
            load_unit_multiplier = 224.808943;       //kN->lbf
            //stress_multiplier = 145.037738;        //MPa->psi
            length_unit_multiplier = 0.0393700787;   //mm->in
            area_unit_multiplier = 0.0015500031;     //mm2->in2
        }
        else if(unit_index == KGF_CM){
            load_unit_multiplier = 101.971621;       //kN->kgf
            //stress_multiplier = 10.197162;         //MPa->kgf/cm2
            length_unit_multiplier = 0.1;            //mm->cm
            area_unit_multiplier = 0.01;             //mm2->cm2
        }
        break;
    case LBF_IN:
        if(unit_index == KN_MM){
            load_unit_multiplier = 0.00444822162;    //lbf->kN
            //stress_multiplier = 0.00689475729;     //psi->MPa
            length_unit_multiplier = 25.4;           //in->mm
            area_unit_multiplier = 645.16;           //in2->mm2
        }
        else if(unit_index == KGF_CM){
            load_unit_multiplier = 0.45359237;       //lbf->kgf
            //stress_multiplier = 0.070306958;       //psi->kgf/cm2
            length_unit_multiplier = 2.54;           //in->cm
            area_unit_multiplier = 6.4516;           //in2->cm2
        }
        break;
    case KGF_CM:
        if(unit_index == KN_MM){
            load_unit_multiplier = 0.00980665;       //kgf->kN
            //stress_multiplier = 0.0980665;         //kgf/cm2->MPa
            length_unit_multiplier = 10;             //cm->mm
            area_unit_multiplier = 100;              //cm2->mm2
        }
        else if(unit_index == LBF_IN){
            load_unit_multiplier = 2.20462262;       //kgf->lbf
            //stress_multiplier = 14.2233433;        //kgf/cm2->psi
            length_unit_multiplier = 0.393700787;    //cm->in
            area_unit_multiplier = 0.15500031;       //cm2->in2
        }
        break;
    }

    double uncorrupted_pace = ui->doubleSpinBox_pace_rate->value();

    ui->doubleSpinBox_specimen_cube_w->setValue(ui->doubleSpinBox_specimen_cube_w->value() * length_unit_multiplier);
//    ui->doubleSpinBox_specimen_cube_l->setValue(ui->doubleSpinBox_specimen_cube_l->value() * length_unit_multiplier);
//    ui->doubleSpinBox_specimen_cube_h->setValue(ui->doubleSpinBox_specimen_cube_h->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_cyl_d->setValue(ui->doubleSpinBox_specimen_cyl_d->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_cyl_l->setValue(ui->doubleSpinBox_specimen_cyl_l->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_masonry_unit_l->setValue(ui->doubleSpinBox_specimen_masonry_unit_l->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_masonry_unit_w->setValue(ui->doubleSpinBox_specimen_masonry_unit_w->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_beam3_l->setValue(ui->doubleSpinBox_specimen_beam3_l->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_beam3_b->setValue(ui->doubleSpinBox_specimen_beam3_b->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_beam3_d->setValue(ui->doubleSpinBox_specimen_beam3_d->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_beam4_l->setValue(ui->doubleSpinBox_specimen_beam4_l->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_beam4_s->setValue(ui->doubleSpinBox_specimen_beam4_s->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_beam4_b->setValue(ui->doubleSpinBox_specimen_beam4_b->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_beam4_d->setValue(ui->doubleSpinBox_specimen_beam4_d->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_kerb_a->setValue(ui->doubleSpinBox_specimen_kerb_a->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_kerb_b->setValue(ui->doubleSpinBox_specimen_kerb_b->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_kerb_c->setValue(ui->doubleSpinBox_specimen_kerb_c->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_kerb_d->setValue(ui->doubleSpinBox_specimen_kerb_d->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_kerb_l->setValue(ui->doubleSpinBox_specimen_kerb_l->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_flagstone_l->setValue(ui->doubleSpinBox_specimen_flagstone_l->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_flagstone_s->setValue(ui->doubleSpinBox_specimen_flagstone_s->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_flagstone_b->setValue(ui->doubleSpinBox_specimen_flagstone_b->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_flagstone_d->setValue(ui->doubleSpinBox_specimen_flagstone_d->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_split_cube_w->setValue(ui->doubleSpinBox_specimen_split_cube_w->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_split_cylinder_l->setValue(ui->doubleSpinBox_specimen_split_cylinder_l->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_split_cylinder_d->setValue(ui->doubleSpinBox_specimen_split_cylinder_d->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_split_paving_stone_l->setValue(ui->doubleSpinBox_specimen_split_paving_stone_l->value() * length_unit_multiplier);
    ui->doubleSpinBox_specimen_split_paving_stone_d->setValue(ui->doubleSpinBox_specimen_split_paving_stone_d->value() * length_unit_multiplier);

    ui->doubleSpinBox_pace_rate->setValue(uncorrupted_pace * load_unit_multiplier);
    uncorrupted_pace = ui->doubleSpinBox_pace_rate->value();

    switch (parameters[current_frame].test_type) {  //this is for area recalculation
        case COMPRESSION:
            on_comboBox_specimen_currentIndexChanged(parameters[current_frame].speciment_type_index_compression);
            break;
        case FLEXURAL:
            on_comboBox_specimen_currentIndexChanged(parameters[current_frame].speciment_type_index_flexural);
            break;
        case SPLIT_TENSILE:
            on_comboBox_specimen_currentIndexChanged(parameters[current_frame].speciment_type_index_split_tensile);
            break;
    }

    ui->doubleSpinBox_pace_rate->setValue(uncorrupted_pace);
    switch(unit_index){
    case KN_MM:     //1 Pa = 1 N/m2
        ui->doubleSpinBox_pace_rate_mpa->setValue(1000 * ui->doubleSpinBox_pace_rate->value() / calc_area);
        break;
    case LBF_IN:    //1 psi = 1 lbf/in2
        ui->doubleSpinBox_pace_rate_mpa->setValue(ui->doubleSpinBox_pace_rate->value() / calc_area);
        break;
    case KGF_CM:    //kgf/cm2
        ui->doubleSpinBox_pace_rate_mpa->setValue(ui->doubleSpinBox_pace_rate->value() / calc_area);
        break;
    }

    ui->doubleSpinBox_max_load->setValue(ui->doubleSpinBox_max_load->value() * load_unit_multiplier);
    ui->doubleSpinBox_load_treshold->setValue(ui->doubleSpinBox_load_treshold->value() * load_unit_multiplier);
    ui->doubleSpinBox_zero_suppression->setValue(ui->doubleSpinBox_zero_suppression->value() * load_unit_multiplier);

  //  ui->label_pace_rate->setText(QString("Yükleme Hızı : %1 %2/s").arg(ui->doubleSpinBox_pace_rate->value()).arg(load_unit));     // OPEN

// GUI'den ////////////////////////////////////////
    if(device_opening == false){
        if(current_frame == FRAME1)
            ui->comboBox_channel_no->setCurrentIndex(0);
        else if(current_frame == FRAME2)
            ui->comboBox_channel_no->setCurrentIndex(1);

        ui->doubleSpinBox_cal_point_value_1->setValue(ui->doubleSpinBox_cal_point_value_1->value() * load_unit_multiplier);
        ui->doubleSpinBox_cal_point_value_2->setValue(ui->doubleSpinBox_cal_point_value_2->value() * load_unit_multiplier);
        ui->doubleSpinBox_cal_point_value_3->setValue(ui->doubleSpinBox_cal_point_value_3->value() * load_unit_multiplier);
        ui->doubleSpinBox_cal_point_value_4->setValue(ui->doubleSpinBox_cal_point_value_4->value() * load_unit_multiplier);
        ui->doubleSpinBox_cal_point_value_5->setValue(ui->doubleSpinBox_cal_point_value_5->value() * load_unit_multiplier);
        ui->doubleSpinBox_cal_point_value_6->setValue(ui->doubleSpinBox_cal_point_value_6->value() * load_unit_multiplier);
        ui->doubleSpinBox_cal_point_value_7->setValue(ui->doubleSpinBox_cal_point_value_7->value() * load_unit_multiplier);
        ui->doubleSpinBox_cal_point_value_8->setValue(ui->doubleSpinBox_cal_point_value_8->value() * load_unit_multiplier);

        ui->pushButton_save_all_cal_data->click();
    }
}
void PressApp::on_comboBox_unit_ch_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->label_ch2_unit->setText(load_unit);
        ui->label_ch3_unit->setText(load_unit);
        ui->label_ch4_unit->setText(load_unit);
        parameters[current_frame].ch_unit  = 0;
        break;
    case 1:
        ui->label_ch2_unit->setText(length_unit);
        ui->label_ch3_unit->setText(length_unit);
        ui->label_ch4_unit->setText(length_unit);
        parameters[current_frame].ch_unit  = 1;
        break;
    case 2:
        ui->label_ch2_unit->setText("   ");
        ui->label_ch3_unit->setText("   ");
        ui->label_ch4_unit->setText("   ");
        parameters[current_frame].ch_unit  = 2;
        break;
    }
}
void PressApp::on_combo_scrRes_currentIndexChanged(int index)
{
    // olmayabilir bu
    switch (index) {
    case 0:

        break;
    case 1:
        ScreenWidth<1680;
        qDebug()<<Fontsize;
        break;
    }
}
void PressApp::on_comboBox_formatFile_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        format_type = _PDF;
        break;
    case 1:
        format_type = _TXT;
        break;
    }
}
// buttons :
void PressApp::on_pushButton_toApp_clicked()
{
    userDir = ui->lineEdit_user->text();
    ui->page_main->hide();
    ui->page_app->adjustSize();
    ui->page_app->show();
    resizer->stop();
    ui->label_calculated_area->setText("Alan :");
    if(!standard_change){
        ui->combo_testType ->setCurrentIndex(COMPRESSION);
        ui->combo_testType ->setDisabled(1);
        ui->comboBox_specimen -> clear();
        ui->comboBox_specimen ->addItem(cube, 0);
        ui->comboBox_specimen ->addItem(cylinder, 1);
        material_type = concrete;
    }
    setup_users();
    /////
    qDebug()<<"test_type"<<test_type<<test_type_name<<"\n";
    qDebug()<<"specimen_type"<<specimen_type<<specimen_name;
}
void PressApp::on_pushButton_connect_clicked()     //setup.gui : lineedit inputmask kaldır
{
    QString targetIP;

    if(ui->lineEdit_ip->text().isEmpty())
        targetIP = "Localhost";
    else
        targetIP = ui->lineEdit_ip->text();

    remote->setTarget(targetIP);
    periodic_response_handler(QByteArray());
    start_comm();

    ui->pushButton_connect->setDisabled(1);
    ui->pushButton_cutconnect->setEnabled(1);
    qDebug()<<"Connected to"<<targetIP;

}
void PressApp::on_pushButton_cutconnect_clicked()
{
    end_comm();
    _start_com = false;
    ui->pushButton_connect->setDisabled(0);
    ui->pushButton_cutconnect->setEnabled(0);
}
void PressApp::on_pushButton_saveFile_clicked()
{
    QString parameters_file;
    QFileDialog fileDialog(this,"PARAMETRELER");
    parameters_file = fileDialog.getSaveFileName(this, tr("Farklı Kaydet"), QDir::currentPath(), ".ini (*.ini)");
    saveParameters(parameters_file);
}
void PressApp::on_pushButton_openFile_clicked()
{
    QString parameters_file;
    QFileDialog fileDialog(this,"PARAMETRELER");
    parameters_file = fileDialog.getOpenFileName(this, tr("Dosya Aç"), QDir::currentPath(), ".ini (*.ini)");
    readParameters(parameters_file);
}
void PressApp::on_btn_okSpecimen_clicked()
{
// dimension'lar okunamayan/yazilamayan numunelerden dolayi eklendi
    calculate_area();
    if(test_type == COMPRESSION){
        switch (specimen_type) {
        case COMPRESSION_CUBE:
            dimensions = QString::number(ui->doubleSpinBox_specimen_cube_w->value())+" x "
                    + QString::number(ui->doubleSpinBox_specimen_cube_w->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_cube_w->value());
            break;
        case COMPRESSION_CYLINDER:
            dimensions = QString::number(ui->doubleSpinBox_specimen_cyl_d->value())+" x "
                    + QString::number(ui->doubleSpinBox_specimen_cyl_l->value());
            break;
        case COMPRESSION_MASONRY_UNIT:
            dimensions = QString::number(ui->doubleSpinBox_specimen_masonry_unit_l->value())+" x "
                    + QString::number(ui->doubleSpinBox_specimen_masonry_unit_w->value());
            break;
        }
    }
    else if(test_type == FLEXURAL){
        switch(specimen_type) {
        case FLEXURAL_BEAM3:
            dimensions = QString::number(ui->doubleSpinBox_specimen_beam3_l->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_beam3_b->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_beam3_d->value());
            break;
        case FLEXURAL_BEAM4:
            dimensions = QString::number(ui->doubleSpinBox_specimen_beam4_l->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_beam4_s->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_beam4_b->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_beam4_d->value());
            break;
        case FLEXURAL_KERB:
            dimensions = QString::number(ui->doubleSpinBox_specimen_kerb_a->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_kerb_b->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_kerb_c->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_kerb_d->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_kerb_l->value());
            break;
        case FLEXURAL_FLAGSTONE:
            dimensions = QString::number(ui->doubleSpinBox_specimen_flagstone_l->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_flagstone_s->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_flagstone_b->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_flagstone_d->value());
            break;
        }
    }
    else if(test_type == SPLIT_TENSILE){
        switch(specimen_type) {
        case SPLIT_TENSILE_CUBE:
            dimensions = QString::number(ui->doubleSpinBox_specimen_split_cube_w->value())+" x "
                    + QString::number(ui->doubleSpinBox_specimen_split_cube_w->value());
            break;
        case SPLIT_TENSILE_CYLINDER:
            dimensions = QString::number(ui->doubleSpinBox_specimen_split_cylinder_l->value())+" x "
                    + QString::number(ui->doubleSpinBox_specimen_split_cylinder_d->value());
            break;
        case SPLIT_TENSILE_PAVING_STONE:
            dimensions = QString::number(ui->doubleSpinBox_specimen_split_paving_stone_l->value()) + " x "
                    + QString::number(ui->doubleSpinBox_specimen_split_paving_stone_d->value());
            break;
        }
    }
}
void PressApp::on_btn_expand_clicked()
{
    dia_expand = new QDialog;
    QGridLayout *grid_expand = new QGridLayout;
    dia_expand->setLayout(grid_expand);
    grid_expand->addWidget(customPlot,0,0);
    dia_expand->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    dia_expand->setWindowTitle("Grafik");
    dia_expand->setMinimumSize(AppW,AppH);
    customPlot->setGeometry(0,0,dia_expand->width(),dia_expand->height());
    switch (dia_expand->exec()) {
    case QDialog::Accepted:
        break;
    case QDialog::Rejected:
        grid_plotArea->addWidget(customPlot,0,0);
        break;
    }
}
void PressApp::on_pushButton_startTest_clicked()
{
    show_graph = 0;
    global_running_timer.restart();
    if(_start_com) {
        _time->start();
        remote->set("main.start_test",QString::number(1));
        start_date = QDate::currentDate().toString("dd.MM.yyyy");   // added to print results
        start_time = QTime::currentTime().toString();               // added to print results
        ui->toolBox_app->setDisabled(1);
        ui->wdg_ReadWrite->setDisabled(1);
        ui->btn_expand->setDisabled(1);
        ui->pushButton_printPlot->setDisabled(1);
        ui->btn_expand->setStyleSheet("image: url(:/icons/fit_to_size_dis.png);");
        ui->pushButton_printPlot->setStyleSheet("image: url(:/icons/document_chart_dis.png);");
        ui->label_test_start_date->setText(start_date);
        ui->label_test_start_time->setText(start_time);
        if(current_test_no > 999) current_test_no = 0;
        start_date_filename_arg = QString("(%1-%2)").arg(start_date).arg(start_time);// "(" + start_date + " - " + start_time + ")";

// ////// GUI'den   ////////////////
        test_status  = TEST_RUNNING;
        auxthread->relay_start_stop = RELAY_ON;
        //auxthread->dac_value = dac_voltage_to_raw((double)0.1 * ui->spinBox_start_speed_percentage->value());
        if(!step_response_status)
            ui->pushButton_step_response->setText("Autotuning Durdur");
    }
}
void PressApp::on_pushButton_pauseTest_clicked()
{
    remote->set("main.pause_test",QString::number(1));
    ui->label_test_status->setText("Deney Durumu  : DURAKLADI");
    test_status = TEST_PAUSED;
}
void PressApp::on_pushButton_stopTest_clicked()
{
    _time->stop();
    remote->set("main.stop_test",QString::number(1));
  //  auxthread->test_finished = true;      // crash
}
void PressApp::on_pushButton_refreshTest_clicked()
{
    remote->set("main.refresh",QString::number(1));
    ui->label_time->setText("Zaman : 0.000");
    test_status = TEST_STOPPED;
    step_response_status = false;
    ui->pushButton_step_response->setText("Autotuning Başla");
    customPlot->graph(0)->data().data()->clear();
}
void PressApp::on_pushButton_write_to_device_clicked()
{
    QMessageBox msg;
    msg.setFont(QFont("Amerika", Fontsize-1, -1, true));
    if(_start_com){
        write_parameters_to_the_device();
        write_specimens_to_the_device();
        msg.setText("   Veriler cihaza aktarıldı   ");
        msg.setWindowTitle("Uyarı Kutusu");
        msg.setIconPixmap(QPixmap(":/icons/okay.png"));
        msg.exec();
    }
    else if (!_start_com){
        msg.setText("   Bağlı cihaz yok !    ");
        msg.setWindowTitle("Uyarı Kutusu");
        msg.setIconPixmap(QPixmap(":/icons/warning.png"));
        msg.exec();
    }
}
void PressApp::on_pushButton_read_from_device_clicked()
{
    QMessageBox msg;
    msg.setFont(QFont("Amerika", Fontsize-1 , -1, true));
    msg.setWindowTitle("Uyarı Kutusu");
    if(_start_com){
        read_parameters_from_the_device();
        read_specimens_from_the_device();

        //ui->label_current_test_no->setText(QString::number(real_time.test_no,10));    // TODO : bu sonuç şeyinde
        ui->label_test_status->setText(real_time.status);
        ui->label_calculated_area->setText("Alan : " + QString::number(real_time.area,'f',3) + QString(" %1%2").arg(length_unit,"2"));
        ui->label_load->setText(QString("Yük (%1) : ").arg(load_unit) + QString::number(real_time.load,'f',3));
        //ui->spinBox_load_invisible->setValue(real_time.load);
        ui->label_stress->setText(QString("Gerilme (%1) : ").arg(stress_unit) + QString::number(real_time.stress,'f',3));

        msg.setText("   Veriler cihazdan alındı   ");
        msg.setIconPixmap(QPixmap(":/icons/okay.png"));
        msg.exec();
    }
    else if (!_start_com){
        msg.setText("   Bağlı cihaz yok !   ");
        msg.setIconPixmap(QPixmap(":/icons/warning.png"));
        msg.exec();
    }
}
void PressApp::on_btn_saveSet_clicked()
{
    // tarih - dil -vs kaydet
    if(ui->combo_lang->currentIndex() == 0) lang_index = _TR;
    else if(ui->combo_lang->currentIndex() == 1) lang_index = _ENG;
}
void PressApp::on_pushButton_removeUser_clicked()
{
    int selected_index = ui->comboBox_user->currentIndex();
    QString selected_str = ui->comboBox_user->currentText();
    QMessageBox message;
    message.setWindowTitle("Uyarı Kutusu");
    message.setFont(QFont("Amerika", Fontsize-1 , -1, true));
    if(mouseevent){
        if(selected_str != ""){
            message.setText(QString("%1 kullanıcısına ait dosyalar silinecek. Emin misiniz ?").arg(selected_str));
            message.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
            message.setDefaultButton(QMessageBox::Cancel);
            message.setIconPixmap(QPixmap(":/icons/warning.png"));
            if(message.exec() == QMessageBox::Yes){
                removeDir(selected_str);
                str_users.removeOne(selected_str);
                ui->comboBox_user->removeItem(selected_index);
                QString it_user = str_users.join("\n");
                QFile users_file(QDir::currentPath() + "/user_list.txt");
                QTextStream line(&users_file);
                if(users_file.open(QIODevice::ReadWrite)){
                    users_file.resize(0);
                    line << it_user << "\n";
                }
                message.setText(QString("   %1 başarıyla kaldırıldı  ").arg(selected_str));
                message.setIconPixmap(QPixmap(":/icons/okay.png"));
                message.setStandardButtons(QMessageBox::Ok);
                message.exec();
                qDebug()<<selected_str<<" : user removed";
            }
            else;
            message.close();
        }
    }
    else
        authorization_event();
}
void PressApp::on_pushButton_load_factory_settings_clicked()
{
    QMessageBox message;
    message.setWindowTitle("Uyarı Kutusu");
    message.setFont(QFont("Amerika", Fontsize-1 , -1, true));
    message.setText(QString("Kayıtlı tüm veriler ve kullanıcılar sıfırlanacak. Emin misiniz ?"));
    message.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    message.setDefaultButton(QMessageBox::Cancel);
    message.setIconPixmap(QPixmap(":/icons/warning.png"));
    if(message.exec() == QMessageBox::Yes){
        // TODO : fabrika ayarı ne olması gerekiyorsa
    }
}
// toolbox :
void PressApp::on_toolBox_app_currentChanged(int tab)
{
     if (tab == TAB_GAIN || tab == TAB_CALIB || tab == TAB_PID)    // ui->wdg_adminSetting click ekle      // TODO
        authorization_event();
     if (mouseevent && tab == TAB_PID){         // TODO
         ui->pushButton_step_response->show();
         auxthread->relay_auto_man = RELAY_ON;
     }
     else
         ui->pushButton_step_response->hide();
}
// radio button:
void PressApp::assign_frame()
{
    if(ui->radioButton_frame1->isChecked()){
        ui->label_frame_type->setText("Gövde : 1");
        current_frame = FRAME1;
    }
    else if(ui->radioButton_frame2->isChecked()){
        ui->label_frame_type->setText("Gövde : 2");
        current_frame = FRAME2;
    }
    else{
        ui->label_frame_type->setText("Gövde : 1");
        ui->radioButton_frame1->setChecked(1);
        current_frame = FRAME1;
    }
    if(device_opening == false){
        gain_cal_send_timer->start();
        auxthread->command_silencer = true;
    }
}
void PressApp::assign_controlType()
{
    if (ui->radioButton_auto->isChecked()){
        control_mode = AUTO;
        auxthread->relay_auto_man = RELAY_ON;
    }
    else if (ui->radioButton_man->isChecked()){
        control_mode = MAN;
        auxthread->relay_auto_man = RELAY_OFF;
    }
}
void PressApp::assign_printMode()
{
    if(ui->radioButton_automatic_print_on->isChecked()){
        automatic_print = 1;
    }
    else if(ui->radioButton_automatic_print_off->isChecked()){
        automatic_print = 0;
    }
}
// spinbox :
void PressApp::pace_rate_handler_kn(){
    //qDebug()<<"pace rate handler";
    //if(real_time.area > 0){
        switch(unit_index){
        case KN_MM:     //1 Pa = 1 N/m2
            ui->doubleSpinBox_pace_rate_mpa->setValue((1000 * ui->doubleSpinBox_pace_rate->value()) / real_time.area);
            break;
        case LBF_IN:    //1 psi = 1 lbf/in2
            ui->doubleSpinBox_pace_rate_mpa->setValue((ui->doubleSpinBox_pace_rate->value()) / real_time.area);
            break;
        case KGF_CM:    //kgf/cm2
            ui->doubleSpinBox_pace_rate_mpa->setValue((ui->doubleSpinBox_pace_rate->value()) / real_time.area);
            break;
        }
    //}
    ui->label_pace_rate->setText(QString("Yükleme Hızı : %1 %2/s").arg(ui->doubleSpinBox_pace_rate->value()).arg(load_unit));
}
void PressApp::pace_rate_handler_mpa(){
    switch(unit_index){
    case KN_MM:     //1 Pa = 1 N/m2
        ui->doubleSpinBox_pace_rate->setValue((ui->doubleSpinBox_pace_rate_mpa->value() * (real_time.area)/1000.0));
        break;
    case LBF_IN:    //1 psi = 1 lbf/in2
        ui->doubleSpinBox_pace_rate->setValue(ui->doubleSpinBox_pace_rate_mpa->value() * real_time.area);
        break;
    case KGF_CM:    //kgf/cm2
        ui->doubleSpinBox_pace_rate->setValue(ui->doubleSpinBox_pace_rate_mpa->value() * real_time.area);
        break;
    }
    ui->label_pace_rate->setText(QString("Yükleme Hızı : %1 %2/s").arg(ui->doubleSpinBox_pace_rate->value()).arg(load_unit));
}
// Screen resolution :
int PressApp::GetScreenHRes(int s)
{
    auto screens = QGuiApplication::screens();
    qDebug() << "Ekran Listesi " << screens.count();
    int i = 0;
    if (screens.count() >= 1) i = s;
    auto SecScrenRect = screens[s]->geometry();
    QString Text = QString ("%1 Ekran Resolution "). arg(s);
    qDebug() << Text << SecScrenRect;
    auto px = screens[i]-> physicalDotsPerInchX();
    auto lx = screens[i]-> logicalDotsPerInchX();
    QRect rec = screens[i]->geometry();
    ScreenWidth = rec.width();
    ScreenHeight = rec.height();
    Text = QString ("%1 Ekran"). arg(s);
    qDebug() << Text << "Yatay:" << ScreenWidth << "Pixel  &  Dikey:" << ScreenHeight << "Pixel";
    qDebug() << Text << "Yatay Faktor:"  << "PX =" << px << "LX " << lx << "SR =" << lx/px;
    i = (1000*px)/lx;
    if (px >= lx) i = (1000*lx)/px;;
    return (i) ;
    return ((1000*lx)/px) ;
}
int PressApp::GetScreenVRes(int s)
{
    auto screens = QGuiApplication::screens();
    auto ly = screens[s]-> physicalDotsPerInchY();
    auto py = screens[s]-> logicalDotsPerInchY();
    QString Text = QString (" %1 Ekran Dikey Faktor ").arg(s);
    qDebug() << Text<< "PY =" << py << "LY " << ly << "SR =" << py / ly;
    int i = (1000*py)/ly;
    if (py >= ly) i = (1000*ly)/py;;
    return (i) ;
}

PressApp::~PressApp()
{
    delete ui;
}






