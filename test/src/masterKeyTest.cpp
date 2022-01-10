#include "../../include/error.hpp"
#include "../../include/master_key_c.hpp"
#include "../include/test.hpp"

using namespace std;

TEST(masterKeyTest, generateCryptKey)
{
    TestLog_c test("マスターキーの暗号鍵生成テスト");
    master_key_c mkey;
    dynamic_mem_c crypt_mkey = mkey.generate_crypt_key("1d6b:0003", "hoge");
    ASSERT_EQ(crypt_mkey.size(), AES_SIZE);

    ERROR_TEST;
    ASSERT_EQ(mkey.generate_crypt_key("hoge", "").size(), 0);
    ASSERT_EQ(mkey.generate_crypt_key("11111", "").size(), 0);
    ASSERT_EQ(mkey.generate_crypt_key("", "").size(), 0);
    ASSERT_EQ(mkey.generate_crypt_key("11", "hoge").size(), 0);
}

TEST(masterKeyTest, reset)
{
    TestLog_c testname("マスターキー初期化テスト");
    // mkeyを初期化できるかテスト
    master_key_c mkey;
    ASSERT_TRUE(mkey.init("1d6b:0003", "hoge"));
    dynamic_mem_c master_key = mkey.get_master_key();

    // mkeyがファイルに暗号化されて出力されたか確認
    file_ptr_c fp;
    ASSERT_TRUE(fp.open(MASTER_KEY_LIST_FILE, "rb"));
    size_t read_size     = 0;
    const uint line_size = HASH_SIZE + AES_SIZE * 2;
    dynamic_mem_c buffer(line_size);
    if ((read_size = fread(buffer.mem_, 1, line_size, fp.fp_)) < 0) {
        ERROR("ファイルの読み込みサイズエラー");
        log::push_value(TO_STRING(read_size), read_size);
        FAIL();
    }
    dynamic_mem_c iv(AES_SIZE);
    dynamic_mem_c enc_mkey(AES_SIZE);

    // iv, keyをコピー
    for (size_t i = 0; i < HASH_SIZE; i++) {
        iv.mem_[i]       = buffer.mem_[i + HASH_SIZE];
        enc_mkey.mem_[i] = buffer.mem_[i + HASH_SIZE + AES_SIZE];
    }
    aes_c aes;
    dynamic_mem_c plain(AES_SIZE);
    dynamic_mem_c crypt_key = mkey.generate_crypt_key("1d6b:0003", "hoge");
    ASSERT_EQ(crypt_key.size(), AES_SIZE);
    ASSERT_TRUE(aes.set_iv_key(iv, crypt_key));
    aes.decrypt(plain, enc_mkey, aes_c::AES_bit_e::aes_256);
    for (size_t i = 0; i < AES_SIZE; i++) {
        if (plain.mem_[i] != master_key.mem_[i]) {
            ERROR("マスターキーが不一致");
            PUSH_VALUE(plain.to_string());
            PUSH_VALUE(plain.size());
            PUSH_VALUE(master_key.to_string());
            PUSH_VALUE(master_key.size());
            FAIL();
        }
    }
}

TEST(masterKeyTest, decMey)
{
    TestLog_c test("マスターキー復号テスト");
    master_key_c mkey;
    ASSERT_TRUE(mkey.init("1d6b:0003", "hoge"));
    dynamic_mem_c master_key_origin = mkey.get_master_key();

    dynamic_mem_c master_key_dec = mkey.get_master_key("1d6b:0003", "hoge");
    ASSERT_EQ(master_key_dec.size(), AES_SIZE);
    for (size_t i = 0; i < AES_SIZE; i++) {
        if (master_key_origin.mem_[i] != master_key_dec.mem_[i]) {
            cout << "master_key_origin: " << master_key_origin.to_string() << "\n"
                 << "master_key_dec: " << master_key_dec.to_string() << endl;
            FAIL();
        }
    }

    ERROR_TEST;
    dynamic_mem_c temp = mkey.get_master_key("hoge", "hoge");
    ASSERT_EQ(temp.size(), 0);
}