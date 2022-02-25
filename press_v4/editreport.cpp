#include "editreport.h"
#include "ui_editreport.h"
#include "pressapp.h"

EditReport::EditReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditReport)
{
    ui->setupUi(this);
}
void EditReport::on_pushButton_save_clicked()       // todo
{
    switch (ui->comboBox_template->currentIndex()) {
    case 0:
        template_type == TEMPLATE_1;
        break;
    case 1:
        template_type == TEMPLATE_2;
        break;
    case 2:
        template_type == TEMPLATE_3;
        break;
    }
    this->close();
}
EditReport::~EditReport()
{
    delete ui;
}


