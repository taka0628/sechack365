#ifndef ___FILE_ENC_HPP
#define ___FILE_ENC_HPP

#include "string"
#include "fstream"
#include "iostream"

#include "aes_c.hpp"
#include "sha_c.hpp"

#define FILE_PATH_SIZE_LIM 500
#define ERROR(comment) \
    printf("[ERROR]\n\t%s: %d\n\t%s\n", __func__, __LINE__, comment)

class file_enc_c
{
private:
    std::string file_path_;
    std::string file_buff_;
    std::string enc_buf_;
    std::string password_;
    std::string safe_pass_;
    bool isExit_;
    bool isFile_;
    bool isDir_;
    bool isEncrypt_;
    bool isNoEncrypt_;

public:
    file_enc_c();
    ~file_enc_c();

    bool set_file_path(std::string filepath);
    bool set_password(std::string pass);
    bool file_enc();
    bool file_dec();

    std::string get_file_pass() const;

    bool is_file_exit() const;
    bool is_file() const;
    bool is_dir() const;
    bool is_enc() const;
    bool is_no_enc() const;
};

#endif
