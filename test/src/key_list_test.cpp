#include "../include/test.hpp"

using namespace std;

TEST(KeyListCryptTest, EncryptTest)
{
    key_list_c keyList;
    dynamic_mem_c key;
    string pass("hoge");
    SHA_c sha;
    string key_st = sha.sha2_cal(pass, SHA_c::SHA2_bit::SHA_256);
    key.d_new(SHA256_DIGEST_LENGTH);
    for (size_t i = 0; i < key.size(); i++) {
        key.mem_[i] = (unsigned char)key_st[i];
    }
    cout << sha.str2hex(key_st) << endl;
    cout << sha.str2hex(sha.sha2_cal(key_st, SHA_c::SHA2_bit::SHA_256)) << endl;

    ASSERT_TRUE(keyList.encrypt(key));
    ASSERT_TRUE(keyList.decrypt(key));
}

TEST(KeyListCryptError, DISABLED_KeySize)
{
    key_list_c keyList;
    dynamic_mem_c key;
    // 鍵のサイズが違う
    key.d_new(128 / 8);
    RAND_bytes(key.mem_, 128 / 8);
    ASSERT_FALSE(keyList.encrypt(key));
    ASSERT_FALSE(keyList.decrypt(key));
}

TEST(KeyListCryptError, DISABLED_NullKey)
{
    key_list_c keyList;
    dynamic_mem_c key;
    key.d_new(AES_SIZE);
    ASSERT_FALSE(keyList.encrypt(key));
    ASSERT_FALSE(keyList.decrypt(key));
}

TEST(KeyListCryptError, DISABLED_DiffKey)
{
    key_list_c keyList;
    dynamic_mem_c key;
    key.d_new(AES_SIZE);
    // 鍵が異なる
    RAND_bytes(key.mem_, key.size());
    ASSERT_TRUE(keyList.encrypt(key));

    RAND_bytes(key.mem_, key.size());
    ASSERT_FALSE(keyList.decrypt(key));
}