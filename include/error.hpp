#ifndef ___ERROR_HPP
#define ___ERROR_HPP

#include "macro.hpp"

#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

void push_error_log(const char *comment, const char *file, const char *func, const int line);

#endif
