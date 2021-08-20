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
}

bool file_enc_c::set_file_path(string filepath)
{
    if (filepath.size() > FILE_PATH_SIZE_LIM)
    {
        ERROR("ファイルパスが長すぎます");
        return false;
    }
    this->file_path_ = filepath;

    if (this->file_path_.find("\n") != string::npos)
    {
        this->file_path_.erase(this->file_path_.find("\n"), 1);
    }
    if (this->file_path_.find("\r") != string::npos)
    {
        this->file_path_.erase(this->file_path_.find("\r"), 1);
    }

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
    this->safe_pass_ = sha.sha2_cal(this->password_, SHA_c::SHA2_bit::SHA_256);
    aes_c aes;
    aes.set_iv(sha.str2hex(this->safe_pass_));
    aes.set_key(sha.str2hex(this->safe_pass_));

    string out_buf, buffer;
    char buf[2048];
    memset(buf, 0, 2048);
    fs.seekg(0, ios_base::beg);

    FILE *fp = fopen(this->get_file_pass().c_str(), "rb");
    if (fp == NULL)
    {
        ERROR("ファイルが開けません");
        return false;
    }
#if 1
    const string buff_file_name("crypt_temp");
    FILE *fp_buffer = fopen(buff_file_name.c_str(), "wb");
    int buf_size = 0;

    // 暗号化
    while ((buf_size = fread(buf, 1, 1024, fp)) > 0)
    {
        aes.encrypt(out_buf, buf, aes_c::AES_bit_e::aes_256);
        fwrite(out_buf.c_str(), 1, buf_size, fp_buffer);
        buffer.clear();
        out_buf.clear();
        memset(buf, 0, 2048);
    }
    fclose(fp);
    fclose(fp_buffer);

    // ファイル出力
    fp = fopen(this->get_file_pass().c_str(), "wb");
    if ((fp_buffer = fopen(buff_file_name.c_str(), "rb")) == NULL)
    {
        ERROR("ファイルが開けません");
        return false;
    }
    while ((buf_size = fread(buf, 1, 1024, fp_buffer)) > 0)
    {
        fwrite(buf, 1, buf_size, fp);
    }
    fclose(fp);
    fclose(fp_buffer);
    this->file_delete(buff_file_name);

    // 拡張子変更
    string new_file_name = this->get_file_pass() + ".enc";
    if (rename(this->get_file_pass().c_str(), new_file_name.c_str()))
    {
        ERROR("ファイル名の変更に失敗");
        return false;
    }
#else
    const string buff_file_name("crypt_temp");
    FILE *fp_buffer = fopen(buff_file_name.c_str(), "wb");
    while (fread(buf, 1, 1024, fp) > 0)
    {
        fwrite(buf, 1, 1024, fp_buffer);
        memset(buf, 0, 1024);
    }
    fclose(fp);
    fclose(fp_buffer);

    // ファイル出力
    fp = fopen(this->get_file_pass().c_str(), "wb");
    if ((fp_buffer = fopen(buff_file_name.c_str(), "rb")) == NULL)
    {
        ERROR("ファイルが開けません");
        return false;
    }
    while (fread(buf, 1, 1024, fp_buffer))
    {
        fwrite(buf, 1, 1024, fp);
    }
    fclose(fp);
    fclose(fp_buffer);
    delete (buf);
    cout << "file_size: " << file_size << endl;

#endif
    cout << "暗号化に成功" << endl;
    return true;
}

bool file_enc_c::file_dec()
{
    // エラーチェック
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

    // パスワードのハッシュを鍵とivに使用
    SHA_c sha;
    this->safe_pass_ = sha.sha2_cal(this->password_, SHA_c::SHA2_bit::SHA_256);
    aes_c aes;
    aes.set_iv(sha.str2hex(this->safe_pass_));
    aes.set_key(sha.str2hex(this->safe_pass_));

    string out_buf, temp;
    out_buf.clear();
    fs.seekg(0, ios::basic_ios::beg);
    string buffer, buffer_sub;
    FILE *fp = fopen(this->get_file_pass().c_str(), "rb");
    if (fp == NULL)
    {
        ERROR("ファイルが開けません");
        return false;
    }
    char buf[2048];
    memset(buf, 0, 2048);
    const string buff_file_name("crypt_temp");

    FILE *fp_buffer = fopen(buff_file_name.c_str(), "wb");
    int buf_size = 0;
    while ((buf_size = fread(buf, 1, 1024, fp)) > 0)
    {
        aes.decrypt(out_buf, buf, aes_c::AES_bit_e::aes_256);
        fwrite(out_buf.c_str(), 1, buf_size, fp_buffer);
        buffer.clear();
        out_buf.clear();
        memset(buf, 0, 2048);
    }
    fclose(fp);
    fclose(fp_buffer);

    // ファイル出力
    fp = fopen(this->get_file_pass().c_str(), "wb");
    if ((fp_buffer = fopen(buff_file_name.c_str(), "rb")) == NULL)
    {
        ERROR("ファイルが開けません");
        return false;
    }
    while ((buf_size = fread(buf, 1, 1024, fp_buffer)) > 0)
    {
        fwrite(buf, 1, buf_size, fp);
    }
    fclose(fp);
    fclose(fp_buffer);
    this->file_delete(buff_file_name);

    // ファイル名変更
    string new_file_name = this->get_file_pass();
    // ファイル拡張子を更新
    if (new_file_name.find(".enc") != string::npos)
    {
        new_file_name.erase(new_file_name.find(".enc"), 4);
    }
    if (rename(this->get_file_pass().c_str(), new_file_name.c_str()))
    {
        ERROR("ファイル名の変更に失敗");
        return false;
    }

    cout << "復号に成功" << endl;
    return true;
}

string file_enc_c::get_file_pass() const
{
    return this->file_path_;
}

// ファイルポインタは先頭にして返す
size_t file_enc_c::getFileSize(FILE *fp) const
{
    if (fp == NULL)
    {
        return -1;
    }

    if (fseek(fp, 0L, SEEK_END) != 0)
    {
        return -1;
    }
    size_t file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return file_size;
}

void file_enc_c::file_delete(string file_path) const
{
    FILE *fp = fopen(file_path.c_str(), "wb");
    if (fp == NULL)
    {
        ERROR("");
        return;
    }
    fclose(fp);
    // remove(file_path.c_str());
}
