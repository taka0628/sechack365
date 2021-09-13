#ifndef ___FILE_ENC_HPP
#define ___FILE_ENC_HPP

#include "string"
#include "fstream"
#include "iostream"
#include "cstdio"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "openssl/rand.h"

#include "aes_c.hpp"
#include "sha_c.hpp"
#include "macro.hpp"

class file_enc_c
{
private:
	file_enc_c(const file_enc_c &);

	std::string file_path_;
	std::string file_buff_;
	std::string enc_buf_;
	std::string password_;
	std::string safe_pass_;
	bool isExit_;
	bool isFile_;
	bool isDir_;
	bool isEncrypt_;
	bool isNoEncrypt_;

	size_t getFileSize(FILE *fp) const;
	void file_delete(std::string const file_path) const;

public:
	file_enc_c();
	~file_enc_c();

	enum class CRYPT_MODE
	{
		DECRYPT,
		ENCRYPT
	};

	bool set_file_path(std::string filepath);
	bool set_password(std::string pass);
	bool file_enc();
	bool file_dec();
	bool crypt_process(aes_c &aes, file_enc_c::CRYPT_MODE const mode) const;
	bool calc_file_hash(const std::string file_name, dynamic_mem_c &out) const;
	void extemsion_set(const file_enc_c::CRYPT_MODE mode);
	std::string get_file_pass() const;

	bool is_file_exit() const;
	bool is_file() const;
	bool is_dir() const;
	bool is_enc() const;
	bool is_no_enc() const;
};

class key_list_c
{
private:
	key_list_c(const key_list_c &);
	const std::string key_file_name_ = KEY_FILE_NAME;

	// 該当ハッシュ値のファイルをデータベースから削除し、以降のファイルを埋める
	// 重複は両方削除される
	bool plug(const dynamic_mem_c &hash);

public:
	key_list_c();
	~key_list_c();

	std::string get_file_name() const;

	// ハッシュ値でファイルを検索し、iv, keyを取得
	bool pop_file(dynamic_mem_c const &hash, dynamic_mem_c &iv, dynamic_mem_c &key);
	// データベースにファイルを登録
	bool add_file(dynamic_mem_c const &hash, dynamic_mem_c const &iv, dynamic_mem_c const &key) const;
	// 鍵ファイルを暗号化 AES-256bit
	bool encrypt(dynamic_mem_c const &key) const;
	// 鍵ファイルを復号 AES-256bit
	bool decrypt(dynamic_mem_c const &key) const;
	// 鍵リストの共通鍵が正しいか確認
	bool key_check(dynamic_mem_c const &key) const;
	// 鍵リストの共通鍵のハッシュ値をファイルに上書き
	bool key_list_pkey_update(dynamic_mem_c const &key) const;
};

class file_ptr_c
{
private:
	file_ptr_c(const file_ptr_c &);

public:
	file_ptr_c(const std::string filepath, const std::string option);
	file_ptr_c();
	~file_ptr_c();
	bool open(const std::string filepath, const std::string option);
	bool reopen(const std::string filepath, const std::string option);
	void close();
	FILE *fp_;
};

#endif
