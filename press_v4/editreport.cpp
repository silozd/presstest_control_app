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

    //connect(ui->comboBox_template, SIGNAL(currentIndexChanged(int)), pressApp, SLOT(preview_results_file(QString)));
    //connect(ui->pushButton_save,   SIGNAL(clicked()), pressApp, SLOT());
}

EditReport::~EditReport()
{
    delete ui;
}



