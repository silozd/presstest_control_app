#ifndef EDITREPORT_H
#define EDITREPORT_H

#include <QDialog>

namespace Ui {
class EditReport;
}
class PressApp ;
class EditReport : public QDialog
{
    Q_OBJECT

public:
    explicit EditReport(QWidget *parent = 0);
    ~EditReport();

    Ui::EditReport *ui;
    PressApp *pressApp;

    int templ_type;
    int lang_file;

public slots:
    void on_comboBox_template_currentIndexChanged(int index);
    void on_pushButton_saveEdit_clicked();
    void on_comboBox_langEdit_currentIndexChanged(int index);

private slots:

private:
};

#endif // EDITREPORT_H
