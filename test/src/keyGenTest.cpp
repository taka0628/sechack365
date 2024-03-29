#include "../include/test.hpp"

using namespace std;

TEST(keyGenMethodTest, setPass)
{
    key_gen_c key;
    ASSERT_TRUE(key.set_pass("hoge"));
    ERROR_TEST;
    ASSERT_FALSE(key.set_pass(""));
}

TEST(keyGenMethodTest, canKeyGen)
{
    key_gen_c key;
    string usbID = "8564:1000";
    ASSERT_TRUE(key.set_usb(usbID));
    ASSERT_TRUE(key.set_pass("hoge"));
    ASSERT_TRUE(key.canKeyGen());
    key.~key_gen_c();

    ERROR_TEST;
    key_gen_c keyError;
    ASSERT_FALSE(keyError.canKeyGen());
    ASSERT_TRUE(keyError.set_pass("hoge"));
    TestLog_c test("ASSERT");
    ASSERT_FALSE(keyError.canKeyGen());
}

TEST(errorLogTest, printError)
{
    key_gen_c key;
    PRINT_ERROR_LOG("test");
}

TEST(keyGenMethodTest, nonce)
{
    key_gen_c key;
    dynamic_mem_c buf;
}
TEST(keyGenMethodTest, keyGen)
{
    TestLog_c test("鍵生成テスト");
    key_gen_c key;
}

#if 1
TEST(keyGenMethodTest, getKey)
{
    TestLog_c test("鍵入手テスト");
    key_gen_c key;
    ASSERT_TRUE(key.set_pass("hoge"));
    ASSERT_TRUE(key.set_usb("8564:1000"));
    ASSERT_TRUE(key.canKeyGen());
    ASSERT_TRUE(key.key_gen());

    dynamic_mem_c key_1(AES_SIZE);
    dynamic_mem_c key_2(AES_SIZE);
    try {
        key_1 = key.get_key();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        FAIL();
    }
    if (key_1.empty()) {
        FAIL();
    }

    key_gen_c key_check;
    ASSERT_TRUE(key_check.set_pass("hoge"));
    ASSERT_TRUE(key_check.set_usb("8564:1000"));
    ASSERT_TRUE(key_check.canKeyGen());
    ASSERT_TRUE(key_check.key_gen());
    try {
        key_2 = key_check.get_key();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        FAIL();
    }

    for (size_t i = 0; i < key_1.size(); i++) {
        if (key_1.mem_[i] != key_2.mem_[i]) {
            FAIL();
        }
    }
}
#endif

TEST(keyGenMethodTest, PasswordCheck)
{
    TestLog_c test("パスワードチェックテスト");
    key_gen_c keygen;
    ASSERT_TRUE(keygen.set_pass2file("hoge"));
    ASSERT_TRUE(keygen.set_pass("hoge"));
    ASSERT_TRUE(keygen.is_pass_correct());

    ERROR_TEST;
    ASSERT_TRUE(keygen.set_pass("huga"));
    ASSERT_FALSE(keygen.is_pass_correct());
}