#include "pressapp.h"
#include <QApplication>
#include <QFile>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PressApp w;
    w.show();

    return a.exec();
}
