#ifndef ___MASTER_KEY_HPP
#define ___MASTER_KEY_HPP

#include "aes_c.hpp"
#include "macro.hpp"
#include "openssl/rand.h"
#include "sha_c.hpp"

#include <cstdio>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

class master_key_c {
private:
    master_key_c(const master_key_c&);
public:
    master_key_c(/* args */);
    ~master_key_c();
};

master_key_c::master_key_c(/* args */)
{
}

master_key_c::~master_key_c()
{
}

#endif