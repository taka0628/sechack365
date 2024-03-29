#ifndef ___DEVICE_HPP
#define ___DEVICE_HPP

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "algorithm"
#include "cstdio"
#include "error.hpp"
#include "fstream"
#include "iostream"
#include "macro.hpp"
#include "memory"
#include "sstream"
#include "string"
#include "vector"

#include "file_enc.hpp"

class device_c {
private:
    std::string usb_id_;
    std::string usb_serial_;
    uint file_read_cnt;

public:
    device_c();
    ~device_c();
    device_c(const device_c&)            = delete;
    device_c& operator=(const device_c&) = delete;

    bool has_serial(const std::string usb_id) const;
    std::vector<std::string> get_usbList() const;
    // USB_IDとシリアル番号を設定
    bool set_usbID(const std::string);
    bool set_usbID_form_file();

    std::string get_usbID() const;
    std::string get_usbSerial() const;
    uint32_t get_usb_cnt() const;
    // usbIDをファイルへ追加
    bool add_usbID2file(const std::string usbID) const;
    // usbIDがファイルに存在するか？
    bool is_exist_usbID_in_file(const std::string usbID) const;
};

#endif