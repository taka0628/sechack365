#include "../include/key_gen.hpp"

using namespace std;

key_gen_c::key_gen_c()
{
	this->pass.clear();
}

key_gen_c::~key_gen_c()
{
}

bool key_gen_c::set_pass(std::string const pass)
{
	if (pass.empty())
	{
		ERROR_NO_COMMENT;
		return false;
	}
	this->pass = pass;
	return true;
}

string key_gen_c::get_pass() const
{
	if (this->pass.empty())
	{
		return "";
	}
	return this->pass;
}

bool key_gen_c::canKeyGen() const
{
	if (this->pass.empty())
	{
		return false;
	}
	return true;
}

bool key_gen_c::key_gen()
{
	if (this->canKeyGen() == false)
	{
		ERROR_NO_COMMENT;
		return false;
	}
	return true;
}

bool key_gen_c::getUsbSerial()
{
	FILE *fp;
	string id = "8564:1000";
	string cmdline = "sudo lsusb -d ";
	cmdline += id;
	cmdline += " -v | grep iSerial | awk '{print $3}' ";
	cout << "cmd: " << cmdline << endl;
	if ((fp = popen(cmdline.c_str(), "r")) == NULL)
	{
		ERROR("can not exec commad");
		return false;
	}
	char buf[256];

	while (!feof(fp))
	{
		fgets(buf, sizeof(buf), fp);
		printf("=> %s", buf);
	}

	(void)pclose(fp);
	return true;
}

bool key_gen_c::set_usbID(string const id)
{
	if (id.empty())
	{
		PRINT_ERROR_LOG("idが空");
		return false;
	}

	return true;
}
