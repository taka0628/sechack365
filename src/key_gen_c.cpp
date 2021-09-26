#include "../include/key_gen.hpp"

using namespace std;

key_gen_c::key_gen_c()
{
	this->pass_.clear();
	this->usbID_.clear();
	this->usbSerial_.clear();
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
	this->pass_ = pass;
	return true;
}

string key_gen_c::get_pass() const
{
	if (this->pass_.empty())
	{
		return "";
	}
	return this->pass_;
}

bool key_gen_c::canKeyGen() const
{
	if (this->pass_.empty() || this->get_usbSerial().empty())
	{
		return false;
	}
	return true;
}

string key_gen_c::get_usbSerial() const
{
	if (this->usbSerial_.empty())
	{
		PRINT_ERROR_LOG("USBのシリアル番号がセットされていません");
		return "";
	}
	return this->usbSerial_;
}

bool key_gen_c::new_key_gen()
{
	this->set_nonce();
	return this->key_gen();
}

bool key_gen_c::key_gen()
{
	if (this->canKeyGen() == false)
	{
		ERROR_NO_COMMENT;
		return false;
	}

	dynamic_mem_c nonce;
	nonce.d_new(NONCE_SIZE);
	this->get_nonce(nonce);

	string buf;
	buf = this->get_pass() + this->get_usbSerial();
	dynamic_mem_c key;
	key.d_new(NONCE_SIZE + buf.size());

	SHA_c sha;
	this->key_.d_new(SHA256_DIGEST_LENGTH);
	if (sha.sha2_cal(key, this->key_, SHA_c::SHA2_bit::SHA_256) == false)
	{
		PRINT_ERROR_LOG("鍵を取得できませんでした");
		this->key_.d_free();
		return false;
	}
	return true;
}

bool key_gen_c::get_nonce(dynamic_mem_c &to) const
{
	if (to.get_size() != NONCE_SIZE)
	{
		PRINT_ERROR_LOG("nonceを格納する大きさがありません");
		return false;
	}

	file_ptr_c fp;
	if (fp.open(NONCE_FILE, "rb") == false)
	{
		PRINT_ERROR_LOG("nonceファイルを読み取れません");
		return false;
	}
	if (fread(to.mem, 1, NONCE_SIZE, fp.fp_) != NONCE_SIZE)
	{
		PRINT_ERROR_LOG("nonceのサイズが違います");
		return false;
	}
	return true;
}

bool key_gen_c::set_nonce() const
{
	file_ptr_c fp;
	if (fp.open(NONCE_FILE, "wb") == false)
	{
		PRINT_ERROR_LOG("nonceファイルが開けません");
		return false;
	}
	dynamic_mem_c rand;
	rand.d_new(NONCE_SIZE);
	RAND_bytes(rand.mem, NONCE_SIZE);
	fwrite(rand.mem, 1, rand.get_size(), fp.fp_);
	return true;
}

bool key_gen_c::set_UsbSerial()
{
	if (this->usbID_.empty())
	{
		PRINT_ERROR_LOG("USBIDが指定されていません");
		return false;
	}

	FILE *fp;
	string id = this->get_usbID();

	string cmdline = "sudo lsusb -d ";
	cmdline += id;
	cmdline += " -v | grep iSerial | awk '{print $3}' ";
	cout << "cmd: " << cmdline << endl;
	if ((fp = popen(cmdline.c_str(), "r")) == NULL)
	{
		PRINT_ERROR_LOG("can not exec commad");
		return false;
	}
	char buf[256];

	while (!feof(fp))
	{
		fgets(buf, sizeof(buf), fp);
		printf("=> %s", buf);
	}

	(void)pclose(fp);
	this->usbSerial_ = buf;
	return true;
}

bool key_gen_c::set_usbID(string const id)
{
	if (id.empty())
	{
		PRINT_ERROR_LOG("idが空");
		return false;
	}
	if (id.find(":") == string::npos)
	{
		PRINT_ERROR_LOG("不正な引数");
		return false;
	}

	string cmdline;
	cmdline += "lsusb | grep ";
	cmdline += id;
	FILE *fp;
	if ((fp = popen(cmdline.c_str(), "r")) == NULL)
	{
		PRINT_ERROR_LOG("can not exec commad");
		return false;
	}

	char buf[256] = {"0"};
	string result;
	while (!feof(fp))
	{
		fgets(buf, sizeof(buf), fp);
		result += buf;
	}
	if (result.size() < 10)
	{
		PRINT_ERROR_LOG("USBが検出できません");
		return false;
	}

	this->usbID_ = id;

	return true;
}

string key_gen_c::get_usbID() const
{
	if (this->usbID_.empty())
	{
		return "";
	}
	return this->usbID_;
}

dynamic_mem_c key_gen_c::get_key() const
{
	if (this->key_.is_empty())
	{
		PRINT_ERROR_LOG("鍵がありません");
	}

	return this->key_;
}