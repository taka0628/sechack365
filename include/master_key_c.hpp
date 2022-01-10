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

/*
MasterKeyListの構造
    暗号化されたマスターキーの復号鍵のハッシュ値
    iv
    暗号化されたマスターキー
*/

class master_key_c {
private:
    master_key_c(const master_key_c&);
    dynamic_mem_c master_key_;
    dynamic_mem_c iv_;
    // 暗号化された鍵をファイルへ出力
    bool push_key(const dynamic_mem_c crypt_key, const dynamic_mem_c iv, const dynamic_mem_c enc_mkey) const;
    // MkeyListからivと暗号化されたマスターキーを取得
    bool get_key_from_file(const dynamic_mem_c hash, dynamic_mem_c& iv, dynamic_mem_c& enc_key) const;
    // mkeyを暗号化
    dynamic_mem_c enc_mkey(const dynamic_mem_c key);
    // mkeyを復号
    bool dec_mkey(const dynamic_mem_c crypt_key, const dynamic_mem_c enc_mkey, const dynamic_mem_c iv);

public:
    master_key_c();
    ~master_key_c();
    // Mkeyが正しく取得できない場合は異常終了
    dynamic_mem_c get_master_key() const;
    // mkeyListから対象のマスターキーを取得して復号する
    dynamic_mem_c get_master_key(const std::string usb_id, const std::string password);
    dynamic_mem_c get_iv() const;
    // mkeyを暗号化するための鍵生成
    dynamic_mem_c generate_crypt_key(const std::string usb_id, const std::string password) const;
    // 認証情報を含みMKeyをリセット
    bool init(std::string usb_id, std::string pass_word);
    // Mkeyに使用する認証情報を追加
    bool add_authorization(const std::vector<u_char> current_key, const std::vector<u_char> new_key);
};

#endif