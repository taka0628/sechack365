#include "../include/device_c.hpp"

device_c::device_c()
{
}

device_c::~device_c()
{
}

using namespace std;

vector<string> device_c::get_usbList() const
{
	string cmdline = "lsusb | cut -d ' ' -f 5- ";
	FILE *fp;
	std::vector<std::string> usb_list;

	if ((fp = popen(cmdline.c_str(), "r")) == NULL)
	{
		PRINT_ERROR_LOG("can not exec commad");
		usb_list.clear();
		return usb_list;
	}
	char cmd_buf[256];
	while (!feof(fp))
	{
		fgets(cmd_buf, sizeof(cmd_buf), fp);
		usb_list.push_back(cmd_buf);
	}

	if (usb_list.empty())
	{
		PRINT_ERROR_LOG("コマンドラインから出力を得られませんでした");
		usb_list.clear();
		return usb_list;
	}
	(void)pclose(fp);

	// 改行文字を処理
	for (string &in : usb_list)
	{
		in.erase(in.find("\n", 1));
	}
	return usb_list;
}