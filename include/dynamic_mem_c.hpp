#ifndef ___DYNAMIC_MEM_HPP
#define ___DYNAMIC_MEM_HPP

#include <memory.h>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

#include "macro.hpp"

class dynamic_mem_c
{
private:
    dynamic_mem_c(const dynamic_mem_c &);
    size_t size;
    int usage_;

public:
    dynamic_mem_c();
    dynamic_mem_c(const uint size);
    ~dynamic_mem_c();

    unsigned char *mem;

    void d_new(const uint size);
    void d_free();
    size_t get_size() const;
    void copy(std::string &dest, const uint size) const;
    void reset();
    bool is_empty() const;
};

#endif