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
	key_gen_c key;
	ASSERT_TRUE(key.set_pass("hoge"));
	ASSERT_TRUE(key.set_usbID("1d6b:0002"));
	ASSERT_TRUE(key.set_UsbSerial());
	ASSERT_TRUE(key.new_key_gen());

	dynamic_mem_c temp;
	try
	{
		temp = key.get_key();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		FAIL();
	}
	if (temp.is_empty())
	{
		FAIL();
	}

	cout << "key: ";
	SHA_c sha;
	cout << sha.str2hex(temp);
	cout << endl;
}
#endif