#include "pass_check.h"

#include "ui_pass_check.h"

pass_check::pass_check(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::pass_check)
{
    ui->setupUi(this);
    isPassInput_ = false;
}

pass_check::~pass_check() { delete ui; }

void pass_check::on_pushButton_clicked()
{
    QString pass_qst = ui->lineEdit_pass->text();
    if (pass_qst.size() <= 0) {
        sleep(1);
        ui->label_error_message->setText("パスワードが空です");
        return;
    }
    key_gen_c keygen;
    if (!keygen.set_pass(pass_qst.toStdString())) {
        sleep(1);
        ui->label_error_message->setText("パスワードが違います");
        return;
    }
    if (!keygen.is_pass_correct()) {
        sleep(1);
        ui->label_error_message->setText("パスワードが違います");
        return;
    }
    this->isPassInput_ = true;
    this->pass_        = pass_qst.toStdString();
    this->done(0);
}

void pass_check::on_pushButton_2_clicked()
{
    this->done(1);
}

std::string pass_check::get_pass() const
{
    return this->pass_;
}
