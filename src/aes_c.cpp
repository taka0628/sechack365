#include "../include/aes_c.hpp"

using namespace std;

aes_c::aes_c(/* args */)
{
}

aes_c::~aes_c()
{
}

void aes_c::set_iv(std::string hex)
{
	char buf[2] = {0};
	char *bin = (char *)calloc(sizeof(char), hex.size());
	int binsize = hex.size();
	printf("binsize: %d\n", binsize);

	this->remove_iv();
	char *pch;
	for (size_t i = 0; i < hex.size(); i += 2)
	{
		buf[0] = hex[i];
		buf[1] = hex[i + 1];
		pch = buf;
		bin[i / 2] = (char)strtoul(pch, NULL, 16);
		this->iv.push_back(bin[i / 2]);
	}
	free(bin);
	bin = nullptr;
}

bool aes_c::set_iv_key(const dynamic_mem_c &iv, const dynamic_mem_c &key)
{
	if (iv.is_empty() || key.is_empty())
	{
		ERROR("");
		return false;
	}
	if (iv.get_size() != key.get_size())
	{
		ERROR("");
		return false;
	}

	for (auto i = 0; i < iv.get_size(); i++)
	{
		this->iv.push_back(iv.mem[i]);
		this->key.push_back(key.mem[i]);
	}
	return true;
}

std::string aes_c::get_iv() const
{
	string iv;
	stringstream ss;
	char tch[10];
	for (const auto &i : this->iv)
	{
		sprintf(tch, "%02x", (int)i);
		ss << tch;
	}
	iv = ss.str();
	return iv;
}

void aes_c::set_key(string hex)
{
	// string buf(2, 0);
	char buf[2] = {0};
	char *bin = (char *)calloc(sizeof(char), hex.size());
	int binsize = hex.size();
	printf("binsize: %d\n", binsize);

	this->remove_key();
	char *pch;
	for (size_t i = 0; i < hex.size(); i += 2)
	{
		buf[0] = hex[i];
		buf[1] = hex[i + 1];
		pch = buf;
		bin[i / 2] = (char)strtoul(pch, NULL, 16);
		this->key.push_back(bin[i / 2]);
	}
	free(bin);
	bin = nullptr;
}

void aes_c::remove_key()
{
	this->key.erase(this->key.begin(), this->key.end());
}

void aes_c::remove_iv()
{
	this->iv.erase(this->iv.begin(), this->iv.end());
}

std::string aes_c::get_key() const
{
	string key;
	stringstream ss;
	char tch[10];
	for (const auto &i : this->key)
	{
		sprintf(tch, "%02x", (int)i);
		ss << tch;
	}
	key = ss.str();
	return key;
}

void aes_c::create_key(int bit)
{
	this->key.erase(this->key.begin(), this->key.end());
	unsigned char buf[bit / 8];
	memset(buf, 0, sizeof(buf));
	RAND_bytes(buf, bit / 8);
	for (int i = 0; i < bit / 8; i++)
	{
		this->key.push_back(buf[i]);
	}
}

void aes_c::create_iv(int bit)
{
	this->iv.erase(this->iv.begin(), this->iv.end());
	unsigned char buf[bit / 8];
	memset(buf, 0, sizeof(buf));
	RAND_bytes(buf, bit / 8);
	for (int i = 0; i < bit / 8; i++)
	{
		this->iv.push_back(buf[i]);
	}
}

void aes_c::print_0x(const string header, const string &buf) const
{
	cout << header;
	for (size_t i = 0; i < buf.size(); i++)
	{
		printf("%02x", (unsigned char)buf[i]);
	}
	puts("");
}

string aes_c::ui2hex(const vector<uint8_t> src) const
{
	stringstream buf;
	for (size_t i = 0; i < src.size(); i++)
	{
		buf << hex << int(src[i]);
	}
	return buf.str();
}

string aes_c::str2hex(const string src) const
{
	stringstream buf;
	char p[10];
	for (size_t i = 0; i < src.size(); i++)
	{
		sprintf(p, "%02x", (unsigned char)src[i]);
		buf << p;
	}
	return buf.str();
}

