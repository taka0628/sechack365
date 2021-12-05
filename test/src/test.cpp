#include "../include/test.hpp"

using namespace std;

void create_rand_hash(dynamic_mem_c& hash)
{
    dynamic_mem_c temp(hash.size());
    RAND_bytes(temp.mem_, hash.size());

    SHA_c sha;
    sha.sha2_cal(temp, hash, SHA_c::SHA2_bit::SHA_256);
}

TEST(KeyListTest, TrueProcess)
{
    int crypt_size = 256 / 8;
    dynamic_mem_c hash(crypt_size), iv(crypt_size), key(crypt_size),
        temp(crypt_size);
    SHA_c sha;
    temp.mem_[0] = 1;
    sha.sha2_cal(temp, hash, SHA_c::SHA2_bit::SHA_256);

    file_ptr_c fp;
    key_list_c testKey;
    fp.open(testKey.get_file_name(), "wb");
    fp.~file_ptr_c();

    for (auto i = 0; i < 3; i++) {
        create_rand_hash(hash);
        create_rand_hash(iv);
        create_rand_hash(key);
        ASSERT_TRUE(testKey.add_file(hash, iv, key));
    }
    ASSERT_TRUE(testKey.add_file(hash, iv, key));

    ASSERT_TRUE(testKey.pop_file(hash, iv, key));
    string out_hash, out_iv, out_key;
    for (size_t i = 0; i < hash.size(); i++) {
        out_hash.push_back(hash.mem_[i]);
        out_iv.push_back(iv.mem_[i]);
        out_key.push_back(key.mem_[i]);
    }
    cout << "hash: " << sha.str2hex(out_hash) << endl;
    cout << "iv: " << sha.str2hex(out_iv) << endl;
    cout << "key: " << sha.str2hex(out_key) << endl;
}

TEST(KeyListTest, FalseProcess)
{
    int crypt_size = 256 / 8;
    dynamic_mem_c hash(crypt_size), iv(crypt_size), key(crypt_size),
        temp(crypt_size);
    SHA_c sha;
    key_list_c testKey;
    ASSERT_FALSE(testKey.add_file(hash, iv, key));
    ASSERT_FALSE(testKey.pop_file(hash, iv, key));

    create_rand_hash(temp);
    ASSERT_FALSE(testKey.pop_file(temp, iv, key));
}

TEST(FileEncTest, Normal)
{
    const string test_filepath("/home/taka/github/2021_sec/test/data.jpg");
    file_enc_c file_enc;
    ASSERT_TRUE(file_enc.set_file_path(test_filepath));
    ASSERT_TRUE(file_enc.is_file_exit());
    ASSERT_TRUE(file_enc.file_enc());

    ASSERT_TRUE(file_enc.set_file_path(test_filepath + ".enc"));
    ASSERT_TRUE(file_enc.file_dec());
}

TEST(FileEncTest, ErrorProcess)
{
    const string error_filepath(
        "/home/taka/github/2021_sec/test/hogehoge.huga");
    file_enc_c file_enc;
    ASSERT_FALSE(file_enc.set_file_path(error_filepath));
    ASSERT_FALSE(file_enc.is_file_exit());
    ASSERT_FALSE(file_enc.file_enc());

    ASSERT_FALSE(file_enc.set_file_path(error_filepath + ".enc"));
    ASSERT_FALSE(file_enc.file_dec());
}

#if 0
TEST(IGNORESandBox, TestRun)
{
	FILE *fp;
	string cmdline = "sudo lsusb -d 8564:1000  -v | grep iSerial | awk '{print $3}'";
	if ((fp = popen(cmdline.c_str(), "r")) == NULL)
	{
		FAIL();
		perror("can not exec commad");
	}
	char buf[BUF];

	while (!feof(fp))
	{
		fgets(buf, sizeof(buf), fp);
		printf("=> %s", buf);
	}

	(void)pclose(fp);
}
#endif