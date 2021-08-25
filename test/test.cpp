#include "test.hpp"

using namespace std;

TEST(IsKeyAddTest, None){
    dynamic_mem_c hash(256), iv(256), key(256), temp(256);
    SHA_c sha;
    temp.mem[0] = 1;
    sha.sha2_cal(temp, hash, SHA_c::SHA2_bit::SHA_256);

    key_list_c testKey;
    ASSERT_FALSE(testKey.add_file(hash, iv, key));
}