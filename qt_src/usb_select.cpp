#include "usb_select.h"
#include "ui_usb_select.h"

usb_select::usb_select(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usb_select)
{
    ui->setupUi(this);
}

usb_select::~usb_select()
{
    delete ui;
}
