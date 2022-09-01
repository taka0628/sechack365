/********************************************************************************
** Form generated from reading UI file 'pass_check.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASS_CHECK_H
#define UI_PASS_CHECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pass_check
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_pass;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_error_message;

    void setupUi(QWidget *pass_check)
    {
        if (pass_check->objectName().isEmpty())
            pass_check->setObjectName(QString::fromUtf8("pass_check"));
        pass_check->resize(309, 164);
        horizontalLayoutWidget = new QWidget(pass_check);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 50, 231, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_pass = new QLineEdit(horizontalLayoutWidget);
        lineEdit_pass->setObjectName(QString::fromUtf8("lineEdit_pass"));
        lineEdit_pass->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(lineEdit_pass);

        pushButton = new QPushButton(pass_check);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 120, 89, 25));
        pushButton_2 = new QPushButton(pass_check);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(180, 120, 89, 25));
        label = new QLabel(pass_check);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 131, 17));
        label_error_message = new QLabel(pass_check);
        label_error_message->setObjectName(QString::fromUtf8("label_error_message"));
        label_error_message->setGeometry(QRect(40, 90, 231, 17));

        retranslateUi(pass_check);

        QMetaObject::connectSlotsByName(pass_check);
    } // setupUi

    void retranslateUi(QWidget *pass_check)
    {
        pass_check->setWindowTitle(QApplication::translate("pass_check", "Form", nullptr));
        pushButton->setText(QApplication::translate("pass_check", "OK", nullptr));
        pushButton_2->setText(QApplication::translate("pass_check", "Cansel", nullptr));
        label->setText(QApplication::translate("pass_check", "\343\203\221\343\202\271\343\203\257\343\203\274\343\203\211\343\202\222\345\205\245\345\212\233", nullptr));
        label_error_message->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class pass_check: public Ui_pass_check {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASS_CHECK_H
