/********************************************************************************
** Form generated from reading UI file 'dialog_dec_pass.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_DEC_PASS_H
#define UI_DIALOG_DEC_PASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog_dec_pass
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit_dec_pass;

    void setupUi(QDialog *Dialog_dec_pass)
    {
        if (Dialog_dec_pass->objectName().isEmpty())
            Dialog_dec_pass->setObjectName(QString::fromUtf8("Dialog_dec_pass"));
        Dialog_dec_pass->resize(323, 205);
        buttonBox = new QDialogButtonBox(Dialog_dec_pass);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 130, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit_dec_pass = new QLineEdit(Dialog_dec_pass);
        lineEdit_dec_pass->setObjectName(QString::fromUtf8("lineEdit_dec_pass"));
        lineEdit_dec_pass->setGeometry(QRect(40, 70, 251, 25));
        lineEdit_dec_pass->setEchoMode(QLineEdit::Password);

        retranslateUi(Dialog_dec_pass);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog_dec_pass, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog_dec_pass, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_dec_pass);
    } // setupUi

    void retranslateUi(QDialog *Dialog_dec_pass)
    {
        Dialog_dec_pass->setWindowTitle(QApplication::translate("Dialog_dec_pass", "Dialog", nullptr));
        lineEdit_dec_pass->setPlaceholderText(QApplication::translate("Dialog_dec_pass", "\343\203\221\343\202\271\343\203\257\343\203\274\343\203\211\343\202\222\345\205\245\345\212\233", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_dec_pass: public Ui_Dialog_dec_pass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_DEC_PASS_H