string aes_c::hex2str(const string hex) const
{
	char buf[3] = {0};
	unsigned char *bin = (unsigned char *)calloc(sizeof(char), hex.size());

	string result;
	result.erase(result.begin(), result.end());
	char *pch;
	memset((void *)bin, 0, hex.size());
	for (size_t i = 0; i < hex.size(); i += 2)
	{
		buf[0] = hex[i];
		buf[1] = hex[i + 1];
		pch = buf;
#if 1
		bin[i / 2] = (unsigned char)strtoul(pch, NULL, 16);
		cout << "strtoil: " << strtoul(pch, NULL, 16) << endl;
		// result[i / 2] = char_out;
		// result[i / 2 + 1] = NULL;
		// result.push_back(char_out);
		result.push_back(bin[i / 2]);
#else
		bin[i / 2] = (char)strtoul(pch, NULL, 16);
		//        result.push_back(bin[i / 2]);
		result = result + bin[i / 2];
		this->print_0x("0x: ", result);
#endif
	}
	free(bin);
	bin = nullptr;
	return result;
}

// std::vector<uint8_t> aes_c::hex2ui8(const string src) const
// {
//     stringstream buf;
//     for (int i = 0; i < src.size(); i++)
//     {
//         buf << (char)src[i];
//     }
//     return buf.str();
// }

void aes_c::encrypt(string &out, const string in, const AES_bit_e bit)
{

	int out_len, in_len = in.size();
	EVP_CIPHER_CTX *ctx;

	unsigned char *in2aes = (unsigned char *)in.data();
	unsigned char *outFromAes = (unsigned char *)calloc(sizeof(unsigned char), in.size());

	if (key.empty())
	{
		ERROR("key empty");
		return;
	}
	if (this->iv.empty())
	{
		ERROR("iv empty");
		return;
	}
	u_int8_t *key2aes = (u_int8_t *)this->key.data();
	u_int8_t *iv2aes = (u_int8_t *)this->iv.data();

	if (!(ctx = EVP_CIPHER_CTX_new()))
	{
		printf("error EVP_CIPHER_CTX_new\n");
		return;
	}

	switch (bit)
	{
	case AES_bit_e::aes_128:
		if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ctr(), NULL, key2aes, iv2aes))
		{
			printf("error EVP_EncryptInit_ex\n");
			return;
		}
		break;
	case AES_bit_e::aes_256:
		if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, key2aes, iv2aes))
		{
			printf("error EVP_EncryptInit_ex\n");
			return;
		}
		break;

	default:
		break;
	}

	if (1 != EVP_EncryptUpdate(ctx, outFromAes, &out_len, in2aes, in_len))
	{
		printf("error EVP_EncryptUpdate\n");
		return;
	}
	if (out_len != in_len)
	{
		printf("error encrypt out_len(%d) != in_len(%d)\n", out_len, in_len);
	}

	EVP_CIPHER_CTX_free(ctx);

	for (size_t i = 0; i < in.size(); i++)
	{
		out.push_back(outFromAes[i]);
	}

	free(outFromAes);
	outFromAes = nullptr;
}

void aes_c::encrypt(dynamic_mem_c &out, const dynamic_mem_c &in, const AES_bit_e bit)
{

	// int out_len, in_len = in.size();
	EVP_CIPHER_CTX *ctx;

	if (key.empty())
	{
		ERROR("key empty");
		return;
	}
	if (this->iv.empty())
	{
		ERROR("iv empty");
		return;
	}
	u_int8_t *key2aes = (u_int8_t *)this->key.data();
	u_int8_t *iv2aes = (u_int8_t *)this->iv.data();

	if (!(ctx = EVP_CIPHER_CTX_new()))
	{
		printf("error EVP_CIPHER_CTX_new\n");
		return;
	}

	switch (bit)
	{
	case AES_bit_e::aes_128:
		if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ctr(), NULL, key2aes, iv2aes))
		{
			printf("error EVP_EncryptInit_ex\n");
			return;
		}
		break;
	case AES_bit_e::aes_256:
		if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, key2aes, iv2aes))
		{
			printf("error EVP_EncryptInit_ex\n");
			return;
		}
		break;

	default:
		break;
	}

	int size2aes = (int)in.get_size();
	unsigned char *in2aes = (unsigned char *)in.mem;
	unsigned char *outFromAes = (unsigned char *)calloc(sizeof(unsigned char), out.get_size());

	if (1 != EVP_EncryptUpdate(ctx, outFromAes, &size2aes, in2aes, in.get_size()))
	{
		printf("error EVP_EncryptUpdate\n");
		return;
	}
	if (size2aes != in.get_size())
	{
		printf("error encrypt out_len(%d) != in_len(%d)\n", size2aes, in.get_size());
	}

	EVP_CIPHER_CTX_free(ctx);

	memcpy(out.mem, outFromAes, out.get_size());

	free(outFromAes);
	outFromAes = nullptr;
}

