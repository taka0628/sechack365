#ifndef ___MASTER_KEY_HPP
#define ___MASTER_KEY_HPP

#include "aes_c.hpp"
#include "device_c.hpp"
#include "key_gen.hpp"
#include "macro.hpp"
#include "openssl/rand.h"
#include "sha_c.hpp"

#include <assert.h>
#include <cstdio>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

class master_key_c {
private:
    master_key_c(const master_key_c&);
    std::vector<u_char> master_key_;

public:
    master_key_c();
    ~master_key_c();
    // Mkeyが正しく取得できない場合は異常終了
    std::vector<u_char> get_key() const;
    // Mkeyのハッシュ値を取得
    std::vector<u_char> get_hash() const;
    // 認証情報を含みMKeyをリセット
    bool init(std::string usb_id, std::string pass_word);
    // Mkeyが復号され、メンバ変数に正しく格納されているか確認
    bool isCorrect() const;
    // Mkeyに使用する認証情報を追加
    bool add_authorization(const std::vector<u_char> current_key, const std::vector<u_char> new_key);
};

#endif