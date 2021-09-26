#include "../include/test.hpp"

TEST(DMem, copy)
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