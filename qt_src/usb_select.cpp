#include "usb_select.h"
#include "ui_usb_select.h"

usb_select::usb_select(QWidget *parent) : QWidget(parent),
    ui(new Ui::usb_select)
{
    ui->setupUi(this);

    //起動時処理
    this->update();
}

usb_select::~usb_select()
{
    delete ui;
}

using namespace std;

bool usb_select::update()
{
    device_c usb;
    vector<string> usb_list;
    usb_list = usb.get_usbList();

    QString usb_list_qs;
    for(string temp : usb_list){
        usb_list_qs.fromStdString(temp);
        ui->listWidget_select->addItem(usb_list_qs);
    }
    return true;
}

