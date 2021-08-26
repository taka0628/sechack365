#include "file_enc.hpp"

using namespace std;

key_list_c::key_list_c()
{
	file_ptr_c fp(KEY_FILE_NAME, "a");
}

key_list_c::~key_list_c()
{
}

string key_list_c::get_file_name() const
{
	if (this->key_file_name_.empty())
	{
		ERROR("ファイル名が指定されていません");
		return nullptr;
	}
	return this->key_file_name_;
}

bool key_list_c::pop_file(dynamic_mem_c const &hash, dynamic_mem_c &iv, dynamic_mem_c &key)
{
	if (hash.is_empty())
	{
		return false;
	}

	file_ptr_c fp(this->get_file_name().c_str(), "rb");
	fseek(fp.fp_, 0, SEEK_SET);

	bool isFindHash = false;
	const uint line_size = HASH_SIZE + AES_SIZE * 2;
	dynamic_mem_c buffer(line_size);
	u_char temp[HASH_SIZE];
	size_t read_size = 0;

	// ハッシュ値を検索
	while ((read_size = fread(buffer.mem, 1, line_size, fp.fp_)) > 0)
	{
		if (read_size != line_size)
		{
			break;
		}
		memcpy(temp, buffer.mem, HASH_SIZE);
		if (memcmp(temp, hash.mem, HASH_SIZE) == 0)
		{
			isFindHash = true;
			break;
		}
	}
	fp.close();

	if (isFindHash == false)
	{
		return false;
	}

	// iv, keyをコピー
	for (size_t i = 0; i < HASH_SIZE; i++)
	{
		iv.mem[i] = buffer.mem[i + HASH_SIZE];
		key.mem[i] = buffer.mem[i + HASH_SIZE + AES_SIZE];
	}

	this->plug(hash);

	return true;
}

bool key_list_c::plug(const dynamic_mem_c &hash)
{
	// 読み取りファイル
	file_ptr_c fp(this->get_file_name().c_str(), "rb");

	// バッファ用ファイル
	const string buffer_file_name = "buffer_file_key_list";
	file_ptr_c buffer_fp(buffer_file_name.c_str(), "wb");

	const uint line_size = HASH_SIZE + AES_SIZE * 2;
	dynamic_mem_c buffer(line_size), temp(HASH_SIZE);

	// バッファへ該当ハッシュ値のファイルの除いて書き出し
	size_t read_size = 0;
	while ((read_size = fread(buffer.mem, 1, line_size, fp.fp_)) > 0)
	{
		if (read_size != line_size)
		{
			break;
		}
		if (memcmp(buffer.mem, hash.mem, HASH_SIZE) == 0)
		{
			continue;
		}
		fwrite(buffer.mem, 1, line_size, buffer_fp.fp_);
	}

	// バッファを読み取り元ファイルへ書き出し
	buffer_fp.reopen(buffer_file_name.c_str(), "rb");
	fp.reopen(this->get_file_name().c_str(), "wb");
	while ((read_size = fread(buffer.mem, 1, line_size, buffer_fp.fp_)))
	{
		fwrite(buffer.mem, 1, read_size, fp.fp_);
	}
	// バッファ用ファイルを初期化
	buffer_fp.reopen(buffer_file_name.c_str(), "wb");
	return true;
}

bool key_list_c::add_file(dynamic_mem_c const &hash, dynamic_mem_c const &iv, dynamic_mem_c const &key) const
{
	// hashに値は入っているか？
	if (hash.is_empty() == true || iv.is_empty() == true || key.is_empty() == true)
	{
		return false;
	}

	file_ptr_c fp;
	fp.open(this->get_file_name().c_str(), "ab");

	fwrite(hash.mem, 1, hash.get_size(), fp.fp_);
	fwrite(iv.mem, 1, iv.get_size(), fp.fp_);
	fwrite(key.mem, 1, key.get_size(), fp.fp_);

	return true;
}