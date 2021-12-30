#include "../include/file_enc.hpp"

using namespace std;

key_list_c::key_list_c() { file_ptr_c fp(KEY_FILE_NAME, "a"); }

key_list_c::~key_list_c() {}

string key_list_c::get_file_name() const
{
    if (this->key_file_name_.empty()) {
        ERROR("ファイル名が指定されていません");
        return nullptr;
    }
    return this->key_file_name_;
}

bool key_list_c::pop_file(dynamic_mem_c const& hash, dynamic_mem_c& iv,
    dynamic_mem_c& key)
{
    if (hash.empty()) {
        return false;
    }

    file_ptr_c fp(this->get_file_name().c_str(), "rb");
    fseek(fp.fp_, 0, SEEK_SET);

    bool isFindHash      = false;
    const uint line_size = HASH_SIZE + AES_SIZE * 2;
    dynamic_mem_c buffer(line_size);
    u_char temp[HASH_SIZE];
    size_t read_size = 0;

    // ハッシュ値を検索
    while ((read_size = fread(buffer.mem_, 1, line_size, fp.fp_)) > 0) {
        if (read_size != line_size) {
            break;
        }
        memcpy(temp, buffer.mem_, HASH_SIZE);
        if (memcmp(temp, hash.mem_, HASH_SIZE) == 0) {
            isFindHash = true;
            break;
        }
    }
    fp.close();

    if (isFindHash == false) {
        return false;
    }

    // iv, keyをコピー
    for (size_t i = 0; i < HASH_SIZE; i++) {
        iv.mem_[i]  = buffer.mem_[i + HASH_SIZE];
        key.mem_[i] = buffer.mem_[i + HASH_SIZE + AES_SIZE];
    }

    this->plug(hash);

    return true;
}

bool key_list_c::plug(const dynamic_mem_c& hash)
{
    // 読み取りファイル
    file_ptr_c fp(this->get_file_name().c_str(), "rb");

    // バッファ用ファイル
    const string buffer_file_name = BUFFER_FILE_NAME;
    file_ptr_c buffer_fp(buffer_file_name.c_str(), "wb");

    const uint line_size = HASH_SIZE + AES_SIZE * 2;
    dynamic_mem_c buffer(line_size), temp(HASH_SIZE);

    // バッファへ該当ハッシュ値のファイルの除いて書き出し
    size_t read_size = 0;
    while ((read_size = fread(buffer.mem_, 1, line_size, fp.fp_)) > 0) {
        if (read_size != line_size) {
            break;
        }
        if (memcmp(buffer.mem_, hash.mem_, HASH_SIZE) == 0) {
            continue;
        }
        fwrite(buffer.mem_, 1, line_size, buffer_fp.fp_);
    }

    // バッファを読み取り元ファイルへ書き出し
    buffer_fp.reopen(buffer_file_name.c_str(), "rb");
    fp.reopen(this->get_file_name().c_str(), "wb");
    while ((read_size = fread(buffer.mem_, 1, line_size, buffer_fp.fp_))) {
        fwrite(buffer.mem_, 1, read_size, fp.fp_);
    }
    // バッファ用ファイルを初期化
    buffer_fp.reopen(buffer_file_name.c_str(), "wb");
    return true;
}

bool key_list_c::add_file(dynamic_mem_c const& hash, dynamic_mem_c const& iv,
    dynamic_mem_c const& key) const
{
    // hashに値は入っているか？
    if (hash.empty() == true || iv.empty() == true || key.empty() == true) {
        return false;
    }

    file_ptr_c fp;
    fp.open(this->get_file_name().c_str(), "ab");

    fwrite(hash.mem_, 1, hash.size(), fp.fp_);
    fwrite(iv.mem_, 1, iv.size(), fp.fp_);
    fwrite(key.mem_, 1, key.size(), fp.fp_);

    return true;
}

bool key_list_c::encrypt(dynamic_mem_c const& key) const
{
    if (key.empty() || key.size() != AES_SIZE) {
        ERROR_NO_COMMENT;
        return false;
    }

    file_ptr_c fp;
    if (fp.open(this->get_file_name(), "rb") == false) {
        ERROR_NO_COMMENT;
        return false;
    }

    aes_c aes;
    dynamic_mem_c iv;
    iv.d_new(AES_SIZE);
    RAND_bytes(iv.mem_, iv.size());
    aes.set_iv_key(iv, key);
    file_enc_c file_enc;
    file_enc.set_file_path(this->get_file_name());

    if (file_enc.crypt_process(aes, file_enc_c::CRYPT_MODE::ENCRYPT) == false) {
        ERROR_NO_COMMENT;
        return false;
    }

    fp.reopen(this->get_file_name().c_str(), "ab");
    fwrite(iv.mem_, 1, iv.size(), fp.fp_);
    fp.close();

    file_enc.extemsion_set(file_enc_c::CRYPT_MODE::ENCRYPT);

    this->key_list_pkey_update(key);

    return true;
}

