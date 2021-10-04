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

bool device_c::set_usbID(const string usbID)
{
	if (usbID.empty() || usbID.size() != 9)
	{
		PRINT_ERROR_LOG("usbIDが不正");
		return false;
	}
	// sudo lsusb -d 1d6b:0002 -v | grep iSerial | awk '{print $3}'
	string cmdline = "sudo lsusb -d ";
	cmdline += usbID;
	cmdline += " -v | grep iSerial | awk '{print $3}' | tail -n -1";

	FILE *fp;
	if ((fp = popen(cmdline.c_str(), "r")) == NULL)
	{
		PRINT_ERROR_LOG("can not exec commad");
		return false;
	}
	char cmd_buf[256];
	string temp;

	fgets(cmd_buf, sizeof(cmd_buf), fp);
	temp = cmd_buf;

	(void)pclose(fp);

	// 4文字未満のシリアル番号はエラーとみなす
	if (temp.empty() || temp.size() < 4)
	{
		PRINT_ERROR_LOG("コマンドラインから出力を得られませんでした");
		return false;
	}
	else
	{
		temp.erase(temp.find("\n", 1), 1);
		this->usb_serial_ = temp;
		this->usb_id_ = usbID;
	}

	return true;
}

string device_c::get_usbID() const
{
	if (this->usb_id_.empty())
	{
		return "";
	}
	return this->usb_id_;
}

string device_c::get_usbSerial() const
{
	if (this->usb_serial_.empty())
	{
		return "";
	}
	return this->usb_serial_;
}