#ifndef ___SHA1_HPP
#define ___SHA1_HPP

#include "openssl/aes.h"
#include "openssl/evp.h"
#include "openssl/sha.h"
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

class SHA_c
{
private:
    SHA_c(const SHA_c &);

public:
    SHA_c();
    ~SHA_c();
    enum class SHA2_bit
    {
        SHA_224,
        SHA_256,
        SHA_384,
        SHA_512,
    };

    std::string sha1_cal(const std::string &src) const;
    std::string sha2_cal(const std::string &src, const SHA2_bit bit) const;

    std::string str2hex(const std::string &src) const;
};

#endif