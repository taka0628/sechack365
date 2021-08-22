#ifndef DIALOG_DEC_PASS_H
#define DIALOG_DEC_PASS_H

#include <QDialog>
#include "iostream"
#include "string"
#include <chrono>

#include "../src/file_enc.hpp"

namespace Ui {
class Dialog_dec_pass;
}

class Dialog_dec_pass : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_dec_pass(QWidget *parent = 0);
    ~Dialog_dec_pass();

    void set_file_path(std::string file_pass);


private slots:

    void on_buttonBox_accepted();

private:
    Ui::Dialog_dec_pass *ui;

    std::string file_path_;
};

#endif // DIALOG_DEC_PASS_H
