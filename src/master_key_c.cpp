#include "../include/master_key_c.hpp"

master_key_c::master_key_c()
{
    this->master_key_.d_free();
}

master_key_c::~master_key_c()
{
}

using namespace std;

bool master_key_c::isCorrect() const
{
    if (this->master_key_.empty() == true) {
        return false;
    }
    if (this->master_key_.size() != AES_SIZE) {
        return false;
    }
    return true;
}

dynamic_mem_c master_key_c::get_key() const
{
    if (this->isCorrect() == false) {
        ERROR("master key is false");
        log::push_value("this->master_key_.size()", this->master_key_.size());
        exit(1);
    }
    return this->master_key_;
}

bool master_key_c::push_key(const dynamic_mem_c enc_mkey, const dynamic_mem_c iv, const dynamic_mem_c key) const
{
    if (enc_mkey.size() != AES_SIZE || iv.size() != AES_SIZE || key.size() != AES_SIZE) {
        ERROR("鍵のサイズが不正");
        log::push_value("enc_mkey.size()", enc_mkey.size());
        log::push_value("iv.size()", iv.size());
        log::push_value("key.size()", key.size());
        return false;
    }
    // 鍵のハッシュ値
    dynamic_mem_c hash_key(HASH_SIZE);
    SHA_c sha;
    if (!sha.sha2_cal(enc_mkey, hash_key, SHA_c::SHA2_bit::SHA_256)) {
        ERROR("ハッシュ計算エラー");
        return false;
    }
    if (hash_key.size() != HASH_SIZE) {
        ERROR("ハッシュサイズエラー");
        log::push_value("hash_key.size()", hash_key.size());
        return false;
    }

    file_ptr_c fp;
    if (!fp.open(MASTER_KEY_LIST_FILE, "wb")) {
        ERROR("ファイルが開けません");
        return false;
    }
    fwrite(hash_key.mem_, 1, hash_key.size(), fp.fp_);
    fwrite(enc_mkey.mem_, 1, enc_mkey.size(), fp.fp_);
    fwrite(iv.mem_, 1, iv.size(), fp.fp_);
    return true;
}

bool master_key_c::init(string usb_id, string pass_word)
{
    if (usb_id.empty() || pass_word.empty()) {
        ERROR("引数が空");
        PUSH_VALUE(usb_id);
        PUSH_VALUE(pass_word);
        return false;
    }

    dynamic_mem_c mkey(AES_SIZE);
    RAND_bytes(mkey.mem_, AES_SIZE);

    // mkeyを暗号化するための鍵生成
    key_gen_c crypt_key;
    if (!crypt_key.set_pass(pass_word)) {
        ERROR("パスワードをセットできません");
        PUSH_VALUE(pass_word);
        return false;
    }
    if (!crypt_key.set_usbID(usb_id)) {
        ERROR("usbIDがセットできません");
        PUSH_VALUE(usb_id);
        return false;
    }
    if (!crypt_key.set_UsbSerial()) {
        ERROR("usb serialがセットできません");
        return false;
    }
    if (!crypt_key.key_gen()) {
        ERROR("鍵生成ができませんでした");
        return false;
    }
    if (!this->enc_mkey(crypt_key.get_key())) {
        ERROR("mkeyの暗号化に失敗");
        return false;
    }
    return true;
}

bool master_key_c::enc_mkey(const dynamic_mem_c key) const
{
    dynamic_mem_c enc_mkey;
    if (!this->isCorrect()) {
        ERROR("mkeyが格納されていません");
        return false;
    }
    dynamic_mem_c iv(AES_SIZE);
    RAND_bytes(iv.mem_, AES_SIZE);
    aes_c aes;
    aes.set_iv_key(iv, key);
    enc_mkey.d_new(AES_SIZE);
    aes.encrypt(enc_mkey, this->get_key(), aes_c::AES_bit_e::aes_256);
    if (enc_mkey.size() != AES_SIZE) {
        ERROR("鍵のサイズが不正");
        log::push_value("enc_mkey.size()", enc_mkey.size());
        return false;
    }
    if (!this->push_key(enc_mkey, iv, key)) {
        ERROR("file output error");
        return false;
    }
    return true;
}

vector<u_char> master_key_c::get_hash() const
{
    assert(!this->master_key_.empty());
    vector<u_char> result;
    if (!this->isCorrect()) {
        result.clear();
        return result;
    }
    SHA_c sha;
    dynamic_mem_c hash(AES_SIZE);
    sha.sha2_cal(this->get_key(), hash, SHA_c::SHA2_bit::SHA_256);
    return result = hash.to_vector();
}