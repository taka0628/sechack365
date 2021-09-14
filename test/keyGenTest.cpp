#include "test.hpp"

TEST(keyGenMethodTest, getUsbSerial)
{
	key_gen_c key;
	ASSERT_TRUE(key.getUsbSerial());
}

TEST(errorLogTest, printError)
{
	key_gen_c key;
	PRINT_ERROR_LOG("test");
}
