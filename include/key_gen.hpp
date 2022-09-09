#ifndef ___KEY_GEN_HPP
#define ___KEY_GEN_HPP

#include <cstdio>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <openssl/rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

#include "dynamic_mem_c.hpp"
#include "error.hpp"
#include "file_enc.hpp"
#include "macro.hpp"
#include "sha_c.hpp"

#if LOCAL_TEST
#include "device_c.hpp"
#else
#include "../test/include/usb_debug.hpp"
#endif

class key_gen_c {
private:
#if LOCAL_TEST
    device_c usb_;
#else
    usb_debug usb_;
#endif

    dynamic_mem_c key_;
    std::string pass_;

    std::string get_pass() const;
    std::string get_usbSerial() const;
    std::string get_usbID() const;

    bool get_nonce(dynamic_mem_c& to) const;
    bool generate_nonce() const;

public:
    key_gen_c();
    ~key_gen_c();
    key_gen_c(const key_gen_c&)           = delete;
    key_gen_c& operator=(const device_c&) = delete;

    // bool new_key_gen();
    bool key_gen();

    bool set_pass(std::string const pass);
    // パスワードは正しいか？
    // ハッシュ値で比較
    bool is_pass_correct() const;
    // パスワードのハッシュ値をファイルに書き込む
    bool set_pass2file(std::string const pass) const;

    // usbIDとシリアル番号の設定を行う
    bool set_usb(std::string const id);

    dynamic_mem_c get_key() const;
    bool canKeyGen() const;
};

#endif