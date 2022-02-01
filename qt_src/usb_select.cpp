#include "usb_select.h"

#include "ui_usb_select.h"

usb_select::usb_select(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::usb_select)
{
    ui->setupUi(this);
    //起動時処理
    this->update();
}

usb_select::~usb_select() { }

using namespace std;

bool usb_select::update()
{
    device_c usb;
    vector<string> usb_list;
    usb_list = usb.get_usbList();

    //    USBリストを表示
    for (string temp : usb_list) {
        new QListWidgetItem(tr(temp.c_str()), ui->listWidget_select);
    }
    return true;
}

// USB IDを抽出
void usb_select::on_listWidget_select_itemClicked(QListWidgetItem* item)
{
    string selected_usb { item->text().toStdString() };
    this->usbID_ = selected_usb.substr(0, 9);
    ui->label_selected_usbID->setText(QString::fromStdString(this->usbID_));
}

void usb_select::on_pushButton_ok_clicked()
{
    if (this->usbID_.empty()) {
        return;
    }

    device_c usb;
    if (!usb.add_usbID2file(this->usbID_)) {
        QMessageBox msgBox(this);
        msgBox.setText("指定されたUSBを設定できません");
        msgBox.exec();
        return;
    }

    this->done(0);
}

void usb_select::on_pushButton_cansel_clicked()
{
    this->done(1);
}
