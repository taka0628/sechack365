#ifndef ___AES_HPP
#define ___AES_HPP

#include "openssl/aes.h"
#include "openssl/evp.h"
#include <openssl/rand.h>
#include <memory.h>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>


class aes_c
{
private:
    std::vector<u_int8_t> key;
    std::vector<u_int8_t> iv;
    aes_c(const aes_c &);

public:
    aes_c();
    ~aes_c();

    enum class AES_bit_e
    {
        aes_128,
        aes_256,
    };

    void set_key(const std::string hex);
    std::string get_key() const;
    void create_key(int bit);
    void remove_key();

    void set_iv(const std::string hex);
    std::string get_iv() const;
    void create_iv(const int bit);
    void remove_iv();

    void reset();

    void encrypt(std::string &out, const std::string in, const AES_bit_e bit);
    void decrypt(std::string &out, const std::string in, const AES_bit_e bit);

    void print_0x(const std::string header, const std::string &buf) const;
    std::string ui2hex(const std::vector<uint8_t> src) const;
    std::string str2hex(const std::string src) const;
    std::string hex2str(const std::string src) const;
};

#endif
