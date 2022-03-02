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

    int template_type;

public slots:

    void on_pushButton_save_clicked();

private:
};

#endif // EDITREPORT_H
