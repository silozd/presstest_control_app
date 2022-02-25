#ifndef EDITREPORT_H
#define EDITREPORT_H

#include <QDialog>

#define TEMPLATE_1  0
#define TEMPLATE_2  1
#define TEMPLATE_3  2

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

    int template_type;

private slots:

    void on_pushButton_save_clicked();

private:
};

#endif // EDITREPORT_H
