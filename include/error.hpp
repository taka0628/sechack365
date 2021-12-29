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

#include "macro.hpp"

namespace log {
void push_log(const char* comment, const char* file, const char* func,
    const int line);
template <typename T>
void push_value(std::string name, T value);
} // namespace log

#endif
