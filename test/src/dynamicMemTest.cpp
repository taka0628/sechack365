#include "../include/test.hpp"

TEST(DMem, copyConst)
{
    dynamic_mem_c from;
    from.d_new(100);
    try
    {
        dynamic_mem_c to(from);
    }
    catch (const std::exception &e)
    {
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
    if (from.empty())
    {
        FAIL();
    }
    to = from;
    if (from.empty())
    {
        FAIL();
    }
    try
    {
        to.d_free();
        to.d_new(2);
        from.d_free();
        from.d_new(2);
        from.mem_[0] = 1;
        to = from;
    }
    catch (const std::exception &e)
    {
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