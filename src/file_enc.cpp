#include "file_enc.hpp"

using namespace std;

file_enc_c::file_enc_c()
{
    this->file_buff_ = nullptr;
    this->file_path_ = nullptr;
    this->isDir_ = false;
    this->isFile_ = false;
    this->isEncrypt_ = false;
    this->isNoEncrypt_ = false;
    this->isExit_ = false;
}

file_enc_c::~file_enc_c() {
    this->isDir_ = this->isEncrypt_ = this->isFile_ = this->isNoEncrypt_ = false;
}

bool file_enc_c::set_file_path(string filepath){
    if(filepath.size() > FILE_PATH_SIZE_LIM){
        ERROR("ファイルパスが長すぎます");
        return false;
    }
    this->file_path_ = filepath;

    fstream fs(this->file_path_);
    if(!fs){
        ERROR("ファイルオープンに失敗");
        cerr << "filepath: " << this->file_path_ << endl;
        return false;
    }

    string buf;
    getline(fs, buf);
    if(!fs){
        ERROR("読み取りに失敗");
        cerr << "filepath: " << this->file_path_ << endl;
        return false;
    }

    this->isFile_ = true;
    this->isExit_ = true;

    return true;
}

bool file_enc_c::is_file_exit() const{
    if(this->isFile_ && this->isExit_){
        return true;
    }
    return false;
}