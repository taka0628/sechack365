#include "../../include/error.hpp"
#include "../../include/master_key_c.hpp"
#include "../include/test.hpp"

using namespace std;

TEST(masterKeyTest, reset)
{
    // mkeyを初期化できるかテスト
    master_key_c mkey;
    ASSERT_TRUE(mkey.init());
    vector<u_char> master_key = mkey.get_key();

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
    dynamic_mem_c iv(AES_SIZE);
    dynamic_mem_c key(AES_SIZE);
    // iv, keyをコピー
    for (size_t i = 0; i < HASH_SIZE; i++) {
        iv.mem_[i]  = buffer[i + HASH_SIZE];
        key.mem_[i] = buffer[i + HASH_SIZE + AES_SIZE];
    }
    aes_c aes;
    dynamic_mem_c plain(AES_SIZE);
    dynamic_mem_c enc_plain(AES_SIZE);
    ASSERT_TRUE(enc_plain.from_vector(buffer));
    ASSERT_TRUE(aes.set_iv_key(iv, key));
    aes.decrypt(plain, enc_plain, aes_c::AES_bit_e::aes_256);
    for (size_t i = 0; i < AES_SIZE; i++) {
        if (plain.mem_[i] != master_key[i]) {
            ERROR("マスターキーが不一致");
            FAIL();
        }
    }
}