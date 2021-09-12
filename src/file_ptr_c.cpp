#include "../include/file_enc.hpp"

using namespace std;

file_ptr_c::file_ptr_c(const string filename, const string option)
{
	this->fp_ = fopen(filename.c_str(), option.c_str());
}

file_ptr_c::file_ptr_c()
{
	this->fp_ = NULL;
}

file_ptr_c::~file_ptr_c()
{
	if (this->fp_ == NULL)
	{
		return;
	}
	fclose(this->fp_);
	this->fp_ = NULL;
}

void file_ptr_c::open(const string filepath, const string option)
{
	if (this->fp_ != NULL)
	{
		fclose(this->fp_);
		this->fp_ = NULL;
	}
	this->fp_ = fopen(filepath.c_str(), option.c_str());
	if (this->fp_ == NULL)
	{
		ERROR_NO_COMMENT;
	}
}

void file_ptr_c::reopen(const string filepath, const string option)
{
	if (this->fp_ != NULL)
	{
		fclose(this->fp_);
		this->fp_ = NULL;
	}
	this->fp_ = fopen(filepath.c_str(), option.c_str());
}

void file_ptr_c::close()
{
	if (this->fp_ == NULL || this->fp_ == nullptr)
	{
		return;
	}
	fclose(this->fp_);
	this->fp_ = NULL;
}