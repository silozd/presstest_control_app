/********************************************************************************
** Form generated from reading UI file 'editreport.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITREPORT_H
#define UI_EDITREPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditReport
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QPushButton *pushButton_saveEdit;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QComboBox *comboBox_template;
    QLabel *label;
    QFontComboBox *fontComboBox;
    QPushButton *pushButton_logo;
    QLabel *label_4;
    QComboBox *comboBox_3;
    QLabel *imageLabel;

    void setupUi(QDialog *EditReport)
    {
        if (EditReport->objectName().isEmpty())
            EditReport->setObjectName(QStringLiteral("EditReport"));
        EditReport->resize(1010, 689);
        gridLayout = new QGridLayout(EditReport);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(EditReport);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setCursor(QCursor(Qt::ArrowCursor));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        scrollArea = new QScrollArea(widget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 392, 669));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        comboBox_2 = new QComboBox(scrollAreaWidgetContents);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(comboBox_2, 1, 1, 1, 1);

        pushButton_saveEdit = new QPushButton(scrollAreaWidgetContents);
        pushButton_saveEdit->setObjectName(QStringLiteral("pushButton_saveEdit"));
        pushButton_saveEdit->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(pushButton_saveEdit, 6, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 5, 1, 1, 1);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        comboBox_template = new QComboBox(scrollAreaWidgetContents);
        comboBox_template->setObjectName(QStringLiteral("comboBox_template"));
        comboBox_template->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(comboBox_template, 0, 1, 1, 1);

        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        fontComboBox = new QFontComboBox(scrollAreaWidgetContents);
        fontComboBox->setObjectName(QStringLiteral("fontComboBox"));
        fontComboBox->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(fontComboBox, 2, 1, 1, 1);

        pushButton_logo = new QPushButton(scrollAreaWidgetContents);
        pushButton_logo->setObjectName(QStringLiteral("pushButton_logo"));
        pushButton_logo->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(pushButton_logo, 4, 1, 1, 1);

        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        comboBox_3 = new QComboBox(scrollAreaWidgetContents);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(comboBox_3, 3, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 1);
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(scrollArea, 0, 1, 1, 1);

        imageLabel = new QLabel(widget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setStyleSheet(QStringLiteral("background-color: rgb(250, 250, 250);"));

        gridLayout_3->addWidget(imageLabel, 0, 0, 1, 1);

        gridLayout_3->setColumnStretch(0, 3);
        gridLayout_3->setColumnStretch(1, 2);

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(EditReport);

        QMetaObject::connectSlotsByName(EditReport);
    } // setupUi

    void retranslateUi(QDialog *EditReport)
    {
        EditReport->setWindowTitle(QApplication::translate("EditReport", "Dialog", Q_NULLPTR));
        label_3->setText(QApplication::translate("EditReport", "Yaz\304\261 Tipi :", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("EditReport", "A4", Q_NULLPTR)
         << QApplication::translate("EditReport", "A5", Q_NULLPTR)
         << QApplication::translate("EditReport", "A3", Q_NULLPTR)
        );
        pushButton_saveEdit->setText(QApplication::translate("EditReport", "Kaydet", Q_NULLPTR));
        label_2->setText(QApplication::translate("EditReport", "Boyut :", Q_NULLPTR));
        label->setText(QApplication::translate("EditReport", "Bi\303\247im :", Q_NULLPTR));
        pushButton_logo->setText(QApplication::translate("EditReport", "Logo Y\303\274kle", Q_NULLPTR));
        label_4->setText(QApplication::translate("EditReport", "Dil :", Q_NULLPTR));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("EditReport", "TR", Q_NULLPTR)
         << QApplication::translate("EditReport", "ENG", Q_NULLPTR)
        );
        imageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EditReport: public Ui_EditReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITREPORT_H
