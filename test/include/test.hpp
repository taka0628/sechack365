#ifndef ___TEST_HPP
#define ___TEST_HPP

#include "string"
#include "fstream"
#include "iostream"
#include "cstdio"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#define BUF 256

#include "gtest/gtest.h"
#include "openssl/rand.h"

#include "../../include/file_enc.hpp"
#include "../../include/dynamic_mem_c.hpp"
#include "../../include/sha_c.hpp"
#include "../../include/key_gen.hpp"
#include "../../include/device_c.hpp"

#define ERROR_TEST        \
	TestLog_c testLogIns; \
	testLogIns.errorTest()

#define NORMAL_TEST       \
	TestLog_c testLogIns; \
	testLogIns.correctTest()

#define TEST_END \
	testLogIns.~TestLog_c()

class TestLog_c
{
private:
	/* data */

public:
	TestLog_c();
	TestLog_c(const std::string comment);
	void errorTest();
	void correctTest();
	~TestLog_c();
};

#endif