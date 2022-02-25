#include "pressapp.h"
#include "editreport.h"
#include <QtWebEngineWidgets>
#include <QWebEnginePage>
#include <QPdfWriter>
#include <poppler/qt5/poppler-qt5.h>

void PressApp::record_results(int no)
{
    test_no = no;
    ui->label_test_finish_time->setText(finish_time);
    ui->label_test_peak_stress->setText(QString::number(real_time.stress,'f',3));
    ui->label_test_peak_load->setText(QString::number(real_time.load,'f',3));
    ui->label_test_no->setText(QString::number(test_no));
    ui->label_current_test_no->setText(QString::number(real_time.test_no));
    ui->label_test_test_type->setText(test_type_name);
    ui->label_test_specimen_type->setText(specimen_name);
    ui->label_test_dimensions->setText(dimensions);
    ui->label_test_area->setText(QString::number(real_time.area) + QString(" %1").arg(length_unit) + "2");
    if(ui->label_test_paving_stone_fpl->isHidden() == false){
        ui->label_test_paving_stone_fpl->setText(QString::number((ui->label_test_peak_load->text().toDouble()) / ui->doubleSpinBox_specimen_split_paving_stone_l->value()));
    }
    // load and stress logs :
    QString path = QDir::currentPath() + "/" + "/data_logs";
    excel_file;
    QTextStream line(&excel_file);
    if(ui->radioButton_record_raw_data_on->isChecked()){        // TODO : load ve stress datalarını alt alta yazdır
        excel_file.setFileName(path + QString("/excel_log_%1").arg(current_test_no) + start_date_filename_arg + ".csv");
        excel_file.open(QIODevice::WriteOnly);

        QTextStream line(&excel_file);
        line << "Time (s)" << "," << QString("LOAD (%1)").arg(load_unit) << "," << QString("STRESS (%1)").arg(stress_unit) << "\n";
        line << ui->label_test_finish_time->text() << "," << QString::number(real_time.load,'f',3) << "," << QString::number(real_time.stress,'f',3) << "\n";
    }

//    QFile cal_file;
//    cal_file.setFileName(QString("test_results/calibration.txt"));
//    cal_file.open(QIODevice::WriteOnly);
//    QTextStream lines(&cal_file);

//    lines << "Viva Che!\n";
//    lines << "*****************************************************\n";
//    lines << "================ CALIBRATION VALUES =================\n";
//    lines << "*****************************************************\n";
//    lines << QString("Current Frame : FRAME %1 \n").arg(current_frame + 1);
//    lines << "*****************************************************\n";
//    lines << "FRAME 1 Calibration Values \n";
//    lines << "CHANNEL : 1\n";
//    lines << "Point Number : " << parameters[0].cal[0].point_no << "\n";
//    for(u8 i = 0 ; i < 8 ; i++){
//        lines << QString("RAW Value %1 :").arg(i) << parameters[0].cal[0].real_val[i] << "\t" << QString("Point Value %1 :").arg(i) << parameters[0].cal[0].assigned_val[i] << "\n";
//    }
//    lines << "CHANNEL : 2\n";
//    lines << "Point Number : " << parameters[0].cal[1].point_no << "\n";
//    for(u8 i = 0 ; i < 8 ; i++){
//        lines << QString("RAW Value %1 :").arg(i) << parameters[0].cal[1].real_val[i] << "\t" << QString("Point Value %1 :").arg(i) << parameters[0].cal[1].assigned_val[i] << "\n";
//    }
//    lines << "CHANNEL : 3\n";
//    lines << "Point Number : " << parameters[0].cal[2].point_no << "\n";
//    for(u8 i = 0 ; i < 8 ; i++){
//        lines << QString("RAW Value %1 :").arg(i) << parameters[0].cal[2].real_val[i] << "\t" << QString("Point Value %1 :").arg(i) << parameters[0].cal[2].assigned_val[i] << "\n";
//    }
//    lines << "CHANNEL : 4\n";
//    lines << "Point Number : " << parameters[0].cal[3].point_no << "\n";
//    for(u8 i = 0 ; i < 8 ; i++){
//        lines << QString("RAW Value %1 :").arg(i) << parameters[0].cal[3].real_val[i] << "\t" << QString("Point Value %1 :").arg(i) << parameters[0].cal[3].assigned_val[i] << "\n";
//    }
//    lines << "*****************************************************\n";
//    lines << "FRAME 2 Calibration Values \n";
//    lines << "CHANNEL : 1\n";
//    lines << "Point Number : " << parameters[1].cal[0].point_no << "\n";
//    for(u8 i = 0 ; i < 8 ; i++){
//        lines << QString("RAW Value %1 :").arg(i) << parameters[1].cal[0].real_val[i] << "\t" << QString("Point Value %1 :").arg(i) << parameters[1].cal[0].assigned_val[i] << "\n";
//    }
//    lines << "CHANNEL : 2\n";
//    lines << "Point Number : " << parameters[1].cal[1].point_no << "\n";
//    for(u8 i = 0 ; i < 8 ; i++){
//        lines << QString("RAW Value %1 :").arg(i) << parameters[1].cal[1].real_val[i] << "\t" << QString("Point Value %1 :").arg(i) << parameters[1].cal[1].assigned_val[i] << "\n";
//    }
//    lines << "CHANNEL : 3\n";
//    lines << "Point Number : " << parameters[1].cal[2].point_no << "\n";
//    for(u8 i = 0 ; i < 8 ; i++){
//        lines << QString("RAW Value %1 :").arg(i) << parameters[1].cal[2].real_val[i] << "\t" << QString("Point Value %1 :").arg(i) << parameters[1].cal[2].assigned_val[i] << "\n";
//    }
//    lines << "CHANNEL : 4\n";
//    lines << "Point Number : " << parameters[1].cal[3].point_no << "\n";
//    for(u8 i = 0 ; i < 8 ; i++){
//        lines << QString("RAW Value %1 :").arg(i) << parameters[1].cal[3].real_val[i] << "\t" << QString("Point Value %1 :").arg(i) << parameters[1].cal[3].assigned_val[i] << "\n";
//    }
//    cal_file.close();

}
void PressApp::on_pushButton_saveResults_clicked()      /// Save results
{
    results_saved = true;
    custom_file_loaded = false;
    QPrinter printer(QPrinter::HighResolution);
    QString fileName = ui->lineEdit_fileName->text();
    QString path;
    QDir dir;
    dir.mkdir(userDir);
    if(!userDir.isEmpty())
        path = QDir::currentPath() + "/" + userDir;    // debug folder
    else
        path = QDir::currentPath();

    switch (format_type) {
    case _PDF:{
        ui->pushButton_editFile->setEnabled(1);
        ui->pushButton_editFile->setStyleSheet("color: rgb(0,20,255);");
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPageSize(QPageSize(QPageSize::A4));
        printer.setOrientation(QPrinter::Portrait);
        printer.setPaperSize(QPrinter::A4);
        printer.setPageSize(QPrinter::A4);
        printer.setPageMargins(15,15,15,15,QPrinter::Millimeter);
        if(ui->lineEdit_fileName->text().isEmpty()){
            res_fileName = QString("/test_%1").arg(test_no) + start_date_filename_arg;
            res_fileName.append(".pdf");
            printer.setOutputFileName(path + res_fileName);
        } else {
            res_fileName = QString("/%1").arg(fileName);
            res_fileName.append(".pdf");
            printer.setOutputFileName(path + res_fileName);
        }
//        //ui->btn_openPrintView->setEnabled(1);     // TODO
        qDebug() << "Page px :" << printer.pageRect() << printer.paperRect();
        qDebug() << "Page mm :" << printer.pageRect(QPrinter::Millimeter) << printer.paperRect(QPrinter::Millimeter);
        qreal left, top, right, bottom;
        printer.getPageMargins(&left, &top, &right, &bottom, QPrinter::DevicePixel);
        qDebug() << "Marges px :" << left << top << right << bottom;
        printer.getPageMargins(&left, &top, &right, &bottom, QPrinter::Millimeter);
        qDebug() << "Marges mm :" << left << top << right << bottom;

        // TEMPLATE 1:      /////////////////////////////
        QPainter painter(&printer);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform); painter.begin(&printer);
        QFont police(editReport->ui->comboBox_3->currentText(),30);
        QFontMetrics fontmetric = painter.fontMetrics();
        int h_label = fontmetric.width("TEST RESULTS");

        int y = printer.pageRect().y();
        int x = y;
        painter.setPen(Qt::black);
        painter.drawText(printer.width()/2 - h_label/2, 50, "TEST RESULTS");
        painter.drawText( x, 2*y, "Test Start Date :     " + ui->label_test_start_date->text() + "\n");
        painter.drawText( x, 3*y, "Test No :     " + ui->label_test_no->text() + "\n");
        painter.drawText( x, 4*y, "Line 1 :     " + ui->lineEdit_1->text() + "\n");
        painter.drawText( x, 5*y, "Test Start Date :     " + ui->label_test_start_date->text() + "\n");
        painter.drawText( x, 6*y, "Test Start Time :     " + ui->label_test_start_time->text() + "\n");
        painter.drawText( x, 7*y, "Test Finish Time :     " + ui->label_test_finish_time->text() + "\n");
        painter.drawText( x, 8*y, "Test Type :     " + ui->label_test_test_type->text() + "\n");
        painter.drawText( x, 9*y, "Specimen :     " + ui->label_test_specimen_type->text() + "\n");
        painter.drawText( x, 10*y, QString("Dimensions (%1) :     ").arg(length_unit) + ui->label_test_dimensions->text() + "\n");
        painter.drawText( x, 11*y, QString("Area (%1%2) :     ").arg(length_unit,"2") + ui->label_test_area->text() + "\n");
        painter.drawText( x, 12*y, QString("Peak Load (%1) :     ").arg(load_unit) + ui->label_test_peak_load->text() + "\n");
        painter.drawText( x, 13*y, QString("Peak Stress (%1) :     ").arg(stress_unit) + ui->label_test_peak_stress->text() + "\n");

        printer.newPage();
        const QImage image(QDir::currentPath()+"/22_şubat_deney_grafiği.pdf");
        const QPoint imageCoordinates(15,0);

        const QImage image1(QDir::currentPath()+"/22_şubat_deneyi.pdf");
        const QPoint imageCoordinates1(9000,0);

        painter.drawImage(imageCoordinates, image);
        painter.drawImage(imageCoordinates1, image1);
        //pdfWriter.newPage();

        painter.drawText(0, y*3, QString::fromUtf8("Ligne 2"));

        QPixmap pix(ui->wdg_plotArea->size());
        QPainter painter1(&pix);
        ui->wdg_plotArea->render(&painter);
        painter.end();

        painter1.begin(&printer);
        double xscale = printer.pageRect().width() / double(pix.width());
        double yscale = printer.pageRect().height() / double(pix.height());
        double scale = qMin(xscale, yscale);
        painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
                       printer.paperRect().y()*4 + printer.pageRect().height() / 2);
        painter.scale(scale, scale);
        painter.translate(-ui->wdg_plotArea->width() /2, -ui->wdg_plotArea->height() /2);
        painter.drawPixmap(0, 0, pix);
        painter1.end();
        break;
    }
    case _TXT:
        QFile test_res;
        if(ui->lineEdit_fileName->text().isEmpty())
            res_fileName = QString("/test_%1").arg(test_no) + start_date_filename_arg;
        else
            res_fileName = QString("/%1").arg(fileName);
        res_fileName.append(".txt");
        test_res.setFileName(path + res_fileName);
        test_res.open(QIODevice::WriteOnly);
        QTextStream lines(&test_res);
        lines.setCodec("UTF-8");
        lines << QString("\nTEST RESULTS \n");
        lines << QString("Line_1 :") << ui->lineEdit_1->text() << "\n";
        lines << QString("Line_2 :") << ui->lineEdit_2->text() << "\n";
    //    lines << trUtf8("User :") << ui->lineEdit_3->text() << "\n";      // OPEN
        lines << QString("Test_No :") << ui->label_test_no->text() << "\n";
        lines << QString("Test_Start_Date :") << ui->label_test_start_date->text() << "\n";
        lines << QString("Test_Start_Time :") << ui->label_test_start_time->text() << "\n";
        lines << QString("Test_Finish_Time :") << ui->label_test_finish_time->text() << "\n";
        lines << QString("Test_Type :") << ui->label_test_test_type->text() << "\n";
        lines << QString("Specimen :") << ui->label_test_specimen_type->text() << "\n";
        lines << QString("Dimensions_(%1) :").arg(length_unit) << ui->label_test_dimensions->text() << "\n";
        lines << QString("Area_(%1%2) :").arg(length_unit,"2") << ui->label_test_area->text() << "\n";
        lines << QString("Peak_Load_(%1) :").arg(load_unit) << ui->label_test_peak_load->text() << "\n";
        lines << QString("Peak_Stress_(%1) :").arg(stress_unit) << ui->label_test_peak_stress->text() << "\n";
        if(ui->label_test_paving_stone_fpl->isHidden() == false){
            lines << QString("P/L_(%1/%2)  :").arg(load_unit,length_unit) << ui->label_test_paving_stone_fpl->text() << "\n";
        }
        test_res.close();
        ui->pushButton_editFile->setDisabled(1);
        ui->pushButton_editFile->setStyleSheet("color: rgb(150,180,255)");
        break;
    }
    QMessageBox message;
    message.setWindowTitle("Uyarı Kutusu");
    message.setFont(QFont("Amerika", Fontsize-1 , -1, true));
    message.setText(QString("Sonuçlar '%1' altına kaydedildi.").arg(path));
    message.setIconPixmap(QPixmap(":/icons/okay.png"));
    message.exec();

    ui->label_nameOfFile->setText(path + res_fileName);
    qDebug()<<"Results saved as"<<res_fileName;
}
void PressApp::preview_results_file(QString fileName)
{
    QString path = QDir::currentPath() + "/" + userDir;
    if(custom_file_loaded)
        fileName = custom_path;
    else if(results_saved)
        fileName = path + fileName;

    ui->label_nameOfFile->setText(fileName);

    Poppler::Document* doc = Poppler::Document::load(fileName);
    Poppler::Page* pdfPage = doc->page(0);  // Document starts at page 0
    QImage image2 = pdfPage->renderToImage(72.0,72.0,-1,-1,editReport->ui->imageLabel->width(),editReport->ui->imageLabel->height());

    if (!doc || doc->isLocked()) {
      delete doc;
      return;
    }
    if (doc == 0) return;
    if (pdfPage == 0) return;
    if (image2.isNull()) return;

    editReport->ui->imageLabel->setPixmap(QPixmap::fromImage(image2));
    delete pdfPage;
    delete doc;
}
void PressApp::on_pushButton_editFile_clicked()
{
    QString path = QDir::currentPath() + "/" + userDir;
    if(!results_saved && !custom_file_loaded){
        editReport->ui->pushButton_save->setDisabled(1);
        editReport->setWindowTitle("Gelişmiş Düzenleme");
    } else{
        editReport->ui->pushButton_save->setEnabled(1);
        if(results_saved){
            editReport->setWindowTitle(path+res_fileName);
            preview_results_file(res_fileName);
        }
        else if (custom_file_loaded){
            editReport->setWindowTitle(custom_path);
            preview_results_file(custom_path);
        }
    }
    editReport->exec();
}
void PressApp::on_pushButton_openFile_view_clicked()
{
    results_saved = false;
    QString filters(".pdf files (*.pdf);; .txt files (*.txt);; All files (*.*)");
    QString defaultFilter(".pdf files (*.pdf)");
    custom_path = QFileDialog::getOpenFileName(this, tr("Dosya Aç"), QDir::currentPath(),
                                                filters, &defaultFilter);
    if(QFileDialog::Accepted){
        custom_file_loaded = true;
        if(!custom_path.endsWith(".pdf")){
            ui->pushButton_editFile->setDisabled(1);
            ui->pushButton_editFile->setStyleSheet("color: rgb(150,180,255)");
        } else{
            ui->pushButton_editFile->setEnabled(1);
            ui->pushButton_editFile->setStyleSheet("color: rgb(0,20,255)");
        }
    }
    else custom_file_loaded = false;

    ui->label_nameOfFile->setText(custom_path);
    res_fileName = custom_path;
    qDebug()<<"custom_path :"<<res_fileName;
}
void PressApp::on_pushButton_printResults_clicked()     /// OPEN PDF FILE :
{
    if(results_saved)
        QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath() + "/" + userDir + res_fileName));
    else if(custom_file_loaded)
        QDesktopServices::openUrl(QUrl::fromLocalFile(custom_path));
    else {
        QMessageBox msg;
        msg.setFont(QFont("Amerika", Fontsize-1, -1, true));
        msg.setText("   Yazdırılacak dosya kaydedilmedi / seçilmedi !    ");
        msg.setWindowTitle("Uyarı Kutusu");
        msg.setIconPixmap(QPixmap(":/icons/warning.png"));
        msg.exec();
    }
}
void PressApp::on_loadFinished(bool ok)     // TODO : bu deneme
{
    qDebug()<<"on_loadFinished";
    if (ok){
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPageSize(QPageSize(QPageSize::A4));
        printer.setPageOrientation(QPageLayout::Portrait);
        printer.setColorMode(QPrinter::GrayScale);
        printer.setOutputFileName(QDir::currentPath() + "/" + userDir + res_fileName);

        static_cast<QWebEngineView *>(sender())->render(&printer);
    }
}

//    //  /// WEB ENGINE VIEW
//    QFile file("/home/sila/Desktop/press_v3/build-press_v3-Desktop-Debug/sıla/sonuc.pdf");
//    QString str;
//    if (file.open(QFile::ReadOnly | QFile::Text))
//    {
//        str.append(file.readAll());
//        ui->webEngineView->load(QUrl("https://google.com"));
//        file.close();
//    }
//    connect(ui->webEngineView, &QWebEngineView::loadFinished, this, &PressApp::on_loadFinished);

