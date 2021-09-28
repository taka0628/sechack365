#include "../include/test.hpp"

using namespace std;

TestLog_c::TestLog_c(string comment)
{
	string text = "===";
	text += comment;
	text += "===";
	PRINT_ERROR_LOG(text.c_str());
}

TestLog_c::~TestLog_c()
{
	PRINT_ERROR_LOG("===TEST END===");
}