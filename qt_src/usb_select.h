#ifndef USB_SELECT_H
#define USB_SELECT_H

#include <QWidget>
#include <unistd.h>
#include <vector>
#include <string>

#include "../include/device_c.hpp"

namespace Ui
{
    class usb_select;
}

class usb_select : public QWidget
{
    Q_OBJECT

public:
    explicit usb_select(QWidget *parent = 0);
    ~usb_select();

    bool update();

private:
    Ui::usb_select *ui;
};

#endif // USB_SELECT_H
