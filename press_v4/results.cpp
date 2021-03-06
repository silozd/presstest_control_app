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
    ui->label_specAge->setText(QString::number(ui->spinBox_specAge->value()));
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
        excel_file.setFileName(path + QString("/excel_log_%1").arg(test_no) + start_date_filename_arg + ".csv");
        excel_file.open(QIODevice::WriteOnly);

        QTextStream line(&excel_file);      // TODO dil ayarı
        line << "CHANNEL" << "," << QString("LOAD (%1)").arg(load_unit) << "," << QString("STRESS (%1)").arg(stress_unit) << "," << "Time (s)" << "\n" ;
        line << "Channel 1 " << "," << QString::number(real_time.load,'f',3) << "," << QString::number(real_time.stress,'f',3) << "," << ui->label_test_finish_time->text() <<"\n";
        line << "FRAME 1 Calibration Values" << "," << "Point Number" << "," ;
        for(u8 i = 0 ; i < 8 ; i++)
            line << QString("RAW Value %1").arg(i) << "," << QString("Point Value %1").arg(i) << ",";
        line << "\n" << "Channel 1" << "," << parameters[0].cal[0].point_no << ",";
        for(u8 i = 0 ; i < 8 ; i++)
            line << parameters[0].cal[0].real_val[i] << "," << parameters[0].cal[0].assigned_val[i] << ",";
        line << "\n" << "Channel 2" << "," << parameters[0].cal[1].point_no << ",";
        for(u8 i = 0 ; i < 8 ; i++)
            line << parameters[0].cal[1].real_val[i] << "," << parameters[0].cal[1].assigned_val[i] << ",";
        line << "\n" << "Channel 3" << "," << parameters[0].cal[2].point_no << "," ;
        for(u8 i = 0 ; i < 8 ; i++)
            line << parameters[0].cal[2].real_val[i] << "," << parameters[0].cal[2].assigned_val[i] << ",";
        line << "\n" << "Channel 4" << "," << parameters[0].cal[3].point_no << "," ;
        for(u8 i = 0 ; i < 8 ; i++)
            line << parameters[0].cal[3].real_val[i] << "," << parameters[0].cal[3].assigned_val[i] << ",";
        line << "\n";
        line << "FRAME 2 Calibration Values" << "\n" ;
        line << "Channel 1" << "," << parameters[0].cal[0].point_no << ",";
        for(u8 i = 0 ; i < 8 ; i++)
            line << parameters[0].cal[0].real_val[i] << "," << parameters[0].cal[0].assigned_val[i] << ",";
        line << "\n" << "Channel 2" << "," << parameters[0].cal[1].point_no << ",";
        for(u8 i = 0 ; i < 8 ; i++)
            line << parameters[0].cal[1].real_val[i] << "," << parameters[0].cal[1].assigned_val[i] << ",";
        line << "\n" << "Channel 3" << "," << parameters[0].cal[2].point_no << "," ;
        for(u8 i = 0 ; i < 8 ; i++)
            line << parameters[0].cal[2].real_val[i] << "," << parameters[0].cal[2].assigned_val[i] << ",";
        line << "\n" << "Channel 4" << "," << parameters[0].cal[3].point_no << "," ;
        for(u8 i = 0 ; i < 8 ; i++)
            line << parameters[0].cal[3].real_val[i] << "," << parameters[0].cal[3].assigned_val[i] << ",";
    }
}
void PressApp::on_pushButton_saveResults_clicked()      /// Save results
{
    results_saved = true;
    custom_file_loaded = false;
    ui->pushButton_quitFile->setEnabled(1);
    ui->pushButton_editFile->setDisabled(1);
    ui->pushButton_editFile->setStyleSheet("color: rgb(150,180,255)");
    QPrinter printer(QPrinter::HighResolution);
    pdf_fileName = ui->lineEdit_fileName->text();
    QDir dir;
    QString path;
    dir.mkdir(userDir);
    if(!userDir.isEmpty())
        pdf_path = QDir::currentPath() + "/" + userDir;    // debug folder
    else
        pdf_path = QDir::currentPath();

    switch (format_type) {
    case _PDF:{
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPageSize(QPageSize(QPageSize::A4));
        printer.setOrientation(QPrinter::Portrait);
        printer.setPaperSize(QPrinter::A4);
        printer.setPageSize(QPrinter::A4);
        printer.setPageMargins(15,15,15,15,QPrinter::Millimeter);
        if(ui->lineEdit_fileName->text().isEmpty()){
            res_fileName = QString("/test_%1").arg(test_no) + start_date_filename_arg;
            res_fileName.append(".pdf");
            printer.setOutputFileName(pdf_path + res_fileName);
        } else {
            res_fileName = QString("/%1").arg(pdf_fileName);
            res_fileName.append(".pdf");
            printer.setOutputFileName(pdf_path + res_fileName);
        }
        qDebug()<<pdf_path;
//        //ui->btn_openPrintView->setEnabled(1);     // TODO
        qDebug() << "Page px :" << printer.pageRect() << printer.paperRect();
        qDebug() << "Page mm :" << printer.pageRect(QPrinter::Millimeter) << printer.paperRect(QPrinter::Millimeter);
        qreal left, top, right, bottom;
        printer.getPageMargins(&left, &top, &right, &bottom, QPrinter::DevicePixel);
        printer.getPageMargins(&left, &top, &right, &bottom, QPrinter::Millimeter);
        qDebug() << "Marges px :" << left << top << right << bottom;
        qDebug() << "Marges mm :" << left << top << right << bottom;

        QPaintEvent *event;
        //QSlider::paintEvent(event);
        QPainter painter(&printer);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform); painter.begin(&printer);
        QFontMetrics fontmetric = painter.fontMetrics();
        fontmetric = painter.fontMetrics();
        header_report = ui->lineEdit_company->text();                    // TODO
        testName_report = ui->lineEdit_testName->text();     // TODO
        if(editReport->lang_file == 1) {
            if(header_report.isEmpty()) header_report = "COMPANY";
            if(testName_report.isEmpty()) testName_report = "Test Name";
            if (material_type == concrete) material_type = "CONCRETE";
            else if (material_type == concrete_floor) material_type = "CONCRETE FLOOR";
            else if (material_type == cement) material_type = "CEMENT";
            if (specimen_name == cube) specimen_name= "Cube";
            else if (specimen_name == cylinder) specimen_name= "Cylinder";
            else if (specimen_name == masonry) specimen_name = "Masonry";
            else if (specimen_name == beam3) specimen_name= "Beam 3P";
            else if (specimen_name == beam4) specimen_name= "Beam 4P";
            else if (specimen_name == kerb) specimen_name = "Kerb";
            else if (specimen_name == pavingstone) specimen_name= "Paving Stone";
            else if (specimen_name == flagstone) specimen_name= "Flagstone";
            if(test_type_name == compress) test_type_name = "Compression";
            else if(test_type_name == flexural) test_type_name = "Flexural";
            if(test_type_name == splittens) test_type_name = "Split Tensile";
        }
        else if(editReport->lang_file == 0){
            if(header_report.isEmpty()) header_report = "FİRMA";
            if(testName_report.isEmpty()) testName_report = "Deney Adı";
            if (material_type == "CONCRETE") material_type = "BETON";
            else if (material_type == "CONCRETE FLOOR") material_type = "BETON DÖŞEME";
            else if (material_type == "CEMENT") material_type = "ÇİMENTO";
            if (specimen_name == "Cube") specimen_name = "Küp";
            else if (specimen_name == "Cylinder") specimen_name = "Silindir";
            else if (specimen_name == "Masonry") specimen_name = "Briket";
            else if (specimen_name == "Beam 3P") specimen_name = "Kiriş 3N";
            else if (specimen_name == "Beam 4P") specimen_name = "Kiriş 4N";
            else if (specimen_name == "Kerb") specimen_name = "Bordür";
            else if (specimen_name == "Paving Stone") specimen_name = "Parke Taşı";
            else if (specimen_name == "Flagstone") specimen_name = "Karo";
            if(test_type_name == "Compression") test_type_name = "Basma";
            else if(test_type_name == "Flexural") test_type_name = "Eğilme";
            if(test_type_name == "Split Tensile") test_type_name = "Yarmada Çekme";
        }
        h_label = fontmetric.width(header_report);
        t_label = fontmetric.width(testName_report);
        int y = printer.pageRect().y();
        int x = y/1.5;
        QStyleOptionViewItem option;
        QModelIndex index;
        QRect rect;     // header rect
        painter.fillRect(option.rect, option.palette.highlight());
        double factor ;//= double(value)/100.0;
        QLineF line(x,y,9000,700);
        painter.setPen(Qt::black);
        painter.setFont(QFont(editReport->ui->fontComboBox->currentFont()));    // works
        QImage LOGO ;
        /// TEMPLATE_1
        if(editReport->templ_type==0){      //
            painter.drawText(0, 200,      header_report);
            painter.drawText(0, 1.5*y,    testName_report);
            painter.drawImage(0,  0,  QImage(editReport->logo_load), -13*x, 0);
            if(editReport->lang_file == 0){
                ui->lineEdit_addInfo->setText("Ek Bilgi");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*6.75, int(1750*(option.rect.width()-5)), option.rect.height()-y*3.45 ); // table
                painter.drawRect( option.rect.x()+x*9, option.rect.y()+6.75*y, int(1020*(option.rect.width())), option.rect.height()-y*3.45 );
                painter.drawText( 0,        3*y,      "DENEY BİLGİSİ");
                painter.drawText( 0,        3.7*y,    "Deney Tarihi");
                painter.drawText( x*9.5,    3.7*y,    ui->label_test_start_date->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*4, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        4.4*y,    "Deney Başlangıç - Bitiş");
                painter.drawText( x*9.5,    4.4*y,    ui->label_test_start_time->text() + " - " +ui->label_test_finish_time->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*4.7, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        5.1*y,    "Deney Sayısı");
                painter.drawText( x*9.5,    5.1*y,    ui->label_test_no->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*5.4, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        5.8*y,    "Deney Tipi");
                painter.drawText( x*9.5,    5.8*y,    test_type_name + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*6.1, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        6.5*y,    ui->lineEdit_addInfo->text());
                painter.drawText( x*9.5,    6.5*y,    ui->lineEdit_addInfo2->text() + "\n");
                //
                painter.drawText( 0,        8*y,     "NUMUNE DETAYLARI");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*13.25, int(1750*(option.rect.width()-5)), option.rect.height()-y*4.95); // table
                painter.drawRect( option.rect.x()+x*9, option.rect.y()+y*13.25, int(1020*(option.rect.width())), option.rect.height()-y*4.95);
                painter.drawText( 0,        8.7*y,    "Numune");
                painter.drawText( x*9.5,    8.7*y,    specimen_name + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*9.05, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        9.4*y,    "Materyal");
                painter.drawText( x*9.5,    9.4*y,    material_type + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*9.75, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        10.1*y,   "Yaş");
                painter.drawText( x*9.5,    10.1*y,   ui->label_specAge->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*10.45, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        10.8*y,   QString("Boyut (%1)").arg(length_unit));
                painter.drawText( x*9.5,    10.8*y,   ui->label_test_dimensions->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*11.15, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        11.5*y,   QString("Alan (%1%2)").arg(length_unit,"2"));
                painter.drawText( x*9.5,    11.5*y,   ui->label_test_area->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*11.85, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        12.2*y,   QString("Tepe Yük (%1)").arg(load_unit));
                painter.drawText( x*9.5,    12.2*y,   ui->label_test_peak_load->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*12.55, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        12.9*y,   QString("Tepe Gerilim (%1)").arg(stress_unit,"2"));
                painter.drawText( x*9.5,    12.9*y,   ui->label_test_peak_stress->text() + "\n");
                painter.drawText( 0,        15*y,     "Ek Bilgi :");
                painter.drawText( 0,        15.7*y,   "Deney Teslimi :");
                painter.drawText( 0,        16.4*y,   "Test Teknikeri :");
                painter.drawText( x*12.5,   16.4*y,   "İmza :");
            }
            if(editReport->lang_file==1){
                ui->lineEdit_addInfo->setText("Additional");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*6.75, int(1750*(option.rect.width()-5)), option.rect.height()-y*3.45 ); // table
                painter.drawRect( option.rect.x()+x*9, option.rect.y()+6.75*y, int(1020*(option.rect.width())), option.rect.height()-y*3.45 );
                painter.drawText( 0,        3*y,      "TEST INFORMATION");
                painter.drawText( 0,        3.7*y,    "Test Date");
                painter.drawText( x*9.5,    3.7*y,    ui->label_test_start_date->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*4, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        4.4*y,    "Test Start - End");
                painter.drawText( x*9.5,    4.4*y,    ui->label_test_start_time->text() + " - " +ui->label_test_finish_time->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*4.7, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        5.1*y,    "Test No");
                painter.drawText( x*9.5,    5.1*y,    ui->label_test_no->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*5.4, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        5.8*y,    "Test Type");
                painter.drawText( x*9.5,    5.8*y,    test_type_name + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*6.1, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        6.5*y,    ui->lineEdit_addInfo->text());
                painter.drawText( x*9.5,    6.5*y,    ui->lineEdit_addInfo2->text() + "\n");
                //
                painter.drawText( 0,        8*y,     "SPECIMEN DETAILS");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*13.25, int(1750*(option.rect.width()-5)), option.rect.height()-y*4.95); // table
                painter.drawRect( option.rect.x()+x*9, option.rect.y()+y*13.25, int(1020*(option.rect.width())), option.rect.height()-y*4.95);
                painter.drawText( 0,        8.7*y,    "Specimen");
                painter.drawText( x*9.5,    8.7*y,     specimen_name + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*9.05, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        9.4*y,    "Material");
                painter.drawText( x*9.5,    9.4*y,    material_type + "\n");        // TOO İNGİİZCE EKLE
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*9.75, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        10.1*y,   "Age");
                painter.drawText( x*9.5,    10.1*y,    ui->label_specAge->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*10.45, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        10.8*y,    QString("Dimensions (%1)").arg(length_unit));
                painter.drawText( x*9.5,    10.8*y,    ui->label_test_dimensions->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*11.15, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        11.5*y,   QString("Area (%1%2)").arg(length_unit,"2"));
                painter.drawText( x*9.5,    11.5*y,   ui->label_test_area->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*11.85, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        12.2*y,   QString("Peak Load (%1)").arg(load_unit));
                painter.drawText( x*9.5,    12.2*y,   ui->label_test_peak_load->text() + "\n");
                painter.drawRect( option.rect.x()+x*18, option.rect.y()+y*12.55, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawText( 0,        12.9*y,   QString("Peak Stress (%1)").arg(stress_unit,"2"));
                painter.drawText( x*9.5,    12.9*y,   ui->label_test_peak_stress->text() + "\n");
                painter.drawText( 0,        15*y,     "Additional :");
                painter.drawText( 0,        15.7*y,   "Test Delivery:");
                painter.drawText( 0,        16.4*y,   "Test Technician :");
                painter.drawText( x*12.5,   16.4*y,   "Signature :");
            }
            painter.restore();
        }
        /// TEMPLATE_2 :
        if(editReport->templ_type == 1){
            painter.drawRect( option.rect.x()+18.1*x, option.rect.y()+y*1.8, int(1770*(option.rect.width()-5)), option.rect.height()-y*2 ); // out table border
            painter.drawRect( option.rect.x()+18.03*x, option.rect.y()+y*1.75, int(1756*(option.rect.width()-5)), option.rect.height()-y*1.9 ); // inner table border
            painter.restore();

            painter.drawText(printer.width()/2 - h_label/2, y/2, header_report);
            painter.drawText(printer.width()/2 - t_label/2, y*1.2, testName_report);
            painter.drawImage(0,     0,        QImage(editReport->logo_load), 0, 0);
            if(editReport->lang_file == 0){
                ui->lineEdit_addInfo->setText("Ek Bilgi");
                painter.drawText( x/2, 3*y,   "Deney Tarihi");
                painter.drawText( x*6, 3*y,   ":  " + ui->label_test_start_date->text() + "\n");
                painter.drawText( x/2, 3.7*y, "Deney Sayısı");
                painter.drawText( x*6, 3.7*y, ":  " + ui->label_test_no->text() + "\n");
                painter.drawText( x/2, 4.4*y, "Deney Başlangıç - Bitiş");
                painter.drawText( x*6, 4.4*y, ":  " + ui->label_test_start_time->text() + " - " +ui->label_test_finish_time->text() + "\n");
                painter.drawText( x/2, 5.1*y, "Deney Tipi");
                painter.drawText( x*6, 5.1*y, ":  " + test_type_name + "\n");
                painter.drawText( x/2, 5.8*y,  QString("Tepe Yük  (%1)").arg(load_unit) + "\n");
                painter.drawText( x*6, 5.8*y,  ":  " + ui->label_test_peak_load->text() + "\n");
                painter.drawText( x/2, 6.5*y,  QString("Tepe Gerilim  (%1)").arg(stress_unit) + "\n");
                painter.drawText( x*6, 6.5*y,  ":  " + ui->label_test_peak_stress->text() + "\n");
                painter.drawText( x/2, 7.2*y,   ui->lineEdit_addInfo->text());
                painter.drawText( x*6, 7.2*y,   ":  " + ui->lineEdit_addInfo2->text() + "\n");
                painter.drawRect( option.rect.x()+17*x, option.rect.y()+7.3*y, int(1020*(option.rect.width()-5)), option.rect.height() );

                QString header2 = "NUMUNE DETAYLARI";
                painter.drawText( x-x*1.1, 8.6*y, header2 + "\n");
                painter.drawRect( option.rect.x()+18.1*x, option.rect.y()+9.8*y, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawRect( option.rect.x()+18.1*x, option.rect.y()+10.7*y, int(1750*(option.rect.width()-5)), option.rect.height()-y*1.8 );
                painter.drawText( x/1.3,  9.4*y,   "Numune");
                painter.drawText( x/4.2,  10.3*y,   specimen_name + "\n");
                painter.drawRect( option.rect.x()+3.4*x, option.rect.y()+10.7*y, (option.rect.width()), option.rect.height()-1300 );
                painter.drawText( x*4.9,  9.4*y,   "Yaş");
                painter.drawText( x*3.7,  10.3*y,  ui->label_specAge->text() + "\n");
                painter.drawRect( option.rect.x()+7*x, option.rect.y()+10.7*y, (option.rect.width()), option.rect.height()-1300 );
                painter.drawText( x*8.1,  9.4*y,   "Materyal");
                painter.drawText( x*7.4,  10.3*y,  material_type + "\n");
                painter.drawRect( option.rect.x()+10.7*x, option.rect.y()+10.7*y, (option.rect.width()), option.rect.height()-1300 );
                painter.drawText( x*12.1, 9.3*y,  "Boyut");
                painter.drawText( x*12.2, 9.6*y,  QString("(%1)").arg(length_unit) + "\n");
                painter.drawText( x*11.1, 10.3*y, ui->label_test_dimensions->text() + "\n");
                painter.drawRect( option.rect.x()+14.5*x, option.rect.y()+10.7*y, (option.rect.width()), option.rect.height()-1300 );
                painter.drawText( x*15.9, 9.3*y,  "Alan");
                painter.drawText( x*15.8, 9.6*y,  QString("(%1%2)").arg(length_unit,"2") + "\n");
                painter.drawText( x*14.9, 10.3*y, ui->label_test_area->text() + "\n");
                painter.drawText( x/2, 12.3*y, "Deney Teslimi");
                painter.drawText( x*6, 12.3*y, ":  ");
                painter.drawText( x/2, 13*y,  "Ek Bilgi");
                painter.drawText( x*6, 13*y, ":  ");
                painter.drawRect( option.rect.x()+17*x, option.rect.y()+13.1*y, int(1020*(option.rect.width()-5)), option.rect.height() );

                painter.drawText( x/2, 16*y,  "Deney Teknikeri :");
                painter.drawText( x*15, 16*y,  "İmza");
                //painter.drawText( x*17,17.5*y,  "1");
            }
            if(editReport->lang_file == 1){
                ui->lineEdit_addInfo->setText("Additional");
                painter.drawText( x/2, 3*y,   "Test Date");
                painter.drawText( x*6, 3*y,   ":  " + ui->label_test_start_date->text() + "\n");
                painter.drawText( x/2, 3.7*y, "Test No");
                painter.drawText( x*6, 3.7*y, ":  " + ui->label_test_no->text() + "\n");
                painter.drawText( x/2, 4.4*y, "Test Start - End");
                painter.drawText( x*6, 4.4*y, ":  " + ui->label_test_start_time->text() + " - " +ui->label_test_finish_time->text() + "\n");
                painter.drawText( x/2, 5.1*y, "Test Type");
                painter.drawText( x*6, 5.1*y, ":  " + test_type_name + "\n");
                painter.drawText( x/2, 5.8*y,  QString("Peak Load  (%1)").arg(load_unit) + "\n");
                painter.drawText( x*6, 5.8*y,  ":  " + ui->label_test_peak_load->text() + "\n");
                painter.drawText( x/2, 6.5*y,  QString("Peak Stress  (%1)").arg(stress_unit) + "\n");
                painter.drawText( x*6, 6.5*y,  ":  " + ui->label_test_peak_stress->text() + "\n");
                painter.drawText( x/2, 7.2*y,   ui->lineEdit_addInfo->text());
                painter.drawText( x*6, 7.2*y,   ":  " + ui->lineEdit_addInfo2->text() + "\n");
                painter.drawRect( option.rect.x()+17*x, option.rect.y()+7.3*y, int(1020*(option.rect.width()-5)), option.rect.height() );

                QString header2 = "SPECIMEN DETAILS";
                painter.drawText( x-x*1.1, 8.6*y, header2 + "\n");
                painter.drawRect( option.rect.x()+18.1*x, option.rect.y()+9.8*y, int(1750*(option.rect.width()-5)), option.rect.height() );
                painter.drawRect( option.rect.x()+18.1*x, option.rect.y()+10.7*y, int(1750*(option.rect.width()-5)), option.rect.height()-y*1.8 );
                painter.drawText( x/1.3,  9.4*y,   "Specimen");
                painter.drawText( x/4.2,  10.3*y,   specimen_name + "\n");
                painter.drawRect( option.rect.x()+3.4*x, option.rect.y()+10.7*y, (option.rect.width()), option.rect.height()-1300 );
                painter.drawText( x*4.9,  9.4*y,   "Age");
                painter.drawText( x*3.7,  10.3*y,  ui->label_specAge->text() + "\n");
                painter.drawRect( option.rect.x()+7*x, option.rect.y()+10.7*y, (option.rect.width()), option.rect.height()-1300 );
                painter.drawText( x*8.1,  9.4*y,   "Material");
                painter.drawText( x*7.4,  10.3*y,  material_type + "\n");
                painter.drawRect( option.rect.x()+10.7*x, option.rect.y()+10.7*y, (option.rect.width()), option.rect.height()-1300 );
                painter.drawText( x*12.1, 9.3*y,  "Dimensions");
                painter.drawText( x*12.2, 9.6*y,  QString("(%1)").arg(length_unit) + "\n");
                painter.drawText( x*11.1, 10.3*y, ui->label_test_dimensions->text() + "\n");
                painter.drawRect( option.rect.x()+14.5*x, option.rect.y()+10.7*y, (option.rect.width()), option.rect.height()-1300 );
                painter.drawText( x*15.9, 9.3*y,  "Area");
                painter.drawText( x*15.8, 9.6*y,  QString("(%1%2)").arg(length_unit,"2") + "\n");
                painter.drawText( x*14.9, 10.3*y, ui->label_test_area->text() + "\n");
                painter.drawText( x/2, 12.3*y, "Test Delivery");
                painter.drawText( x*6, 12.3*y, ":  ");
                painter.drawText( x/2, 13*y,  "Additional");
                painter.drawText( x*6, 13*y, ":  ");
                painter.drawRect( option.rect.x()+17*x, option.rect.y()+13.1*y, int(1020*(option.rect.width()-5)), option.rect.height() );

                painter.drawText( x/2, 16*y,  "Test Technician :");
                painter.drawText( x*15, 16*y,  "Signature");
                //painter.drawText( x*17,17.5*y,  "1");
            }
            qDebug()<<"printer.pageRect().y()"<<printer.pageRect().y()+"\n"<<"printer.width()"<<printer.width();
            qDebug()<<option.rect.x()+2 << option.rect.y()+2 << int(200*(option.rect.width()-5)) << option.rect.height()-5;

// second page of pdf :
//            printer.newPage();
//            painter.drawText( 0,    y, QString::fromUtf8("Grafik"));
//            painter.drawText( x*17, y*17.5,  "2");

//            const QImage image(QDir::currentPath()+"/example.pdf");      // todo : gorunmuyo
//            const QPoint imageCoordinates(x,y*2);

//            const QImage image1(QDir::currentPath()+"/example.pdf");      // todo : gorunmuyo
//            const QPoint imageCoordinates1(x*30,y*2);

//            painter.drawImage(imageCoordinates, image);
//            painter.drawImage(imageCoordinates1, image1);
//            //pdfWriter.newPage();

//            QPixmap pix(ui->wdg_plotArea->size());
//            QPainter painter1(&pix);
//            ui->wdg_plotArea->render(&painter);
//            painter.end();

//            painter1.begin(&printer);
//            double xscale = printer.pageRect().width() / double(pix.width());
//            double yscale = printer.pageRect().height() / double(pix.height());
//            double scale = qMin(xscale, yscale);
//            painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
//                           printer.paperRect().y()*4 + printer.pageRect().height() / 2);
//            painter.scale(scale, scale);
//            painter.translate(-ui->wdg_plotArea->width() /2, -ui->wdg_plotArea->height() /2);
//            painter.drawPixmap(0, 0, pix);

//            painter1.end();
        }
        break;
    }
    case _TXT:
        QFile test_res;
        if(ui->lineEdit_fileName->text().isEmpty())
            res_fileName = QString("/test_%1").arg(test_no) + start_date_filename_arg;
        else
            res_fileName = QString("/%1").arg(pdf_fileName);
        res_fileName.append(".txt");
        test_res.setFileName(pdf_path + res_fileName);
        test_res.open(QIODevice::WriteOnly);
        QTextStream lines(&test_res);
        lines.setCodec("UTF-8");
        if(lang_index == _TR){
            lines << "\nDENEY SONUÇLARI \n";
            lines << "Firma :" << ui->lineEdit_company->text() << "\n";
            lines << "Deney_Adı :" << ui->lineEdit_testName->text() << "\n";
            lines << "Kullanıcı :"<< ui->lineEdit_user->text() << "\n";
            lines << "Deney_Sayısı :" << ui->label_test_no->text() << "\n";
            lines << "Deney_Başlama_Tarihi :" << ui->label_test_start_date->text() << "\n";
            lines << "Deney_Başlama_Saati :" << ui->label_test_start_time->text() << "\n";
            lines << "Deney_Bitiş_Saati :" << ui->label_test_finish_time->text() << "\n";
            lines << "Deney_Tipi :" << test_type_name << "\n";
            lines << "Numune :" << ui->label_test_specimen_type->text() << "\n";
            lines << ui->lineEdit_addInfo->text() << ui->lineEdit_addInfo2->text() << "\n";
            lines << QString("Boyutlar_(%1) :").arg(length_unit) << ui->label_test_dimensions->text() << "\n";
            lines << QString("Yaş :") << ui->label_specAge->text() << "\n";
            lines << QString("Alan_(%1%2) :").arg(length_unit,"2") << ui->label_test_area->text() << "\n";
            lines << QString("Tepe_Yük_(%1) :").arg(load_unit) << ui->label_test_peak_load->text() << "\n";
            lines << QString("Tepe_Gerilim_(%1) :").arg(stress_unit) << ui->label_test_peak_stress->text() << "\n";
            if(ui->label_test_paving_stone_fpl->isHidden() == false){
                lines << QString("P/L_(%1/%2)  :").arg(load_unit,length_unit) << ui->label_test_paving_stone_fpl->text() << "\n";
            }
        }
        else if(lang_index == _ENG){
            lines << "\nTEST RESULTS \n";
            lines << "Company :" << ui->lineEdit_company->text() << "\n";
            lines << "Test_Name :" << ui->lineEdit_testName->text() << "\n";
            lines << "User :" << ui->lineEdit_user->text() << "\n";
            lines << "Test_No :" << ui->label_test_no->text() << "\n";
            lines << "Test_Start_Date :" << ui->label_test_start_date->text() << "\n";
            lines << "Test_Start_Time :" << ui->label_test_start_time->text() << "\n";
            lines << "Test_End_Time :" << ui->label_test_finish_time->text() << "\n";
            lines << "Test_Type :" << test_type_name << "\n";
            lines << "Specimen :" << ui->label_test_specimen_type->text() << "\n";
            lines << ui->lineEdit_addInfo->text() << ui->lineEdit_addInfo2->text() << "\n";
            lines << QString("Dimensions_(%1) :").arg(length_unit) << ui->label_test_dimensions->text() << "\n";
            lines << QString("Age :") << ui->label_specAge->text() << "\n";
            lines << QString("Area_(%1%2) :").arg(length_unit,"2") << ui->label_test_area->text() << "\n";
            lines << QString("Peak_Load_(%1) :").arg(load_unit) << ui->label_test_peak_load->text() << "\n";
            lines << QString("Peak_Stress_(%1) :").arg(stress_unit) << ui->label_test_peak_stress->text() << "\n";
            if(ui->label_test_paving_stone_fpl->isHidden() == false){
                lines << QString("P/L_(%1/%2)  :").arg(load_unit,length_unit) << ui->label_test_paving_stone_fpl->text() << "\n";
            }
        }
        test_res.close();
        break;
    }
    QMessageBox message;
    message.setWindowTitle("Uyarı Kutusu");
    message.setFont(QFont("Amerika", Fontsize-1 , -1, true));
    message.setText(QString("Sonuçlar '%1' altına kaydedildi.").arg(pdf_path));
    message.setIconPixmap(QPixmap(":/icons/okay.png"));
    message.exec();

    ui->label_nameOfFile->setText(pdf_path + res_fileName);
    qDebug()<<"Results saved as"<<res_fileName;
}
void PressApp::on_pushButton_editFile_clicked()
{
    editReport->setWindowTitle("Gelişmiş Düzenleme");
    editReport->exec();
}
void PressApp::on_pushButton_openFile_view_clicked()
{
    results_saved = false;
    QString filters(".pdf files (*.pdf);; .txt files (*.txt)");
    QString defaultFilter(".pdf files (*.pdf)");
    custom_path = QFileDialog::getOpenFileName(this, tr("Dosya Aç"), QDir::currentPath(),
                                                filters, &defaultFilter);
    if(QFileDialog::Accepted){
        custom_file_loaded = true;
        ui->label_nameOfFile->setText(custom_path);
        res_fileName = custom_path;
        qDebug()<<"custom_path :"<<res_fileName;
        if(custom_path.endsWith(".pdf") || custom_path.endsWith(".txt")){
            ui->pushButton_editFile->setDisabled(1);
            ui->pushButton_editFile->setStyleSheet("color: rgb(150,180,255)");
        } else{
            ui->pushButton_editFile->setEnabled(1);
            ui->pushButton_editFile->setStyleSheet("color: rgb(0,20,255)");
        }
        ui->pushButton_quitFile->setEnabled(1);
    }
    else   custom_file_loaded = false;
}
void PressApp::on_pushButton_quitFile_clicked()
{
    results_saved = false;
    custom_file_loaded = false;

    ui->pushButton_editFile->setEnabled(1);
    ui->pushButton_editFile->setStyleSheet("color: rgb(0,20,255)");

    ui->label_nameOfFile->setText("..");

    ui->pushButton_quitFile->setDisabled(1);
}
void PressApp::on_pushButton_printResults_clicked()     /// OPEN PDF FILE :
{
    if(results_saved)
        QDesktopServices::openUrl(QUrl::fromLocalFile(pdf_path + "/" + res_fileName));
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
void PressApp::on_loadFinished(bool ok)     // UNUSED : deneme icin
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

