#include "file_enc.hpp"

using namespace std;

file_enc_c::file_enc_c()
{
    this->isDir_ = false;
    this->isFile_ = false;
    this->isEncrypt_ = false;
    this->isNoEncrypt_ = false;
    this->isExit_ = false;
}

file_enc_c::~file_enc_c()
{
    this->isDir_ = this->isEncrypt_ = this->isFile_ = this->isNoEncrypt_ = false;
}

bool file_enc_c::set_file_path(string filepath)
{
    if (filepath.size() > FILE_PATH_SIZE_LIM)
    {
        ERROR("ファイルパスが長すぎます");
        return false;
    }
    this->file_path_ = filepath;

    this->file_path_.erase(this->file_path_.find("\n"), 1);
    this->file_path_.erase(this->file_path_.find("\r"), 1);

    fstream input_fs(this->file_path_);
    if (!input_fs)
    {
        ERROR("ファイルオープンに失敗");
        cerr << "filepath: " << this->file_path_ << endl;
        return false;
    }

    string buf;
    getline(input_fs, buf);
    if (!input_fs)
    {
        ERROR("読み取りに失敗");
        cerr << "filepath: " << this->file_path_ << endl;
        return false;
    }

    this->isFile_ = true;
    this->isExit_ = true;

    return true;
}

bool file_enc_c::is_file_exit() const
{
    if (this->isFile_ && this->isExit_)
    {
        return true;
    }
    return false;
}

bool file_enc_c::set_password(string pass)
{
    if (pass.size() == 0)
    {
        ERROR("パスワードが入力されていません");
        return false;
    }
    if (pass.find("\n") != string::npos)
    {
        pass.erase(pass.find("\n"), 1);
    }
    if (pass.find("\r") != string::npos)
    {
        pass.erase(pass.find("\r"), 1);
    }
    if (pass.size() == 0)
    {
        ERROR("パスワード入力が不正です");
        return false;
    }
    this->password_ = pass;
    return true;
}

bool file_enc_c::file_enc()
{
    if (this->file_path_.size() == 0 ||
        this->is_file_exit() == false ||
        this->password_.size() == 0)
    {
        return false;
    }

    fstream fs(this->file_path_);
    if (!fs)
    {
        ERROR("ファイルオープンに失敗");
        cerr << "filepath: " << this->file_path_ << endl;
        return false;
    }

    SHA_c sha;
    this->safe_pass_ = sha.sha2_cal(this->file_path_, SHA_c::SHA2_bit::SHA_256);
    aes_c aes;
    aes.set_iv(sha.str2hex(this->safe_pass_));
    aes.set_key(sha.str2hex(this->safe_pass_));

    string buf, out_buf;
    while (getline(fs, buf))
    {
        aes.encrypt(out_buf, buf, aes_c::AES_bit_e::aes_256);
        this->enc_buf_ += out_buf;
    }

    fs.close();

    ofstream out_fs;
    out_fs.open(this->get_file_pass(), ios::trunc);
    out_fs << this->enc_buf_;

    cout << "暗号化に成功" << endl;
    return true;
}

string file_enc_c::get_file_pass() const
{
    return this->file_path_;
}
