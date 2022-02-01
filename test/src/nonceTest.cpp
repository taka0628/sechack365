#include "../include/test.hpp"

using namespace std;

TEST(NonceTest, getNonce)
{
    file_ptr_c fp;
    ASSERT_TRUE(fp.open(NONCE_FILE, "rb"));
    dynamic_mem_c nonce(NONCE_SIZE);
    int read_size = fread(nonce.mem_, 1, NONCE_SIZE, fp.fp_);
    ASSERT_EQ(read_size, NONCE_SIZE);
}