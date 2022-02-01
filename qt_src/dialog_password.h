#ifndef DIALOG_PASSWORD_H
#define DIALOG_PASSWORD_H

#include <QDialog>
#include <chrono>

#include "../include/file_enc.hpp"
#include "../include/key_gen.hpp"
#include "../include/master_key_c.hpp"

namespace Ui {
class Dialog_password;
}

class Dialog_password : public QDialog {
    Q_OBJECT

public:
    explicit Dialog_password(QWidget* parent = 0);
    ~Dialog_password();

    bool is_ok() const;
    bool is_calcel() const;

    void set_file_path(std::string file_path);
    std::string get_pass() const;

private slots:

    void on_lineEdit_password_check_textChanged(const QString& arg1);

    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::Dialog_password* ui;

    bool is_canceled_;
    bool is_ok_;
    std::string pass_;

    std::string file_path_;
};

#endif // DIALOG_PASSWORD_H
