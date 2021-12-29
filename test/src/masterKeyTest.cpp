#include "../../include/master_key_c.hpp"
#include "../include/test.hpp"

using namespace std;

TEST(masterKeyTest, getMasterKey)
{
    master_key_c mkey;
    mkey.get_master_key();
}