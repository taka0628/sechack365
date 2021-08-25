#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "algorithm"
#include "iostream"

#include "../src/aes_c.hpp"
#include "../src/RSA_c.hpp"
#include "../src/file_enc.hpp"

#include "dialog_password.h"
#include "dialog_dec_pass.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_push_enc_clicked();

    void on_pushButton_debug_clicked();

    void on_push_dec_clicked();

private:
    Ui::MainWindow *ui;
    Dialog_password *get_password_wind;
    Dialog_dec_pass *get_dec_pass_wind;
};

#endif // MAINWINDOW_H
