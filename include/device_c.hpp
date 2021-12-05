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
#include "memory"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

class device_c
{
private:
	std::string usb_id_;
	std::string usb_serial_;

public:
	device_c();
	~device_c();

	std::vector<std::string> get_usbList() const;
	bool set_usbID(const std::string);
	std::string get_usbID() const;

	std::string get_usbSerial() const;
	uint32_t get_usb_cnt() const;
};

#endif