#include "../../include/device_c.hpp"
#include "gtest/gtest.h"
#include <strings.h>

class usb_debug : public device_c {
private:
    // set_usbID()が呼ばれるとtrueに変化
    // テストでいきなりgetメソッドが呼ばれた際にエラーを返すために定義
    bool exitUsbID_;
    bool exitUsbSerial_;

public:
    usb_debug();
    ~usb_debug();
    std::string get_usbSerial() const;
    std::string get_usbID() const;
    bool set_usbID(const std::string usbID);
};