bool key_list_c::decrypt(dynamic_mem_c const& key) const
{
    if (key.empty() || key.size() != AES_SIZE) {
        ERROR_NO_COMMENT;
        return false;
    }
    if (this->key_check(key) == false) {
        ERROR("鍵が違います");
        sleep(1);
        return false;
    }
    file_ptr_c fp;
    if (fp.open(this->get_file_name() + ".enc", "rb") == false) {
        ERROR_NO_COMMENT;
        return false;
    }

    dynamic_mem_c iv;
    iv.d_new(AES_SIZE);
    fseek(fp.fp_, -iv.size(), SEEK_END);
    size_t read_size = fread(iv.mem_, 1, iv.size(), fp.fp_);
    if (read_size != AES_SIZE) {
        ERROR_NO_COMMENT;
        return false;
    }

    // 末尾のivを削除
    fseek(fp.fp_, 0, SEEK_SET);
    file_ptr_c buff_fp;
    dynamic_mem_c buff;
    buff.d_new(AES_SIZE);
    buff_fp.open(BUFFER_FILE_NAME, "wb");
    while (fread(buff.mem_, 1, buff.size(), fp.fp_) > 0) {
        if (memcmp(buff.mem_, iv.mem_, iv.size()) == 0) {
            break;
        }
        fwrite(buff.mem_, 1, buff.size(), buff_fp.fp_);
    }
    fp.reopen(this->get_file_name() + ".enc", "wb");
    buff_fp.reopen(BUFFER_FILE_NAME, "rb");
    while (fread(buff.mem_, 1, buff.size(), buff_fp.fp_) > 0) {
        fwrite(buff.mem_, 1, buff.size(), fp.fp_);
    }
    buff_fp.close();
    fp.close();

    // ファイル復号
    aes_c aes;
    aes.set_iv_key(iv, key);
    file_enc_c file_enc;
    file_enc.set_file_path(this->get_file_name() + ".enc");

    if (file_enc.crypt_process(aes, file_enc_c::CRYPT_MODE::DECRYPT) == false) {
        ERROR_NO_COMMENT;
        return false;
    }

    file_enc.extemsion_set(file_enc_c::CRYPT_MODE::DECRYPT);
    return true;
}

bool key_list_c::key_check(dynamic_mem_c const& key) const
{
    if (key.size() < AES_SIZE || key.empty()) {
        ERROR_NO_COMMENT;
        return false;
    }
    file_ptr_c fp;
    if (fp.open(KEY_HASH_FILE, "rb") == false) {
        ERROR_NO_COMMENT;
        return false;
    }

    dynamic_mem_c temp;
    temp.d_new(AES_SIZE);
    size_t read_size = fread(temp.mem_, 1, temp.size(), fp.fp_);
    if (read_size != temp.size()) {
        ERROR_NO_COMMENT;
        return false;
    }

    SHA_c sha;
    dynamic_mem_c hash;
    hash.d_new(AES_SIZE);
    sha.sha2_cal(key, hash, SHA_c::SHA2_bit::SHA_256);
    if (memcmp(hash.mem_, temp.mem_, hash.size()) == 0) {
        return true;
    }
    return false;
}

bool key_list_c::key_list_pkey_update(dynamic_mem_c const& key) const
{
    if (key.mem_ == nullptr || key.size() != AES_SIZE) {
        ERROR_NO_COMMENT;
        return false;
    }

    file_ptr_c fp;
    if (fp.open(KEY_HASH_FILE, "wb") == false) {
        ERROR_NO_COMMENT;
        return false;
    }

    SHA_c sha;
    dynamic_mem_c hash;
    hash.d_new(HASH_SIZE);

    sha.sha2_cal(key, hash, SHA_c::SHA2_bit::SHA_256);
    if (fwrite(hash.mem_, 1, hash.size(), fp.fp_) != hash.size()) {
        ERROR_NO_COMMENT;
        return false;
    }
    return true;
}