void aes_c::decrypt(string &out, const string in, const AES_bit_e bit)
{
	int out_len, in_len = in.size();
	EVP_CIPHER_CTX *ctx;

	if (key.empty())
	{
		ERROR("key empty");
		return;
	}
	if (this->iv.empty())
	{
		ERROR("iv empty");
		return;
	}

	unsigned char *in2aes = (unsigned char *)in.data();
	u_int8_t *key2aes = (u_int8_t *)this->key.data();
	u_int8_t *iv2aes = (u_int8_t *)this->iv.data();
	unsigned char *outFromAes = (unsigned char *)calloc(sizeof(unsigned char), in.size());

	if (!(ctx = EVP_CIPHER_CTX_new()))
	{
		printf("error EVP_CIPHER_CTX_new\n");
		return;
	}

	switch (bit)
	{
	case AES_bit_e::aes_128:
		if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ctr(), NULL, key2aes, iv2aes))
		{
			printf("error EVP_DecryptInit_ex\n");
			return;
		}
		break;

	case AES_bit_e::aes_256:
		if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, key2aes, iv2aes))
		{
			printf("error EVP_DecryptInit_ex\n");
			return;
		}
		break;

	default:
		break;
	}

	if (1 != EVP_DecryptUpdate(ctx, outFromAes, &out_len, in2aes, in_len))
	{
		printf("error EVP_DecryptUpdate\n");
		return;
	}
	if (out_len != in_len)
	{
		printf("error decrypt out_len(%d) != in_len(%d)\n", out_len, in_len);
	}

	EVP_CIPHER_CTX_free(ctx);
	for (size_t i = 0; i < in.size(); i++)
	{
		out.push_back(outFromAes[i]);
	}

	free(outFromAes);
	outFromAes = nullptr;
}

void aes_c::decrypt(dynamic_mem_c &out, const dynamic_mem_c &in, const AES_bit_e bit)
{
	int out_len, in_len = in.get_size();
	EVP_CIPHER_CTX *ctx;

	if (key.empty())
	{
		ERROR("key empty");
		return;
	}
	if (this->iv.empty())
	{
		ERROR("iv empty");
		return;
	}

	u_int8_t *key2aes = (u_int8_t *)this->key.data();
	u_int8_t *iv2aes = (u_int8_t *)this->iv.data();

	if (!(ctx = EVP_CIPHER_CTX_new()))
	{
		printf("error EVP_CIPHER_CTX_new\n");
		return;
	}

	switch (bit)
	{
	case AES_bit_e::aes_128:
		if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ctr(), NULL, key2aes, iv2aes))
		{
			printf("error EVP_DecryptInit_ex\n");
			return;
		}
		break;

	case AES_bit_e::aes_256:
		if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, key2aes, iv2aes))
		{
			printf("error EVP_DecryptInit_ex\n");
			return;
		}
		break;

	default:
		break;
	}

	unsigned char *outFromAes = (unsigned char *)calloc(sizeof(unsigned char), in.get_size());
	unsigned char *in2aes = (unsigned char *)in.mem;
	if (1 != EVP_DecryptUpdate(ctx, outFromAes, &out_len, in2aes, in_len))
	{
		printf("error EVP_DecryptUpdate\n");
		return;
	}
	if (out_len != in_len)
	{
		printf("error decrypt out_len(%d) != in_len(%d)\n", out_len, in_len);
	}

	EVP_CIPHER_CTX_free(ctx);
	memcpy(out.mem, outFromAes, out.get_size());

	free(outFromAes);
	outFromAes = nullptr;
}

void aes_c::reset()
{
	this->key.erase(this->key.begin(), this->key.end());
	this->iv.erase(this->iv.begin(), this->iv.end());
}
