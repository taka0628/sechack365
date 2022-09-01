#ifndef ___ERROR_HPP
#define ___ERROR_HPP

#include <stdio.h>
#include <time.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// #include "macro.hpp"

namespace ErrorMsg {
void push_log(const char* comment, const char* file, const char* func,
    const int line);
void push_value(std::string name, const std::string value);
void push_value(std::string name, const size_t value);

} // namespace ErrorMsg

#endif
