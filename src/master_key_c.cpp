#include "../include/master_key_c.hpp"
#include "../include/error.hpp"

master_key_c::master_key_c()
{
    this->master_key_.clear();
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

vector<u_char> master_key_c::get_key() const
{
    if (this->isCorrect() == false) {
        ERROR("master key is false");
        log::push_value(TO_STRING(master_key_), this->master_key_);
        exit(1);
    }
    return this->master_key_;
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
    crypt_key.get_key();
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
    dynamic_mem_c mkey;
    mkey.from_vector(this->master_key_);
    dynamic_mem_c hash(AES_SIZE);
    sha.sha2_cal(mkey, hash, SHA_c::SHA2_bit::SHA_256);
    return result = hash.to_vector();
}