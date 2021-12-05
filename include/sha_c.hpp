#ifndef ___SHA1_HPP
#define ___SHA1_HPP

#include <memory.h>
#include <openssl/rand.h>
#include <stdio.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "dynamic_mem_c.hpp"
#include "macro.hpp"
#include "openssl/aes.h"
#include "openssl/evp.h"
#include "openssl/sha.h"

class SHA_c {
   private:
    SHA_c(const SHA_c &);

   public:
    SHA_c();
    ~SHA_c();
    enum class SHA2_bit {
        SHA_224,
        SHA_256,
        SHA_384,
        SHA_512,
    };

    std::string sha1_cal(const std::string &src) const;
    std::string sha2_cal(const std::string &src, const SHA2_bit bit) const;
    bool sha2_cal(const dynamic_mem_c &in, dynamic_mem_c &out,
                  const SHA2_bit bit) const;

    std::string str2hex(const std::string &src) const;
    std::string str2hex(const dynamic_mem_c &src) const;
};

#endif