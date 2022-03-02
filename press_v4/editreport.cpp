#include "editreport.h"
#include "ui_editreport.h"
#include "pressapp.h"
#include <poppler/qt5/poppler-qt5.h>

EditReport::EditReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditReport)
{
    ui->setupUi(this);

    ui->comboBox_template->addItem("Template 1", 0);
    ui->comboBox_template->addItem("Template 2", 1);
    ui->comboBox_template->addItem("Template 3", 2);

    connect(ui->comboBox_template, SIGNAL(currentIndexChanged(int)), pressApp, SLOT(preview_results_file(QString)));
}
void EditReport::on_pushButton_save_clicked()       // todo
{
    switch (ui->comboBox_template->currentIndex()) {
    case 0:
        template_type == 0;
        break;
    case 1:
        template_type == 1;
        break;
    case 2:
        template_type == 2;
        break;
    }
    //this->close();
    qDebug()<<template_type ;
}

EditReport::~EditReport()
{
    delete ui;
}



