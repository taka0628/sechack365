#include "../include/test.hpp"

using namespace std;

TEST(DMem, copyConst)
{
    dynamic_mem_c from;
    from.d_new(100);
    try {
        dynamic_mem_c to(from);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        ERROR_NO_COMMENT;
        FAIL();
    }
}

TEST(DMem, equal)
{
    dynamic_mem_c to, from;
    from.d_new(2);
    from.mem_[0] = 1;
    if (from.empty()) {
        FAIL();
    }
    to = from;
    if (from.empty()) {
        FAIL();
    }
    try {
        to.d_free();
        to.d_new(2);
        from.d_free();
        from.d_new(2);
        from.mem_[0] = 1;
        to           = from;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        FAIL();
    }
    EXPECT_FALSE(from.empty());
    EXPECT_FALSE(to.empty());
}

TEST(DMem, empty)
{
    dynamic_mem_c test;
    ASSERT_TRUE(test.empty());
    test.d_new(2);
    ASSERT_TRUE(test.empty());
    test.mem_[0] = 1;
    ASSERT_FALSE(test.empty());
}

TEST(DMem, CopyConstractor)
{
    dynamic_mem_c mem1(100);
    for (size_t i = 0; i < mem1.size(); i++) {
        mem1.mem_[i] = 3;
    }
    dynamic_mem_c mem2;
    mem2 = mem1;
    ASSERT_FALSE(mem2.empty());
    ASSERT_EQ(mem1.size(), mem2.size());
    for (size_t i = 0; i < mem2.size(); i++) {
        if (mem1.mem_[i] != mem2.mem_[i]) {
            FAIL();
        }
    }
}

TEST(DMem, toString)
{
    dynamic_mem_c nonce(NONCE_SIZE);
    file_ptr_c fp;
    ASSERT_TRUE(fp.open(NONCE_FILE, "rb"));
    fread(nonce.mem_, 1, NONCE_SIZE, fp.fp_);
    // std::cout << TO_STRING(nonce.to_string()) << " :" << nonce.to_string() << endl;
}