#ifndef ___MACRO_HPP
#define ___MACRO_HPP

#include "error.hpp"

// エラー用マクロ
#define ERROR(comment)                                                                   \
    printf("[ERROR]\n\t__%s__/__%s: %d\n\t%s\n", __FILE__, __func__, __LINE__, comment); \
    log::push_log(comment, __FILE__, __func__, __LINE__)

#define ERROR_NO_COMMENT                                                  \
    printf("[ERROR]\n\t__%s__/__%s: %d\n", __FILE__, __func__, __LINE__); \
    log::push_log("", __FILE__, __func__, __LINE__)

#define PRINT_ERROR_LOG(comment) \
    log::push_log(comment, __FILE__, __func__, __LINE__)

#define TO_STRING(VariableName) #VariableName

// -----------------------------------------------------------------------
// 定数
// 処理するファイルパスの上限
#define FILE_PATH_SIZE_LIM 500

// AES, HASHのビットサイズ
#define ___AES_BIT 256
#define ___HASH_BIT 256
// bit -> byte への変換
#define HASH_SIZE ___HASH_BIT / 8
#define AES_SIZE ___AES_BIT / 8

// ----------------------------------------------------------------------------
// ファイル名
// 鍵リストを暗号化する際に使用するバッファファイル
#define BUFFER_FILE_NAME "buffer_file_key_list"

// 暗号化の際に使用するバッファファイル
#define CRYPT_BUFFER_FILE "crypt_temp"

// 鍵リストのファイル名
#define KEY_FILE_NAME "keyList"

#define KEY_HASH_FILE "key_hash"

#define ERROR_LOG_FILE "errorLog.txt"

constexpr char MASTER_KEY_LIST_FILE[] = "mkeyList";

// ------------------------------------------------------------------------
// nonce設定
#define NONCE_FILE "nonce"
#define NONCE_SIZE 1024 / 8

#endif