#-------------------------------------------------
#
# Project created by QtCreator 2022-01-17T11:37:35
#
#-------------------------------------------------

QT       += core gui serialport network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport webenginewidgets

TARGET = press_v3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.

SOURCES += \
        main.cpp \
        pressapp.cpp \
    remoteconnection.cpp \
    ethernet.cpp \
    qcustomplot.cpp \
    plot.cpp \
    authorization.cpp \
    results.cpp \
    editreport.cpp \
    autotuning.cpp \
    aux_thread.cpp \
    filters.cpp \
    calibration.cpp \
    pid.cpp

HEADERS += \
        pressapp.h \
    remoteconnection.h \
    qcustomplot.h \
    editreport.h \
    aux_thread.h

FORMS += \
        pressapp.ui \
    editreport.ui

#INCLUDEPATH += /usr/local/include/poppler/qt5
LIBS += -L/usr/local/lib -lpoppler-qt5

DISTFILES +=

TRANSLATIONS = press_tr.ts \
            press_en.ts

RESOURCES += \
    source.qrc
