#include "../../include/error.hpp"
#include "../../include/master_key_c.hpp"
#include "../include/test.hpp"

using namespace std;

TEST(masterKeyTest, reset)
{
    // mkeyを初期化できるかテスト
    master_key_c mkey;
    ASSERT_FALSE(mkey.reset());

    // mkeyがファイルに暗号化されて出力されたか確認
    file_ptr_c fp;
    ASSERT_TRUE(fp.open(MASTER_KEY_LIST_FILE, "rb"));
    size_t read_size = 0;
    vector<u_char> buffer;
    const uint line_size = HASH_SIZE + AES_SIZE * 2;
    if (read_size = fread(buffer.data(), 1, line_size, fp.fp_) < 0) {
        ERROR("ファイルの読み込みサイズエラー");
        log::push_value(TO_STRING(read_size), read_size);
        FAIL();
    }
    vector<u_char> iv;
    vector<u_char> key;
    // iv, keyをコピー
    for (size_t i = 0; i < HASH_SIZE; i++) {
        iv[i]  = buffer[i + HASH_SIZE];
        key[i] = buffer[i + HASH_SIZE + AES_SIZE];
    }
}