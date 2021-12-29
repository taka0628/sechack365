#ifndef ___MASTER_KEY_HPP
#define ___MASTER_KEY_HPP

#include "aes_c.hpp"
#include "macro.hpp"
#include "openssl/rand.h"
#include "sha_c.hpp"

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
    master_key_c(/* args */);
    ~master_key_c();
    // Mkeyが正しく取得できない場合は異常終了
    std::vector<u_char> get_key() const;
    // 認証情報を含みMKeyをリセット
    bool reset();
    // Mkeyが復号され、メンバ変数に正しく格納されているか確認
    bool isCorrect() const;
    // Mkeyに使用する認証情報を追加
    bool add_authorization(const std::vector<u_char> current_key, const std::vector<u_char> new_key);
};

#endif