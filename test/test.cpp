#include "test.hpp"

using namespace std;

TEST(KeyListTest, TrueProcess)
{
    int crypt_size = 256 / 8;
    dynamic_mem_c hash(crypt_size), iv(crypt_size), key(crypt_size), temp(crypt_size);
    SHA_c sha;
    temp.mem[0] = 1;
    sha.sha2_cal(temp, hash, SHA_c::SHA2_bit::SHA_256);

    file_ptr_c fp;
    key_list_c testKey;
    fp.open(testKey.get_file_name(), "wb");
    fp.~file_ptr_c();
    ASSERT_TRUE(testKey.add_file(hash, iv, key));

    temp.mem[1] = 1;
    sha.sha2_cal(temp, hash, SHA_c::SHA2_bit::SHA_256);
    temp.mem[2] = 1;
    sha.sha2_cal(temp, iv, SHA_c::SHA2_bit::SHA_256);
    temp.mem[3] = 1;
    sha.sha2_cal(temp, key, SHA_c::SHA2_bit::SHA_256);
    ASSERT_TRUE(testKey.add_file(hash, iv, key));

    ASSERT_TRUE(testKey.pop_file(hash, iv, key));
    string out_hash, out_iv, out_key;
    for (int i = 0; i < hash.get_size(); i++)
    {
        out_hash.push_back(hash.mem[i]);
        out_iv.push_back(iv.mem[i]);
        out_key.push_back(key.mem[i]);
    }
    cout << "hash: " << sha.str2hex(out_hash) << endl;
    cout << "iv: " << sha.str2hex(out_iv) << endl;
    cout << "key: " << sha.str2hex(out_key) << endl;
}

TEST(KeyListTest, FalseProcess)
{
    int crypt_size = 256 / 8;
    dynamic_mem_c hash(crypt_size), iv(crypt_size), key(crypt_size), temp(crypt_size);
    SHA_c sha;
    temp.mem[0] = 1;
    sha.sha2_cal(temp, hash, SHA_c::SHA2_bit::SHA_256);

    key_list_c testKey;
    ASSERT_FALSE(testKey.pop_file(temp, iv, key));
}