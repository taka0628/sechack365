/********************************************************************************
** Form generated from reading UI file 'dialog_password.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_PASSWORD_H
#define UI_DIALOG_PASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog_password
{
public:
    QLineEdit *lineEdit_password;
    QLabel *label;
    QLineEdit *lineEdit_password_check;
    QLabel *label_2;
    QLabel *label_show_pass_check;
    QPushButton *pushButton_OK;
    QPushButton *pushButton_Cancel;

    void setupUi(QDialog *Dialog_password)
    {
        if (Dialog_password->objectName().isEmpty())
            Dialog_password->setObjectName(QString::fromUtf8("Dialog_password"));
        Dialog_password->resize(394, 210);
        lineEdit_password = new QLineEdit(Dialog_password);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(50, 40, 271, 25));
        lineEdit_password->setAutoFillBackground(false);
        lineEdit_password->setEchoMode(QLineEdit::Password);
        lineEdit_password->setReadOnly(false);
        lineEdit_password->setCursorMoveStyle(Qt::LogicalMoveStyle);
        lineEdit_password->setClearButtonEnabled(false);
        label = new QLabel(Dialog_password);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 20, 121, 17));
        lineEdit_password_check = new QLineEdit(Dialog_password);
        lineEdit_password_check->setObjectName(QString::fromUtf8("lineEdit_password_check"));
        lineEdit_password_check->setGeometry(QRect(50, 90, 271, 25));
        lineEdit_password_check->setAutoFillBackground(false);
        lineEdit_password_check->setEchoMode(QLineEdit::Password);
        lineEdit_password_check->setReadOnly(false);
        lineEdit_password_check->setCursorMoveStyle(Qt::LogicalMoveStyle);
        lineEdit_password_check->setClearButtonEnabled(false);
        label_2 = new QLabel(Dialog_password);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 70, 121, 17));
        label_show_pass_check = new QLabel(Dialog_password);
        label_show_pass_check->setObjectName(QString::fromUtf8("label_show_pass_check"));
        label_show_pass_check->setGeometry(QRect(330, 93, 21, 17));
        pushButton_OK = new QPushButton(Dialog_password);
        pushButton_OK->setObjectName(QString::fromUtf8("pushButton_OK"));
        pushButton_OK->setGeometry(QRect(50, 140, 89, 25));
        pushButton_Cancel = new QPushButton(Dialog_password);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(230, 140, 89, 25));

        retranslateUi(Dialog_password);

        QMetaObject::connectSlotsByName(Dialog_password);
    } // setupUi

    void retranslateUi(QDialog *Dialog_password)
    {
        Dialog_password->setWindowTitle(QApplication::translate("Dialog_password", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog_password", "\343\203\221\343\202\271\343\203\257\343\203\274\343\203\211\343\202\222\345\205\245\345\212\233", nullptr));
        lineEdit_password_check->setText(QString());
        label_2->setText(QApplication::translate("Dialog_password", "\347\242\272\350\252\215", nullptr));
        label_show_pass_check->setText(QApplication::translate("Dialog_password", "NG", nullptr));
        pushButton_OK->setText(QApplication::translate("Dialog_password", "OK", nullptr));
        pushButton_Cancel->setText(QApplication::translate("Dialog_password", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_password: public Ui_Dialog_password {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_PASSWORD_H
