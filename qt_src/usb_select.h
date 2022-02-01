#ifndef USB_SELECT_H
#define USB_SELECT_H

#include <unistd.h>

#include <QDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QWidget>
#include <string>
#include <vector>

#include "../include/device_c.hpp"

namespace Ui {
class usb_select;
}

class usb_select : public QDialog, public device_c {
    Q_OBJECT

public:
    explicit usb_select(QWidget* parent = 0);
    ~usb_select();

    bool update();
    std::string usbID_;

private slots:
    void on_listWidget_select_itemClicked(QListWidgetItem* item);

    void on_pushButton_ok_clicked();

    void on_pushButton_cansel_clicked();

private:
    Ui::usb_select* ui;
};

#endif // USB_SELECT_H
