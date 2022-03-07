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
    templ_type=0;
    ui->comboBox_langEdit->addItem("TR",  0);
    ui->comboBox_langEdit->addItem("ENG", 1);
    lang_file=0;

    ui->fontComboBox->setCurrentFont(QFont("Times New Roman"));
}
void EditReport::on_comboBox_template_currentIndexChanged(int index)
{
// Display template form by image:
    switch (index) {
    case 0: ui->imageLabel->setStyleSheet("border-image: url(:/temp_1.png);");//setPixmap(QPixmap::fromImage(img));
        break;
    case 1: ui->imageLabel->setStyleSheet("border-image: url(:/temp_2.png);");
        break;
    case 2: ui->imageLabel->setStyleSheet("border-image: url(:/temp_3.png);");
        break;
    }

//// FOR PREVIEW PDF FILE :
//    switch (index) {
//    case 0:{
//        QString file = QDir::currentPath() + "/template_1.pdf";
//        Poppler::Document* pre_doc = Poppler::Document::load(file);
//        Poppler::Page* pdfPage = pre_doc->page(0);  // Document starts at page 0
//        QImage img;
//        //pressApp->preview_template(0);
//        img = pdfPage->renderToImage(72.0,72.0,-1,-1,ui->imageLabel->width(),ui->imageLabel->height());
//        //
//        if (!pre_doc || pre_doc->isLocked()) {
//          delete pre_doc;
//          return;
//        }
//        if (pre_doc == 0) return;
//        if (pdfPage == 0) return;
//        if (img.isNull()) return;

//        delete pdfPage;
//        ui->imageLabel->setPixmap(QPixmap::fromImage(img));
//        //
//        break;}
//    case 1:{
//        QString file = QDir::currentPath() + "/template_2.pdf";
//        Poppler::Document* pre_doc = Poppler::Document::load(file);
//        Poppler::Page* pdfPage = pre_doc->page(0);  // Document starts at page 0
//        QImage img;img = pdfPage->renderToImage(72.0,72.0,-1,-1,ui->imageLabel->width(),ui->imageLabel->height());
//        //
//        if (!pre_doc || pre_doc->isLocked()) {
//          delete pre_doc;
//          return;
//        }
//        if (pre_doc == 0) return;
//        if (pdfPage == 0) return;
//        if (img.isNull()) return;

//        delete pdfPage;
//        ui->imageLabel->setPixmap(QPixmap::fromImage(img));
//        break;}
//    case 2:{
//        QString file = QDir::currentPath() + "/template_3.pdf";
//        Poppler::Document* pre_doc = Poppler::Document::load(file);
//        Poppler::Page* pdfPage = pre_doc->page(0);  // Document starts at page 0
//        QImage img;
//        img = pdfPage->renderToImage(72.0,72.0,-1,-1,ui->imageLabel->width(),ui->imageLabel->height());
//        //
//        if (!pre_doc || pre_doc->isLocked()) {
//          delete pre_doc;
//          return;
//        }
//        if (pre_doc == 0) return;
//        if (pdfPage == 0) return;
//        if (img.isNull()) return;

//        delete pdfPage;
//        ui->imageLabel->setPixmap(QPixmap::fromImage(img));
//        break;}
//    }
}
void EditReport::on_comboBox_langEdit_currentIndexChanged(int index)
{
    int _template = ui->comboBox_template->currentIndex();
    switch (index) {
    case 0:
        if(_template == 0)
            ui->imageLabel->setStyleSheet("border-image: url(:/temp_1.png);");
        if(_template == 1)
            ui->imageLabel->setStyleSheet("border-image: url(:/temp_2.png);");
        break;
    case 1:
        if(_template == 0)
            ui->imageLabel->setStyleSheet("border-image: url(:/temp_1_eng.png);");
        if(_template == 1)
            ui->imageLabel->setStyleSheet("border-image: url(:/temp_2_eng.png);");
        break;
    }
}
void EditReport::on_pushButton_saveEdit_clicked()
{
    int templ = ui->comboBox_template->currentIndex();
    switch (templ) {
    case 0: templ_type = 0; break;
    case 1: templ_type = 1; break;
    }
    int lang = ui->comboBox_langEdit->currentIndex();
    switch (lang) {
    case 0: lang_file = 0; break;
    case 1: lang_file = 1; break;
    }
    this->close();
    qDebug()<<templ_type;
}

EditReport::~EditReport()
{
    delete ui;
}

