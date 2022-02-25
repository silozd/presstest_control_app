#include "pressapp.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PressApp w;
    w.show();
    QFile file;
    file.setFileName(":/stylesheet.css");
    file.open(QFile::ReadOnly);

    QString styleSheet = QLatin1String(file.readAll());
    w.setStyleSheet(styleSheet);
    return a.exec();
}
