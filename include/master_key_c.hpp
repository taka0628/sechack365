#ifndef ___MASTER_KEY_HPP
#define ___MASTER_KEY_HPP

#include "aes_c.hpp"
#include "device_c.hpp"
#include "error.hpp"
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
    dynamic_mem_c master_key_;
    // 暗号化された鍵をファイルへ出力
    bool push_key(const dynamic_mem_c enc_mkey, const dynamic_mem_c iv, const dynamic_mem_c key) const;
    // ファイルから暗号化された鍵を取得
    dynamic_mem_c get_key_from_keylist(const dynamic_mem_c& key_hash) const;
    // mkeyを暗号化し、ファイルへ保存
    bool enc_mkey(const dynamic_mem_c key) const;

public:
    master_key_c();
    ~master_key_c();
    // Mkeyが正しく取得できない場合は異常終了
    dynamic_mem_c get_key() const;
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