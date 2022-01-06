#include "../include/test.hpp"

using namespace std;

string local::test_cmdline(const string cmd)
{
    FILE* fp;
    string cmdstring;
    if ((fp = popen(cmd.c_str(), "r")) == NULL) {
        PRINT_ERROR_LOG("can not exec commad");
        return "";
    }
    char cmd_buf[256];
    fgets(cmd_buf, sizeof(cmd_buf), fp);
    cmdstring += cmd_buf;

    if (cmdstring.empty()) {
        PRINT_ERROR_LOG("コマンドラインから出力を得られませんでした");
        return "";
    }
    (void)pclose(fp);
    // 改行文字を処理
    if (cmdstring.find("\n", 1) != string::npos) {
        cmdstring.erase(cmdstring.find("\n", 1), 1);
    }
    return cmdstring;
}