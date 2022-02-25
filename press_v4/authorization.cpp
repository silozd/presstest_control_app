#include "pressapp.h"
#include "ui_pressapp.h"

QString path = QDir::currentPath();
QFile file(path + "/get_password.txt");
QTextStream  in(&file);
QString str;
QRegularExpression rx("(^([0-9]{4})$)");
QValidator *validator = new QRegularExpressionValidator(rx);

void PressApp::get_password()   /// to Keep password
{
    ui->lineEdit_oldPsw -> setMaxLength(4);
    ui->lineEdit_oldPsw -> setValidator(validator);
    ui->lineEdit_newPsw -> setValidator(validator);
    ui->lineEdit_oldPsw -> setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->lineEdit_newPsw -> setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->lineEdit_oldPsw -> setClearButtonEnabled(true);
    ui->lineEdit_newPsw -> setClearButtonEnabled(true);
    ui->lineEdit_oldPsw -> setPlaceholderText("Eski şifre");
    ui->lineEdit_newPsw -> setPlaceholderText("Yeni şifre");

    file.open(QIODevice::ReadOnly|QIODevice::Text);
    str = in.readLine();
    file.close();
    qDebug()<<"SIFRE"<<str;
//    qDebug()<<"password path :"<<QString(path);

    connect(this->btn_newPsw, SIGNAL(clicked()),this,SLOT(authorize()));
}
void PressApp::authorization_event() /// Authorization for calib, pid, gain tabs
{
    if(!mouseevent){
        lbl_psw  -> setStyleSheet("font: bold;");
        password -> setValidator(validator);
        password -> setEchoMode(QLineEdit::PasswordEchoOnEdit);
        password -> setClearButtonEnabled(true);
        grid_dialogPsw -> addWidget(lbl_psw,0,0);
        grid_dialogPsw -> addWidget(password,1,0);
        grid_dialogPsw -> addWidget(btn_newPsw,2,0);
        dialog_psw     -> setLayout(grid_dialogPsw);
        dialog_psw     -> setWindowTitle("Erişim Ekranı");
        dialog_psw     -> setWindowIcon(QIcon(":/icons/lock.png"));
        dialog_psw     -> resize(TabW,TabH);
        dialog_psw     -> exec();
    }
}
void PressApp::authorize()
{
    QMessageBox message;
    message.setFont(QFont("Amerika", Fontsize-1, -1, true));
    message.setWindowTitle("Uyarı Kutusu");

    qDebug()<<"autho";
    if(password->text() == str){
        mouseevent = true;
        ui->page_calib->setEnabled(1);
        ui->page_pid->setEnabled(1);
        ui->page_gain->setEnabled(1);
        ui->wdg_adminSetting->setEnabled(1);
        QPixmap unlock(":/icons/unlock.png");
        message.setIconPixmap(QPixmap(unlock));
        message.setText("Erişime izin verildi.");
        message.exec();
        dialog_psw->close();
    }
    else if(password->text() != str){
        mouseevent = false;
        QPixmap lock(":/icons/lock.png");
        message.setIconPixmap(QPixmap(lock));
        message.setText("Geçersiz şifre ! Yeniden deneyin.");
        message.exec();
    }
}
void PressApp::on_pushButton_pswSave_clicked()  /// Save new password
{
    get_password();
    QMessageBox message;
    message.setFont(QFont("Amerika", Fontsize-1 , -1, true));
    message.setWindowTitle("Uyarı Kutusu");

    if (ui->lineEdit_oldPsw->text() == str){
        if (ui->lineEdit_newPsw->validator() == validator && ui->lineEdit_newPsw->text() != ui->lineEdit_oldPsw->text()){
            str.clear();
            if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                str.append(QString(ui->lineEdit_newPsw->text()));
                in << str;
                file.close();
            }
            message.setIconPixmap(QPixmap(":/icons/okay.png"));
            message.setText("Şifre başarıyla değiştirildi.");
            message.exec();
        }
        else if(ui->lineEdit_newPsw->text() == ui->lineEdit_oldPsw->text()){
            message.setIconPixmap(QPixmap(":/icons/warning.png"));
            message.setText("Geçerli bir şifre girin !");
            message.exec();
        }
//        qDebug()<<"yeni şifre :"<<str;
//        qDebug()<<"yeni şifre :"<<newPswd->text();
    }
    else if(ui->lineEdit_oldPsw->text() != str){
        message.setIconPixmap(QPixmap(":/icons/warning.png"));
        message.setText("Eski şifre yanlış.\nYeniden deneyin !");
        message.exec();
    }
    ui->lineEdit_oldPsw -> clear();
    ui->lineEdit_newPsw -> clear();
}
