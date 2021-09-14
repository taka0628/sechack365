#include "test.hpp"

TEST(keyGenMethodTest, getUsbSerial)
{
	key_gen_c key;
	ASSERT_TRUE(key.getUsbSerial());
}
