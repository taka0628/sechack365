#include "../include/device_c.hpp"

device_c::device_c() {}

device_c::~device_c() {}

using namespace std;

namespace local {
vector<string> cmdline2List(string cmd) {
    FILE *fp;
    vector<string> cmdstring;
    if ((fp = popen(cmd.c_str(), "r")) == NULL) {
        PRINT_ERROR_LOG("can not exec commad");
        cmdstring.clear();
        return cmdstring;
    }
    char cmd_buf[256];
    while (fgetc(fp) != EOF) {
        fgets(cmd_buf, sizeof(cmd_buf), fp);
        cmdstring.push_back(cmd_buf);
    }

    if (cmdstring.empty()) {
        PRINT_ERROR_LOG("コマンドラインから出力を得られませんでした");
        cmdstring.clear();
        return cmdstring;
    }
    (void)pclose(fp);

    // 改行文字を処理
    for (string &in : cmdstring) {
        if (in.find("\n", 1) != string::npos) {
            in.erase(in.find("\n", 1), 1);
        }
    }
    return cmdstring;
}
string cmdline(string cmd) {
    FILE *fp;
    string cmdstring;
    if ((fp = popen(cmd.c_str(), "r")) == NULL) {
        PRINT_ERROR_LOG("can not exec commad");
        return "";
    }
    char cmd_buf[256];
    fgets(cmd_buf, sizeof(cmd_buf), fp);
    cmdstring += cmd_buf;

    if (cmdstring.empty()) {
        PRINT_ERROR_LOG("コマンドラインから出力を得られませんでした");
        return "";
    }
    (void)pclose(fp);

    // 改行文字を処理
    if (cmdstring.find("\n", 1) != string::npos) {
        cmdstring.erase(cmdstring.find("\n", 1), 1);
    }
    return cmdstring;
}
}  // namespace local
vector<string> device_c::get_usbList() const {
    string cmdline = "lsusb | cut -d ' ' -f 5- ";
    std::vector<std::string> usb_list;
    usb_list = local::cmdline2List(cmdline);
    return usb_list;
}

bool device_c::set_usbID(const string usbID) {
    if (usbID.empty() || usbID.size() != 9) {
        PRINT_ERROR_LOG("usbIDが不正");
        return false;
    }
    // sudo lsusb -d 1d6b:0002 -v | grep iSerial | awk '{print $3}'
    string cmdline = "sudo lsusb -d ";
    cmdline += usbID;
    cmdline += " -v | grep iSerial | awk '{print $3}' | tail -n -1";

    string temp = local::cmdline(cmdline);
    try {
        // 4文字未満のシリアル番号はエラーとみなす
        if (temp.empty() || temp.size() < 4) {
            PRINT_ERROR_LOG("コマンドラインから出力を得られませんでした");
            return false;
        } else {
            if (temp.find("\n", 1) != string::npos) {
                temp.erase(temp.find("\n", 1));
            }
            this->usb_serial_ = temp;
            this->usb_id_ = usbID;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        PRINT_ERROR_LOG(e.what());
    }

    return true;
}

string device_c::get_usbID() const {
    if (this->usb_id_.empty()) {
        return "";
    }
    return this->usb_id_;
}

string device_c::get_usbSerial() const {
    if (this->usb_serial_.empty()) {
        return "";
    }
    return this->usb_serial_;
}

uint32_t device_c::get_usb_cnt() const {
    uint32_t usb_size =
        static_cast<uint32_t>(stoi(local::cmdline("lsusb | wc -l")));
    return usb_size;
}