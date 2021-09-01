#ifndef ___RSA_HPP
#define ___RSA_HPP

#include "openssl/evp.h"
#include <openssl/rand.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/bio.h>

#include <memory.h>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>

class RSA_c
{
private:
    RSA_c(const RSA_c &);

    RSA *pub_key;
    RSA *priv_key;
    RSA *key_pair;
    uint key_size;
    std::string PRIV_FILE_NAME;
    std::string PUB_FILE_NAME;

public:
    RSA_c();
    ~RSA_c();

    enum class KEY_STATUS
    {
        PUB_KEY,
        PRIV_KEY,
    };

    std::string encrypt(const std::string &in) const;
    std::string decrypt(const std::string &in) const;

    void create_key(const uint bit);
    void create_RSA_file(KEY_STATUS pem_type, std::string file_name);
    std::string get_pub_key() const;
    std::string get_priv_key() const;

    std::string get_string_key(const KEY_STATUS &key) const;

    std::string str2hex(const std::string &str) const;
    std::string hex2bin(const std::string &hex) const;
    std::string decode_base64(std::string src) const;
    void set_key();
};

#endif
