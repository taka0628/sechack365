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

    string temp;
    string out_buf;
    out_buf.clear();
    fs.seekg(0, ios_base::beg);

    // int fd = 0;
    // char buf[2048];
    // memset(buf, 0, sizeof(buf));
    // if ((fd = open(this->get_file_pass().c_str(), O_RDONLY)) > 0)
    // {
    //     int n = 0;
    //     while ((n = read(fd, buf, sizeof(buf))) > 0)
    //     {
    //         aes.encrypt(temp, buf, aes_c::AES_bit_e::aes_256);
    //         out_buf += temp;
    //         temp.clear();
    //         memset(buf, 0, sizeof(buf));
    //     }
    // }
    // else
    // {
    //     puts("ファイルが存在しません");
    // }
    string buffer, buffer_sub;
    while (getline(fs, buffer, '/'))
    {
        getline(fs, buffer_sub);
        if (fs)
        {
            buffer_sub += '/';
            buffer += '/';
        }else{
            buffer += '/';
        }
        buffer += buffer_sub;
        aes.encrypt(temp, buffer, aes_c::AES_bit_e::aes_256);
        out_buf += temp;
        buffer.clear();
        temp.clear();
        buffer_sub.clear();
    }
    fs.close();

    // ファイル出力
    ofstream out_fs;
    out_fs.open(this->get_file_pass(), ios::trunc);
    out_fs << out_buf;
    out_fs.close();

    // 拡張子変更
    string new_file_name = this->get_file_pass() + ".enc";
    if (rename(this->get_file_pass().c_str(), new_file_name.c_str()))
    {
        ERROR("ファイル名の変更に失敗");
        return false;
    }
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
    while (getline(fs, buffer, '/'))
    {
        getline(fs, buffer_sub);
        if (fs)
        {
            buffer_sub += '/';
            buffer += '/';
        }else{
            buffer += '/';
        }
        buffer += buffer_sub;
        aes.decrypt(temp, buffer, aes_c::AES_bit_e::aes_256);
        out_buf += temp;
        buffer.clear();
        temp.clear();
        buffer_sub.clear();
    }
    fs.close();

    // string buffer;
    // FILE *fp = fopen(this->get_file_pass().c_str(), O_RDONLY);
    // char buf[1024];
    // memset(buf, 0, sizeof(buf));
    // while (fread(buf, sizeof(char), sizeof(buf), fp) > 0)
    // {
    //     aes.decrypt(temp, buf, aes_c::AES_bit_e::aes_256);
    //     out_buf += temp;
    //     temp.clear();
    //     memset(buf, 0, sizeof(buf));
    // }
    // fclose(fp);

    // ファイル名変更
    ofstream out_fs;
    out_fs.open(this->get_file_pass(), ios::trunc);
    out_fs << out_buf;
    out_fs.close();
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
