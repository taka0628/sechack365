#include "../include/test.hpp"

using namespace std;

TestLog_c::TestLog_c() { }

TestLog_c::TestLog_c(const string comment)
{
    string text = "===";
    text += comment;
    text += "===";
    PRINT_ERROR_LOG(text.c_str());
}

TestLog_c::~TestLog_c() { PRINT_ERROR_LOG("===TEST END==="); }

void TestLog_c::correctTest()
{
    string text = "===";
    text += "Correct Test";
    text += "===";
    PRINT_ERROR_LOG(text.c_str());
}

void TestLog_c::errorTest()
{
    string text = "===";
    text += "Error Test";
    text += "===";
    PRINT_ERROR_LOG(text.c_str());
}
