#ifndef ___KEY_GEN_HPP
#define ___KEY_GEN_HPP

#include "dynamic_mem_c.hpp"
#include "sha_c.hpp"
#include "macro.hpp"
#include "file_enc.hpp"

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

	dynamic_mem_c key;
	std::string pass;
	std::string usbID;

	std::string get_pass() const;

protected:
public:
	key_gen_c();
	~key_gen_c();

	bool key_gen();

	bool set_pass(std::string const pass);
	bool set_usbID(std::string const id);
	bool getUsbSerial();

	dynamic_mem_c get_key() const;
	bool canKeyGen() const;
};

#endif