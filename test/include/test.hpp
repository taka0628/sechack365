#ifndef ___TEST_HPP
#define ___TEST_HPP

#include "string"
#include "fstream"
#include "iostream"
#include "cstdio"
#include <stdio.h>
#include <stdlib.h>
#define BUF 256

#include "gtest/gtest.h"
#include "openssl/rand.h"

#include "../../include/file_enc.hpp"
#include "../../include/dynamic_mem_c.hpp"
#include "../../include/sha_c.hpp"
#include "../../include/key_gen.hpp"

#define ERROR_TEST \
	push_error_log("===エラーテスト開始===", __FILE__, __func__, __LINE__)

#define NORMAL_TEST \
	push_error_log("===動作テスト開始===", __FILE__, __func__, __LINE__)

class TestLog_c
{
private:
	/* data */
public:
	TestLog_c(std::string comment);
	~TestLog_c();
};

#endif