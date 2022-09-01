#ifndef ___MACRO_HPP
#define ___MACRO_HPP

#include "error.hpp"

// エラー用マクロ

// エラーメッセージをコンソールに出力するか
// 1: 出力, 0: ログファイルにのみ出力
#define ___MACRO_IS_PRINTF 0

#if ___MACRO_IS_PRINTF

#define ERROR(comment)                                                                   \
    printf("[ERROR]\n\t__%s__/__%s: %d\n\t%s\n", __FILE__, __func__, __LINE__, comment); \
    ErrorMsg::push_log(comment, __FILE__, __func__, __LINE__)

#define ERROR_NO_COMMENT                                                  \
    printf("[ERROR]\n\t__%s__/__%s: %d\n", __FILE__, __func__, __LINE__); \
    ErrorMsg::push_log("", __FILE__, __func__, __LINE__)

#else

#define ERROR(comment) \
    ErrorMsg::push_log(comment, __FILE__, __func__, __LINE__)

#define ERROR_NO_COMMENT \
    ErrorMsg::push_log("", __FILE__, __func__, __LINE__)

#endif

#define PRINT_ERROR_LOG(comment) \
    ErrorMsg::push_log(comment, __FILE__, __func__, __LINE__)

#define PUSH_VALUE(arg) \
    ErrorMsg::push_value(TO_STRING(arg), arg)

#define TO_STRING(VariableName) (#VariableName)

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
// 鍵リストの共通鍵のハッシュ値
#define KEY_HASH_FILE "key_hash"
// パスワードのハッシュ値
#define PASSWORD_HASH_FILE "pass_hash"
// USB IDのファイル名
#define USB_ID_LIST "usb_ID"

#define ERROR_LOG_FILE "errorLog.txt"

constexpr char MASTER_KEY_LIST_FILE[] = "mkeyList";

// ------------------------------------------------------------------------
// nonce設定
#define NONCE_FILE "nonce"
#define NONCE_SIZE 1024 / 8

#endif