#ifndef ___DYNAMIC_MEM_HPP
#define ___DYNAMIC_MEM_HPP

#include <memory.h>
#include <stdio.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "macro.hpp"

class dynamic_mem_c {
private:
    size_t size_;
    int usage_;
    std::string to_string_table(const u_int i) const;

public:
    dynamic_mem_c();
    dynamic_mem_c(const uint size);
    ~dynamic_mem_c();
    dynamic_mem_c(const dynamic_mem_c& from);
    dynamic_mem_c& operator=(const dynamic_mem_c& from);

    unsigned char* mem_;

    void d_new(const uint size);
    void d_free();
    size_t size() const;
    void copy(const dynamic_mem_c from, const uint size);
    void copy(const dynamic_mem_c from);
    void reset();
    bool empty() const;
    std::vector<u_char> to_vector() const;
    bool from_vector(const std::vector<u_char>& src);
    std::string to_string() const;
};

#endif