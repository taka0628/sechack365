#include "../include/key_gen.hpp"

using namespace std;

key_gen_c::key_gen_c()
{
    this->pass_.clear();
    this->key_.reset();
}

key_gen_c::~key_gen_c()
{
    if (this->key_.mem_ != nullptr) {
        this->key_.d_free();
    }
}

bool key_gen_c::set_pass(std::string const pass)
{
    if (pass.empty()) {
        ERROR_NO_COMMENT;
        return false;
    }
    this->pass_ = pass;
    return true;
}

string key_gen_c::get_pass() const
{
    if (this->pass_.empty()) {
        return "";
    }
    return this->pass_;
}

bool key_gen_c::canKeyGen() const
{
    if (this->get_pass().empty()) {
        ERROR("pass is empty");
        ErrorMsg::push_value(TO_STRING(get_pass().empty()), this->get_pass().empty());
        return false;
    }
    if (this->get_usbSerial().empty()) {
        ERROR("serial is empty");
        ErrorMsg::push_value(TO_STRING(get_usbSerial.empty()), this->get_usbSerial().empty());
        return false;
    }
    return true;
}

string key_gen_c::get_usbSerial() const
{
    const string result = this->usb_.get_usbSerial();
    if (result.empty()) {
        ERROR("USBのシリアル番号がセットされていません");
        return "";
    }
    return result;
}

bool key_gen_c::key_gen()
{
    if (this->canKeyGen() == false) {
        ERROR("鍵の生成条件を満たしていません");
        return false;
    }

    dynamic_mem_c nonce(NONCE_SIZE);
    if (this->get_nonce(nonce) == false) {
        ERROR("nonceを取得できませんでした");
    }

    string buf;
    buf = this->get_pass() + this->get_usbSerial();
    if (buf.find("\n") != string::npos) {
        buf.erase(buf.find("\n", 1));
    }
    dynamic_mem_c key;

    key.d_new(NONCE_SIZE + buf.size());
    for (size_t i = 0; i < buf.size(); i++) {
        key.mem_[i] = (u_char)buf[i];
    }
    for (size_t i = 0; i < nonce.size(); i++) {
        key.mem_[i + buf.size()] = nonce.mem_[i];
    }

    SHA_c sha;

    this->key_.d_new(SHA256_DIGEST_LENGTH);
    if (key.empty()) {
        ERROR("ハッシュ値に渡す変数が空です");
        return false;
    }
    if (sha.sha2_cal(key, this->key_, SHA_c::SHA2_bit::SHA_256) == false) {
        ERROR("鍵を取得できませんでした");
        this->key_.d_free();
        return false;
    }
    return true;
}

bool key_gen_c::get_nonce(dynamic_mem_c& to) const
{
    if (to.size() != NONCE_SIZE) {
        ERROR("nonceを格納する大きさがありません");
        return false;
    }

    file_ptr_c fp;
    if (fp.open(NONCE_FILE, "rb") == false) {
        fp.close();
        if (!this->generate_nonce()) {
            ERROR("nonceファイルの生成に失敗");
            return false;
        }
        if (fp.open(NONCE_FILE, "rb") == false) {
            ERROR("nonceファイルを開けません");
            return false;
        }
    }
    if (fread(to.mem_, 1, NONCE_SIZE, fp.fp_) != NONCE_SIZE) {
        ERROR("nonceのサイズが違います");
        return false;
    }
    return true;
}

bool key_gen_c::generate_nonce() const
{
    file_ptr_c fp;
    if (fp.open(NONCE_FILE, "wb") == false) {
        ERROR("nonceファイルが開けません");
        return false;
    }
    dynamic_mem_c rand;
    rand.d_new(NONCE_SIZE);
    RAND_bytes(rand.mem_, NONCE_SIZE);
    fwrite(rand.mem_, 1, rand.size(), fp.fp_);
    return true;
}

bool key_gen_c::set_usb(string const id)
{
    if (id.empty()) {
        ERROR("idが空");
        return false;
    }
    if (id.find(":") == string::npos) {
        ERROR("不正な引数");
        return false;
    }

    if (!this->usb_.set_usbID(id)) {
        ERROR_NO_COMMENT;
        return false;
    }

    return true;
}

string key_gen_c::get_usbID() const
{
    const string result = this->usb_.get_usbID();
    if (result.size() <= 0) {
        ERROR_NO_COMMENT;
        return "";
    }
    return result;
}

dynamic_mem_c key_gen_c::get_key() const
{
    if (this->key_.empty()) {
        ERROR("鍵がありません");
    }

    return this->key_;
}

bool key_gen_c::is_pass_correct() const
{
    if (this->get_pass().empty()) {
        return false;
    }
    file_ptr_c fp;
    fp.open(PASSWORD_HASH_FILE, "rb");
    dynamic_mem_c password_hash_from_file(HASH_SIZE);
    int read_size = fread(password_hash_from_file.mem_, 1, HASH_SIZE, fp.fp_);
    if (read_size != HASH_SIZE) {
        ERROR("パスワードのハッシュ値を取得できません");
        PUSH_VALUE(password_hash_from_file.to_string());
        return false;
    }

    SHA_c sha;
    dynamic_mem_c password, password_hash(HASH_SIZE);
    password.from_string(this->get_pass());
    if (!sha.sha2_cal(password, password_hash, SHA_c::SHA2_bit::SHA_256)) {
        ERROR("ハッシュ値の生成に失敗");
        PUSH_VALUE(this->get_pass());
        return false;
    }
    if (!password_hash.equal(password_hash_from_file)) {
        return false;
    }
    return true;
}

bool key_gen_c::set_pass2file(string const pass) const
{
    if (pass.empty()) {
        return false;
    }
    dynamic_mem_c temp, password_hash(HASH_SIZE);
    temp.from_string(pass);
    SHA_c sha;
    if (!sha.sha2_cal(temp, password_hash, SHA_c::SHA2_bit::SHA_256)) {
        ERROR("ハッシュ値の生成に失敗");
        PUSH_VALUE(pass);
        return false;
    }

    file_ptr_c fp;
    fp.open(PASSWORD_HASH_FILE, "wb");
    int write_size = fwrite(password_hash.mem_, 1, password_hash.size(), fp.fp_);
    if (write_size != HASH_SIZE) {
        ERROR("書き込みサイズがハッシュサイズと一致しません");
        PUSH_VALUE(write_size);
        return false;
    }
    return true;
}