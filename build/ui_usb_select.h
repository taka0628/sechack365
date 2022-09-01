/********************************************************************************
** Form generated from reading UI file 'usb_select.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USB_SELECT_H
#define UI_USB_SELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_usb_select
{
public:
    QListWidget *listWidget_select;
    QLabel *label;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cansel;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLabel *label_selected_usbID;

    void setupUi(QWidget *usb_select)
    {
        if (usb_select->objectName().isEmpty())
            usb_select->setObjectName(QString::fromUtf8("usb_select"));
        usb_select->resize(431, 374);
        listWidget_select = new QListWidget(usb_select);
        listWidget_select->setObjectName(QString::fromUtf8("listWidget_select"));
        listWidget_select->setGeometry(QRect(30, 60, 371, 191));
        label = new QLabel(usb_select);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 40, 91, 17));
        pushButton_ok = new QPushButton(usb_select);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(80, 330, 89, 25));
        pushButton_cansel = new QPushButton(usb_select);
        pushButton_cansel->setObjectName(QString::fromUtf8("pushButton_cansel"));
        pushButton_cansel->setGeometry(QRect(260, 330, 89, 25));
        horizontalLayoutWidget = new QWidget(usb_select);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 270, 371, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        label_selected_usbID = new QLabel(horizontalLayoutWidget);
        label_selected_usbID->setObjectName(QString::fromUtf8("label_selected_usbID"));

        horizontalLayout->addWidget(label_selected_usbID);

        horizontalLayout->setStretch(1, 10);

        retranslateUi(usb_select);

        QMetaObject::connectSlotsByName(usb_select);
    } // setupUi

    void retranslateUi(QWidget *usb_select)
    {
        usb_select->setWindowTitle(QApplication::translate("usb_select", "Form", nullptr));
        label->setText(QApplication::translate("usb_select", "USB List", nullptr));
        pushButton_ok->setText(QApplication::translate("usb_select", "OK", nullptr));
        pushButton_cansel->setText(QApplication::translate("usb_select", "Cansel", nullptr));
        label_3->setText(QApplication::translate("usb_select", "Select USB ID: ", nullptr));
        label_selected_usbID->setText(QApplication::translate("usb_select", "null", nullptr));
    } // retranslateUi

};

namespace Ui {
    class usb_select: public Ui_usb_select {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USB_SELECT_H
