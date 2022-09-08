#include "../include/usb_debug.hpp"

using namespace std;

usb_debug::usb_debug()
{
    this->exitUsbID_ = this->exitUsbSerial_ = false;
}
usb_debug::~usb_debug()
{
    this->exitUsbID_ = this->exitUsbSerial_ = false;
}

string usb_debug::get_usbSerial() const
{
    if (this->exitUsbSerial_ == false) {
        return "";
    }
    return "1111222233334444";
}

bool usb_debug::set_usbID(const string usbID)
{
    this->exitUsbID_ = this->exitUsbSerial_ = true;
    return true;
}

string usb_debug::get_usbID() const
{
    if (this->exitUsbID_ == false) {
        return "";
    }
    return "1111:2222";
}
