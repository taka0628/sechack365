#include "../include/error.hpp"
#include "../include/macro.hpp"

// using namespace std;

using namespace std;

void ErrorMsg::push_log(const char* comment, const char* file, const char* func, const int line)
{
    time_t timer;
    struct tm* date;

    std::string message;
    std::ofstream ofp(ERROR_LOG_FILE, std::ios_base::app);
    if (!ofp) {
        return;
    }

    /* 時間取得 */
    timer         = time(NULL);
    date          = localtime(&timer);
    char buf[512] = { "0" };
    strftime(buf, sizeof(buf), "[%x %H:%M:%S] ", date);

    // ファイル出力
    ofp << buf << "\n\t";
    ofp << "[" << file << ", " << func << ", " << line << "]"
        << "\n\t\t";
    ofp << comment << "\n"
        << endl;
}
void ErrorMsg::push_value(std::string name, const string value)
{
    ofstream ofp(ERROR_LOG_FILE, ios_base::app);
    if (!ofp) {
        ERROR_NO_COMMENT;
        return;
    }

    // ファイル出力
    ofp << "\t" << name << ": " << value << endl;
}
void ErrorMsg::push_value(std::string name, const size_t value)
{
    ofstream ofp(ERROR_LOG_FILE, ios_base::app);
    if (!ofp) {
        ERROR_NO_COMMENT;
        return;
    }

    // ファイル出力
    ofp << "\t" << name << ": " << value << endl;
}
// } // namespace error
