/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_menue_PasswordSetting;
    QAction *action_menue_USBSetting;
    QAction *action_menue_Init;
    QWidget *centralWidget;
    QPushButton *push_enc;
    QPushButton *push_dec;
    QLineEdit *lineEdit_file_path;
    QLabel *label;
    QPushButton *pushButton_clear;
    QLabel *label_usb_debug;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 347);
        action_menue_PasswordSetting = new QAction(MainWindow);
        action_menue_PasswordSetting->setObjectName(QString::fromUtf8("action_menue_PasswordSetting"));
        action_menue_USBSetting = new QAction(MainWindow);
        action_menue_USBSetting->setObjectName(QString::fromUtf8("action_menue_USBSetting"));
        action_menue_Init = new QAction(MainWindow);
        action_menue_Init->setObjectName(QString::fromUtf8("action_menue_Init"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        push_enc = new QPushButton(centralWidget);
        push_enc->setObjectName(QString::fromUtf8("push_enc"));
        push_enc->setGeometry(QRect(70, 180, 89, 25));
        push_dec = new QPushButton(centralWidget);
        push_dec->setObjectName(QString::fromUtf8("push_dec"));
        push_dec->setGeometry(QRect(230, 180, 89, 25));
        lineEdit_file_path = new QLineEdit(centralWidget);
        lineEdit_file_path->setObjectName(QString::fromUtf8("lineEdit_file_path"));
        lineEdit_file_path->setGeometry(QRect(70, 80, 251, 71));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 50, 191, 17));
        pushButton_clear = new QPushButton(centralWidget);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));
        pushButton_clear->setGeometry(QRect(320, 126, 41, 25));
        label_usb_debug = new QLabel(centralWidget);
        label_usb_debug->setObjectName(QString::fromUtf8("label_usb_debug"));
        label_usb_debug->setGeometry(QRect(90, 240, 171, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 28));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setOrientation(Qt::Horizontal);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addSeparator();
        menu->addAction(action_menue_USBSetting);
        menu->addAction(action_menue_Init);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_menue_PasswordSetting->setText(QCoreApplication::translate("MainWindow", "\343\203\221\343\202\271\343\203\257\343\203\274\343\203\211\350\250\255\345\256\232", nullptr));
        action_menue_USBSetting->setText(QCoreApplication::translate("MainWindow", "USB\347\231\273\351\214\262", nullptr));
        action_menue_Init->setText(QCoreApplication::translate("MainWindow", "\345\210\235\346\234\237\345\214\226", nullptr));
        push_enc->setText(QCoreApplication::translate("MainWindow", "encypt", nullptr));
        push_dec->setText(QCoreApplication::translate("MainWindow", "decrypt", nullptr));
        lineEdit_file_path->setPlaceholderText(QCoreApplication::translate("MainWindow", "\343\203\225\343\202\241\343\202\244\343\203\253\343\203\221\343\202\271\345\205\245\345\212\233", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\257\276\350\261\241\343\203\225\343\202\241\343\202\244\343\203\253\343\202\222\343\203\211\343\203\251\343\203\203\343\202\260", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        label_usb_debug->setText(QCoreApplication::translate("MainWindow", "usbID: ", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\343\203\241\343\203\213\343\203\245\343\203\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
