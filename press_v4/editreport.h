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

public slots:

private:
};

#endif // EDITREPORT_H
