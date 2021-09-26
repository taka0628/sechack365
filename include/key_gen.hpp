#ifndef ___KEY_GEN_HPP
#define ___KEY_GEN_HPP

#include "dynamic_mem_c.hpp"
#include "sha_c.hpp"
#include "macro.hpp"
#include "file_enc.hpp"
#include "error.hpp"

#include "string"
#include "fstream"
#include "iostream"
#include "cstdio"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "openssl/rand.h"

class key_gen_c
{
private:
	key_gen_c(const key_gen_c &);

	dynamic_mem_c key_;
	std::string pass_;
	std::string usbID_;
	std::string usbSerial_;

	std::string get_pass() const;
	std::string get_usbSerial() const;

protected:
public:
	key_gen_c();
	~key_gen_c();

	bool new_key_gen();
	bool key_gen();

	bool set_pass(std::string const pass);

	bool set_usbID(std::string const id);
	std::string get_usbID() const;
	bool set_UsbSerial();

	bool get_nonce(dynamic_mem_c &to) const;
	bool set_nonce() const;

	dynamic_mem_c get_key() const;
	bool canKeyGen() const;
};

#endif