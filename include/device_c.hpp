#ifndef ___DEVICE_HPP
#define ___DEVICE_HPP

#include "error.hpp"
#include "macro.hpp"

#include "string"
#include "fstream"
#include "iostream"
#include "sstream"
#include "vector"
#include "cstdio"
#include "algorithm"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

class device_c
{
private:
	/* data */
public:
	device_c();
	~device_c();

	std::vector<std::string> get_usbList() const;
};

#endif