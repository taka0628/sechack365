#ifndef ___FILE_PTR_C
#define ___FILE_PTR_C

#include "stdio.h"
#include "string"
#include "iostream"

#define ERROR(comment)\
     printf("[ERROR]\n\t%s: %d\n\t%s\n", __func__, __LINE__, comment)

class file_ptr_c
{
private:
    file_ptr_c(const file_ptr_c &);

public:
    file_ptr_c(const std::string filepath, const std::string option);
    file_ptr_c();
    ~file_ptr_c();
    void open(const std::string filepath, const std::string option);
    void reopen(const std::string filepath, const std::string option);
    FILE *fp_;
};

#endif