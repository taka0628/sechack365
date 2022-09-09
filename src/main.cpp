#include "../include/aes_c.hpp"
#include "../include/cmdline/cmdline.h"
#include "../include/error.hpp"
#include "../include/file_enc.hpp"
#include "../include/master_key_c.hpp"
#include <iostream>

using namespace std;

bool init(const cmdline::parser& cmd)
{
    if (!cmd.exist("usb-id") || !cmd.exist("password")) {
        ERROR_NO_COMMENT;
        cout << "初期化時には使用するusbIDとパスワードを入力してください" << endl;
        return false;
    }
    master_key_c mkey;
    if (!mkey.init(cmd.get<string>("usb-id"), cmd.get<string>("password"))) {
        cout << "初期化に失敗" << endl;
        return false;
    }
    key_list_c key_list;
    if (!key_list.init()) {
        cout << "鍵リストの初期化に失敗" << endl;
        return false;
    }
    if (!key_list.encrypt(mkey.get_master_key())) {
        cout << "鍵リストの暗号化に失敗" << endl;
        return false;
    }

    return true;
}

bool encrypt(const cmdline::parser& cmd)
{
    if (!cmd.exist("password") || !cmd.exist("file")) {
        ERROR_NO_COMMENT;
        cout << "暗号化時には使用するusbIDとパスワード,ファイルパスを入力してください" << endl;
        return false;
    }
    if (cmd.get<string>("password").empty() || cmd.get<string>("file").empty()) {
        return false;
    }

    device_c usb;
    if (!usb.set_usbID_form_file()) {
        cout << "USB IDを取得できません" << endl;
        return false;
    }
    if (!usb.has_serial(usb.get_usbID())) {
        cout << "USBのシリアル番号を取得できません" << endl;
        return false;
    }

    master_key_c mkey;
    //鍵リストの復号
    key_list_c keylist;
    if (!keylist.decrypt(mkey.get_master_key(usb.get_usbID(), cmd.get<string>("password")))) {
        cout << "鍵リストの復号に失敗" << endl;
        return false;
    }

    //暗号化
    file_enc_c file_enc;
    file_enc.set_file_path(cmd.get<string>("file"));
    if (!file_enc.is_file_exit()) {
        cout << "ファイルが存在しません" << endl;
        return false;
    }
    if (!file_enc.file_enc()) {
        return false;
    }

    if (!keylist.encrypt(mkey.get_master_key(usb.get_usbID(), cmd.get<string>("password")))) {
        return false;
    }
    return true;
}

bool decrypt(const cmdline::parser& cmd)
{
    if (!cmd.exist("password") || !cmd.exist("file")) {
        ERROR_NO_COMMENT;
        cout << "暗号化時には使用するusbIDとパスワード,ファイルパスを入力してください" << endl;
        return false;
    }
    if (cmd.get<string>("password").empty() || cmd.get<string>("file").empty()) {
        return false;
    }

    //ファイルが存在するか確認
    file_enc_c file_dec;
    file_dec.set_file_path(cmd.get<string>("file"));
    if (!file_dec.is_file_exit()) {
        cout << "ファイルが存在しません" << endl;
        return false;
    }

    device_c usb;
    if (!usb.set_usbID_form_file()) {
        cout << "USB IDを取得できません" << endl;
        return false;
    }
    if (!usb.has_serial(usb.get_usbID())) {
        cout << "USBのシリアル番号を取得できません" << endl;
        return false;
    }

    //鍵リストの復号
    master_key_c mkey;
    //鍵リストの復号
    key_list_c keylist;
    if (!keylist.decrypt(mkey.get_master_key(usb.get_usbID(), cmd.get<string>("password")))) {
        cout << "鍵リストの復号に失敗" << endl;
        return false;
    }

    //復号
    if (file_dec.file_dec() == false) {
        cout << "ファイルの復号に失敗" << endl;
        return false;
    }
    if (!keylist.encrypt(mkey.get_master_key(usb.get_usbID(), cmd.get<string>("password")))) {
        return false;
    }
    return true;
}

bool add_usb(const cmdline::parser& cmd)
{
    if (!cmd.exist("password") || !cmd.exist("usb-id")) {
        ERROR_NO_COMMENT;
        cout << "USBの登録にはパスワードとUSB IDが必要です" << endl;
        return false;
    }
    if (cmd.get<string>("password").empty()) {
        return false;
    }
    master_key_c mkey;
    device_c usb;
    if (!usb.set_usbID_form_file()) {
        ERROR("USBIDをセットできません");
        return false;
    }
    if (mkey.add_authorization(usb.get_usbID(), cmd.get<string>("password"), cmd.get<string>("usb-id"))) {
        ERROR("USB IDを追加できません");
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    // create a parser
    cmdline::parser a;
    // mode
    a.add("init", 'i', "init");
    a.add("enc", 'e', "file encrypt");
    a.add("dec", 'd', "file decrypt");
    a.add("add-usb", '0', "add usb id");

    // option
    a.add<string>("usb-id", 'u', "usb id", false);
    a.add<string>("password", 'p', "password", false);
    a.add<string>("file", 'f', "file path", false);

    a.parse_check(argc, argv);
    if (!a.parse(argc, argv)) {
        cout << a.error() << endl;
        return 1;
    }

    if (a.exist("init") && !a.exist("enc") && !a.exist("dec") && !a.exist("add-usb")) {
        if (!init(a)) {
            return 1;
        }
    } else if (!a.exist("init") && a.exist("enc") && !a.exist("dec") && !a.exist("add-usb")) {
        if (!encrypt(a)) {
            return 1;
        }
    } else if (!a.exist("init") && !a.exist("enc") && a.exist("dec") && !a.exist("add-usb")) {
        if (!decrypt(a)) {
            return 1;
        }
    } else if (!a.exist("init") && !a.exist("enc") && !a.exist("dec") && a.exist("add-usb")) {
        if (!add_usb(a)) {
            return 1;
        }
    }

    return 0;
}
