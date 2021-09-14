#include "../include/error.hpp"

using namespace std;

void push_error_log(const char *comment, const char *file, const char *func, const int line)
{
	time_t timer;
	struct tm *date;

	string message;
	ofstream ofp(ERROR_LOG_FILE, ios_base::app);
	if (!ofp)
	{
		ERROR_NO_COMMENT;
		return;
	}

	/* 時間取得 */
	timer = time(NULL);
	date = localtime(&timer);
	char buf[512] = {"0"};
	strftime(buf, sizeof(buf), "[%Y/%x %H:%M:%S] ", date);

	// ファイル出力
	ofp << buf << "\n\t";
	ofp << "[" << file << "," << func << "," << line << "]"
		<< "\t";
	ofp << comment << endl;
}
