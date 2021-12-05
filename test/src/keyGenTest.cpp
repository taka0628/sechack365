#include "../include/test.hpp"

using namespace std;

TEST(keyGenMethodTest, setUsbId)
{
    key_gen_c key;
    ASSERT_TRUE(key.set_usbID("1d6b:0002"));
    ASSERT_FALSE(key.set_usbID(""));
    ASSERT_FALSE(key.set_usbID("hoge"));
    ASSERT_FALSE(key.set_usbID("1d6b"));
    ASSERT_FALSE(key.set_usbID("0002"));
    ASSERT_FALSE(key.set_usbID("1d6:0002"));
}

TEST(keyGenMethodTest, setPass)
{
    key_gen_c key;
    ASSERT_TRUE(key.set_pass("hoge"));
    ASSERT_FALSE(key.set_pass(""));
}

TEST(keyGenMethodTest, canKeyGen)
{
    key_gen_c key;
    ASSERT_FALSE(key.canKeyGen());
    ASSERT_TRUE(key.set_pass("hoge"));
    ASSERT_FALSE(key.canKeyGen());
    ASSERT_TRUE(key.set_usbID("1d6b:0002"));
    ASSERT_TRUE(key.set_UsbSerial());
    ASSERT_TRUE(key.canKeyGen());
}

TEST(errorLogTest, printError)
{
    key_gen_c key;
    PRINT_ERROR_LOG("test");
}

TEST(keyGenMethodTest, setUsbSerial)
{
    key_gen_c key;
    ASSERT_FALSE(key.set_UsbSerial());
    ASSERT_TRUE(key.set_usbID("1d6b:0002"));
    ASSERT_TRUE(key.set_UsbSerial());
}

TEST(keyGenMethodTest, nonce)
{
    key_gen_c key;
    dynamic_mem_c buf;
    ASSERT_TRUE(key.set_nonce());
    ASSERT_FALSE(key.get_nonce(buf));

    buf.d_new(1);
    ASSERT_FALSE(key.get_nonce(buf));
    buf.d_new(NONCE_SIZE - 1);
    ASSERT_FALSE(key.get_nonce(buf));

    buf.d_new(NONCE_SIZE);
    ASSERT_TRUE(key.get_nonce(buf));
    buf.d_new(NONCE_SIZE * 2);
    ASSERT_FALSE(key.get_nonce(buf));
}

TEST(keyGenMethodTest, keyGen)
{
    TestLog_c test("鍵生成テスト");
    key_gen_c key;
    EXPECT_FALSE(key.new_key_gen());

    ASSERT_TRUE(key.set_pass("hoge"));
    EXPECT_FALSE(key.new_key_gen());

    ASSERT_TRUE(key.set_usbID("1d6b:0002"));
    EXPECT_FALSE(key.new_key_gen());

    ASSERT_TRUE(key.set_UsbSerial());
    ASSERT_TRUE(key.new_key_gen());
}

#if 1
TEST(keyGenMethodTest, getKey)
{
    TestLog_c test("鍵入手テスト");
    key_gen_c key;
    ASSERT_TRUE(key.set_pass("hoge"));
    ASSERT_TRUE(key.set_usbID("1d6b:0002"));
    ASSERT_TRUE(key.set_UsbSerial());
    ASSERT_TRUE(key.canKeyGen());
    ASSERT_TRUE(key.new_key_gen());

    dynamic_mem_c key_1;
    dynamic_mem_c key_2;
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
    key_check.set_pass("hoge");
    key_check.set_usbID("1d6b:0002");
    key_check.set_UsbSerial();
    key_check.canKeyGen();
    ASSERT_TRUE(key_check.key_gen());
    try {
        key_2 = key_check.get_key();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        FAIL();
    }

    EXPECT_FALSE(key_1.empty());
    EXPECT_FALSE(key_2.empty());
    for (size_t i = 0; i < key_1.size(); i++) {
        if (key_1.mem_[i] != key_2.mem_[i]) {
            FAIL();
        }
    }

    cout << "key1: ";
    SHA_c sha;
    cout << sha.str2hex(key_1);
    cout << "\n"
         << "key2: " << sha.str2hex(key_2) << endl;
}
#endif