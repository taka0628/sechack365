#ifndef ___KEY_LIST_C_HPP
#define ___KEY_LIST_C_HPP

#include "string"
#include "cstdio"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "dynamic_mem_c.hpp"
#include "file_ptr_c.hpp"
#include "macro.hpp"

#define ___AES_BIT 256
#define ___HASH_BIT 256
#define HASH_SIZE ___HASH_BIT / 8
#define AES_SIZE ___AES_BIT / 8
#define KEY_FILE_NAME "keyList"

class key_list_c
{
private:
    key_list_c(const key_list_c &);
    const std::string key_file_name_ = KEY_FILE_NAME;

    // 該当ハッシュ値のファイルをデータベースから削除し、以降のファイルを埋める
    bool plug(const dynamic_mem_c hash);

public:
    key_list_c();
    ~key_list_c();

    std::string get_file_name() const;

    // ハッシュ値でファイルを検索し、iv, keyを取得
    bool pop_file(dynamic_mem_c const &hash, dynamic_mem_c &iv, dynamic_mem_c &key);
    // データベースにファイルを登録
    bool add_file(dynamic_mem_c const &hash, dynamic_mem_c const &iv, dynamic_mem_c const &key) const;
};

#endif