#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "algorithm"
#include "iostream"

#include "../src/aes_c.hpp"
#include "../src/RSA_c.hpp"

#include "dialog_password.h"


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

private:
    Ui::MainWindow *ui;
    Dialog_password *get_password_wind;
};

#endif // MAINWINDOW_H
