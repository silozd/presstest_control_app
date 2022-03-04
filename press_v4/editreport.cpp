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
    //ui->comboBox_template->setCurrentIndex(0);  // TODO : 0 yap
    templ_type=1; // TODO : 0 yap
}
void EditReport::on_comboBox_template_currentIndexChanged(int index)
{
// Display template form by image:
    switch (index) {
    case 0: ui->imageLabel->setStyleSheet("border-image: url(:/template_1.png);");//setPixmap(QPixmap::fromImage(img));
        break;
    case 1: ui->imageLabel->setStyleSheet("border-image: url(:/template_2.png);");
        break;
    case 2: ui->imageLabel->setStyleSheet("border-image: url(:/template_1.png);");
        break;
    }

//// FOR PREVIEW PDF FILE :
//    QString file = QDir::currentPath() + "/template_1.pdf";
//    Poppler::Document* pre_doc = Poppler::Document::load(file);
//    Poppler::Page* pdfPage = pre_doc->page(0);  // Document starts at page 0
//    QImage img;
//    switch (index) {
//    case 0:
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

//        ui->imageLabel->setPixmap(QPixmap::fromImage(img));
//        //
//        break;
//    case 1:
//        img = pdfPage->renderToImage(72.0,72.0,-1,-1,ui->imageLabel->width(),ui->imageLabel->height());
//        //
//        if (!pre_doc || pre_doc->isLocked()) {
//          delete pre_doc;
//          return;
//        }
//        if (pre_doc == 0) return;
//        if (pdfPage == 0) return;
//        if (img.isNull()) return;

//        ui->imageLabel->setPixmap(QPixmap::fromImage(img));
//        break;
//    case 2:
//        img = pdfPage->renderToImage(72.0,72.0,-1,-1,ui->imageLabel->width(),ui->imageLabel->height());
//        //
//        if (!pre_doc || pre_doc->isLocked()) {
//          delete pre_doc;
//          return;
//        }
//        if (pre_doc == 0) return;
//        if (pdfPage == 0) return;
//        if (img.isNull()) return;

//        ui->imageLabel->setPixmap(QPixmap::fromImage(img));
//        break;
//    }
//    delete pdfPage;
}
void EditReport::on_pushButton_saveEdit_clicked()
{
    int templ = ui->comboBox_template->currentIndex();
    switch (templ) {
    case 0: templ_type = 0; break;
    case 1: templ_type = 1; break;
    case 2: templ_type = 2; break;
    }

    this->close();
    qDebug()<<templ_type;
}

EditReport::~EditReport()
{
    delete ui;
}

