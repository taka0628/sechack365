#ifndef ___TEST_HPP
#define ___TEST_HPP

#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <vector>

#include "cstdio"
#include "fstream"
#include "iostream"
#include "string"
#define BUF 256

#include "../../include/device_c.hpp"
#include "../../include/dynamic_mem_c.hpp"
#include "../../include/file_enc.hpp"
#include "../../include/key_gen.hpp"
#include "../../include/sha_c.hpp"
#include "googletest/include/gtest/gtest.h"
#include "openssl/rand.h"

#define ERROR_TEST        \
    TestLog_c testLogIns; \
    testLogIns.errorTest()

#define NORMAL_TEST       \
    TestLog_c testLogIns; \
    testLogIns.correctTest()

#define TEST_END testLogIns.~TestLog_c()

class TestLog_c {
private:
    /* data */

public:
    TestLog_c();
    TestLog_c(const std::string comment);
    void errorTest();
    void correctTest();
    ~TestLog_c();
};
namespace local {
std::string test_cmdline(const std::string cmd);
}
#endif