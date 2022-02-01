#ifndef PASS_CHECK_H
#define PASS_CHECK_H

#include "../include/key_gen.hpp"
#include <QDialog>
#include <QWidget>
#include <string>

namespace Ui {
class pass_check;
}

class pass_check : public QDialog {
    Q_OBJECT

public:
    explicit pass_check(QWidget* parent = 0);
    ~pass_check();
    bool isPassCorrect() const;
    std::string get_pass() const;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::pass_check* ui;
    bool isPassInput_;
    std::string pass_;
};

#endif // PASS_CHECK_H
