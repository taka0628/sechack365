#ifndef ___FILE_ENC_HPP
#define ___FILE_ENC_HPP

#include "string"
#include "fstream"
#include "iostream"
#include "cstdio"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "openssl/rand.h"

#include "aes_c.hpp"
#include "sha_c.hpp"
#include "key_list_c.hpp"
#include "file_ptr_c.hpp"


#define FILE_PATH_SIZE_LIM 500
#define ERROR(comment) \
    printf("[ERROR]\n\t%s: %d\n\t%s\n", __func__, __LINE__, comment)

class file_enc_c
{
private:
    enum class CRYPT_MODE
    {
        DECRYPT,
        ENCRYPT
    };
    file_enc_c(const file_enc_c &);

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

    size_t getFileSize(FILE *fp) const;
    void file_delete(std::string const file_path) const;
    bool crypt_process(aes_c &aes , file_enc_c::CRYPT_MODE const mode) const;

public:
    file_enc_c();
    ~file_enc_c();

    bool set_file_path(std::string filepath);
    bool set_password(std::string pass);
    bool file_enc();
    bool file_dec();
    bool calc_file_hash(const std::string file_name, dynamic_mem_c &out) const;
    void extemsion_set(const file_enc_c::CRYPT_MODE mode);
    std::string get_file_pass() const;

    bool is_file_exit() const;
    bool is_file() const;
    bool is_dir() const;
    bool is_enc() const;
    bool is_no_enc() const;
};

#endif
