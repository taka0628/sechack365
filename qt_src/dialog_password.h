#ifndef DIALOG_PASSWORD_H
#define DIALOG_PASSWORD_H

#include <QDialog>

namespace Ui {
class Dialog_password;
}

class Dialog_password : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_password(QWidget *parent = 0);
    ~Dialog_password();

private slots:

    void on_lineEdit_password_check_textChanged(const QString &arg1);

private:
    Ui::Dialog_password *ui;
};

#endif // DIALOG_PASSWORD_H
