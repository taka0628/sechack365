#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>

#include "../include/aes_c.hpp"
#include "../include/error.hpp"
#include "../include/file_enc.hpp"
#include "../include/master_key_c.hpp"
#include "algorithm"
#include "dialog_dec_pass.h"
#include "dialog_password.h"
#include "iostream"
#include "pass_check.h"
#include "usb_select.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    void error_messege_box(QString message);

private slots:
    void on_push_enc_clicked();

    //    void on_pushButton_debug_clicked();

    void on_push_dec_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_pass_register_clicked();

    //    void on_MainWindow_destroyed(QObject *arg1);

    void on_action_menue_PasswordSetting_triggered();

    void on_action_menue_USBSetting_triggered();

    void on_action_menue_Init_triggered();

private:
    Ui::MainWindow* ui;
    //    Dialog_password* get_password_wind;
    Dialog_dec_pass* get_dec_pass_wind;
    //    usb_select* usb_select_wind;
};

#endif // MAINWINDOW_H
