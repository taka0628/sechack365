#include "../include/file_enc.hpp"

using namespace std;

file_enc_c::file_enc_c()
{
    this->isDir_       = false;
    this->isFile_      = false;
    this->isEncrypt_   = false;
    this->isNoEncrypt_ = false;
    this->isExit_      = false;
}

file_enc_c::~file_enc_c() { }

bool file_enc_c::set_file_path(string filepath)
{
    if (filepath.size() > FILE_PATH_SIZE_LIM) {
        ERROR("ファイルパスが長すぎます");
        return false;
    }
    this->file_path_ = filepath;

    if (this->file_path_.find("\n") != string::npos) {
        this->file_path_.erase(this->file_path_.find("\n"), 1);
    }
    if (this->file_path_.find("\r") != string::npos) {
        this->file_path_.erase(this->file_path_.find("\r"), 1);
    }

    fstream input_fs(this->file_path_);
    if (!input_fs) {
        ERROR("ファイルオープンに失敗");
        cerr << "filepath: " << this->file_path_ << endl;
        return false;
    }

    string buf;
    getline(input_fs, buf);
    if (!input_fs) {
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
    if (this->isFile_ && this->isExit_) {
        return true;
    }
    return false;
}

bool file_enc_c::set_password(string pass)
{
    if (pass.size() == 0) {
        ERROR("パスワードが入力されていません");
        return false;
    }
    if (pass.find("\n") != string::npos) {
        pass.erase(pass.find("\n"), 1);
    }
    if (pass.find("\r") != string::npos) {
        pass.erase(pass.find("\r"), 1);
    }
    if (pass.size() == 0) {
        ERROR("パスワード入力が不正です");
        return false;
    }
    this->password_ = pass;
    return true;
}

bool file_enc_c::file_enc()
{
    if (this->file_path_.size() == 0 || this->is_file_exit() == false) {
        ERROR("");
        return false;
    }

    fstream fs(this->file_path_);
    if (!fs) {
        ERROR("ファイルオープンに失敗");
        cerr << "filepath: " << this->file_path_ << endl;
        return false;
    }

    SHA_c sha;
    aes_c aes;
#if 0
	this->safe_pass_ = sha.sha2_cal(this->password_, SHA_c::SHA2_bit::SHA_256);

	aes.set_iv(sha.str2hex(this->safe_pass_));
	aes.set_key(sha.str2hex(this->safe_pass_));
#else
    dynamic_mem_c iv(HASH_SIZE), key(HASH_SIZE);
    RAND_bytes(iv.mem_, iv.size());
    RAND_bytes(key.mem_, key.size());
    aes.set_iv_key(iv, key);

#endif

    if (this->crypt_process(aes, file_enc_c::CRYPT_MODE::ENCRYPT) == false) {
        ERROR_NO_COMMENT;
        return false;
    }

    key_list_c key_list;
    dynamic_mem_c hash(HASH_SIZE);
    if (this->calc_file_hash(this->get_file_pass(), hash) == false) {
        ERROR_NO_COMMENT;
        return false;
    }

    if (key_list.add_file(hash, iv, key) == false) {
        ERROR("鍵リストへの登録に失敗しました");
        return false;
    }

    this->extemsion_set(file_enc_c::CRYPT_MODE::ENCRYPT);
    cout << "暗号化に成功" << endl;
    return true;
}

bool file_enc_c::file_dec()
{
    // エラーチェック
    if (this->file_path_.size() == 0 || this->is_file_exit() == false) {
        ERROR_NO_COMMENT;
        return false;
    }

    fstream fs(this->file_path_);
    if (!fs) {
        ERROR("ファイルオープンに失敗");
        cerr << "filepath: " << this->file_path_ << endl;
        return false;
    }

    // パスワードのハッシュを鍵とivに使用
    SHA_c sha;
    aes_c aes;
#if 0
	this->safe_pass_ = sha.sha2_cal(this->password_, SHA_c::SHA2_bit::SHA_256);
	aes.set_iv(sha.str2hex(this->safe_pass_));
	aes.set_key(sha.str2hex(this->safe_pass_));
#else
    dynamic_mem_c hash(HASH_SIZE), iv(AES_SIZE), key(AES_SIZE);
    if (this->calc_file_hash(this->get_file_pass(), hash) == false) {
        ERROR_NO_COMMENT;
        return false;
    }
    key_list_c key_list;
    if (key_list.pop_file(hash, iv, key) == false) {
        ERROR_NO_COMMENT;
        return false;
    }
    aes.set_iv_key(iv, key);
#endif

    if (this->crypt_process(aes, file_enc_c::CRYPT_MODE::DECRYPT) == false) {
        ERROR_NO_COMMENT;
        return false;
    }

    this->extemsion_set(file_enc_c::CRYPT_MODE::DECRYPT);
    cout << "復号に成功" << endl;
    return true;
}

string file_enc_c::get_file_pass() const { return this->file_path_; }

// ファイルポインタは先頭にして返す
size_t file_enc_c::getFileSize(FILE* fp) const
{
    if (fp == NULL) {
        return -1;
    }

    if (fseek(fp, 0L, SEEK_END) != 0) {
        return -1;
    }
    size_t file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return file_size;
}

void file_enc_c::file_delete(string const file_path) const
{
    file_ptr_c fp(file_path.c_str(), "wb");
}

bool file_enc_c::crypt_process(aes_c& aes,
    file_enc_c::CRYPT_MODE const mode) const
{
    const int BUF_SIZE = 2048;
    const string buff_file_name(CRYPT_BUFFER_FILE);

    dynamic_mem_c buf;
    buf.d_new(BUF_SIZE);

    file_ptr_c FP(this->get_file_pass().c_str(), "rb");

    // バッファ用ファイルを作成
    file_ptr_c FP_buffer(buff_file_name.c_str(), "wb");

    int read_size = 0;

    dynamic_mem_c out_buf;
    out_buf.d_new(BUF_SIZE);

    // 暗号化/復号
    switch (mode) {
    case file_enc_c::CRYPT_MODE::ENCRYPT:
        while ((read_size = fread(buf.mem_, 1, 1024, FP.fp_)) > 0) {
            aes.encrypt(out_buf, buf, aes_c::AES_bit_e::aes_256);
            fwrite(out_buf.mem_, 1, read_size, FP_buffer.fp_);
            // out_buf.reset();
            buf.reset();
        }
        break;

    case file_enc_c::CRYPT_MODE::DECRYPT:
        while ((read_size = fread(buf.mem_, 1, 1024, FP.fp_)) > 0) {
            aes.decrypt(out_buf, buf, aes_c::AES_bit_e::aes_256);
            fwrite(out_buf.mem_, 1, read_size, FP_buffer.fp_);
            out_buf.reset();
            buf.reset();
        }
        break;

    default:
        ERROR("");
        break;
    }

    // ファイル出力
    FP.reopen(this->get_file_pass().c_str(), "wb");
    FP_buffer.reopen(buff_file_name.c_str(), "rb");

    while ((read_size = fread(buf.mem_, 1, 1024, FP_buffer.fp_)) > 0) {
        fwrite(buf.mem_, 1, read_size, FP.fp_);
    }
    this->file_delete(buff_file_name);

    return true;
}

bool file_enc_c::calc_file_hash(const string file_name,
    dynamic_mem_c& out) const
{
    file_ptr_c FP;
    FP.open(file_name, "rb");

    fseek(FP.fp_, 0, SEEK_END);
    size_t file_size = ftell(FP.fp_);
    dynamic_mem_c buffer(file_size);

    rewind(FP.fp_);
    fread(buffer.mem_, 1, file_size, FP.fp_);
    dynamic_mem_c hash(HASH_SIZE);

    SHA_c sha;
    sha.sha2_cal(buffer, hash, SHA_c::SHA2_bit::SHA_256);
    if (out.size() < hash.size()) {
        return false;
    }
    memcpy(out.mem_, hash.mem_, hash.size());
    return true;
}

void file_enc_c::extemsion_set(const file_enc_c::CRYPT_MODE mode)
{
    // 拡張子変更
    string new_file_name = this->get_file_pass();
    switch (mode) {
    case file_enc_c::CRYPT_MODE::ENCRYPT:
        new_file_name += ".enc";
        if (rename(this->get_file_pass().c_str(), new_file_name.c_str())) {
            ERROR("ファイル名の変更に失敗");
            return;
        }
        break;

    case file_enc_c::CRYPT_MODE::DECRYPT:
        if (new_file_name.find(".enc") != string::npos) {
            new_file_name.erase(new_file_name.find(".enc"), 4);
        }
        if (rename(this->get_file_pass().c_str(), new_file_name.c_str())) {
            ERROR("ファイル名の変更に失敗");
            return;
        }
        break;

    default:
        break;
    }
}