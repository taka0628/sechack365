#ifndef ___FILE_ENC_HPP
#define ___FILE_ENC_HPP


#include "string"
#include "fstream"
#include "iostream"

#define FILE_PATH_SIZE_LIM 500
#define ERROR(comment) \
    printf("[ERROR]\n\t%s: %d\n\t%s\n", __func__, __LINE__, comment);

class file_enc_c
{
private:
    std::string file_path_;
    std::string file_buff_;
    bool isExit_;
    bool isFile_;
    bool isDir_;
    bool isEncrypt_;
    bool isNoEncrypt_;

public:
    file_enc_c() {}
    ~file_enc_c() {}

    bool set_file_path(std::string filepath);
    bool file_enc();
    bool file_dec();

    bool is_file_exit() const;
    bool is_file() const;
    bool is_dir() const;
    bool is_enc() const;
    bool is_no_enc() const;
};

#endif