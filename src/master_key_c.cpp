#include "../include/master_key_c.hpp"

master_key_c::master_key_c()
{
    this->master_key_.d_free();
    this->iv_.d_free();
}

master_key_c::~master_key_c()
{
}

using namespace std;

dynamic_mem_c master_key_c::get_master_key() const
{
    if (this->master_key_.size() != AES_SIZE) {
        ERROR("master key is false");
        log::push_value("this->master_key_.size()", this->master_key_.size());
        exit(1);
    }
    return this->master_key_;
}

dynamic_mem_c master_key_c::get_master_key(const string usb_id, const string password)
{
    dynamic_mem_c error;
    if (usb_id.empty() || password.empty()) {
        ERROR("引数が不正");
        PUSH_VALUE(usb_id.size());
        PUSH_VALUE(password.size());
        return error;
    }
    dynamic_mem_c crypt_key = this->generate_crypt_key(usb_id, password);
    if (crypt_key.empty()) {
        ERROR("鍵が生成できません");
        return error;
    }
    dynamic_mem_c crypt_key_hash(AES_SIZE);
    SHA_c sha;
    if (!sha.sha2_cal(crypt_key, crypt_key_hash, SHA_c::SHA2_bit::SHA_256)) {
        ERROR("ハッシュ値を計算できません");
        return error;
    }
    dynamic_mem_c iv, enc_mkey;
    if (!this->get_key_from_file(crypt_key_hash, iv, enc_mkey)) {
        ERROR("鍵を取得できません");
        return error;
    }
    if (!this->dec_mkey(crypt_key, enc_mkey, iv)) {
        ERROR("mkeyを復号できませんでした");
        return error;
    }
    return this->get_master_key();
}

bool master_key_c::dec_mkey(const dynamic_mem_c crypt_key, const dynamic_mem_c enc_mkey, const dynamic_mem_c iv)
{
    if (crypt_key.size() != AES_SIZE || enc_mkey.size() != AES_SIZE || iv.size() != AES_SIZE) {
        ERROR("不正な引数");
        PUSH_VALUE(crypt_key.size());
        PUSH_VALUE(enc_mkey.size());
        PUSH_VALUE(iv.size());
        return false;
    }
    aes_c aes;
    if (!aes.set_iv_key(iv, crypt_key)) {
        ERROR("鍵をセットできません");
        return false;
    }
    dynamic_mem_c mkey(AES_SIZE);
    aes.decrypt(mkey, enc_mkey, aes_c::AES_bit_e::aes_256);
    if (mkey.size() != AES_SIZE) {
        ERROR("復号した鍵のサイズが違います");
        PUSH_VALUE(mkey.size());
    }
    this->master_key_.copy(mkey);
    return true;
}

bool master_key_c::get_key_from_file(const dynamic_mem_c hash, dynamic_mem_c& iv, dynamic_mem_c& enc_key) const
{
    if (hash.size() == 0) {
        ERROR("ハッシュ値が空");
        return false;
    }
    // ファイル読み込み
    file_ptr_c fp;
    fp.open(MASTER_KEY_LIST_FILE, "rb");
    dynamic_mem_c read_buf(HASH_SIZE + AES_SIZE * 2);

    int read_size   = 0;
    bool isFindHash = false;
    while ((read_size = fread(read_buf.mem_, 1, read_buf.size(), fp.fp_)) > 0) {
        if (static_cast<size_t>(read_size) != read_buf.size()) {
            break;
        }
        if (memcmp(read_buf.mem_, hash.mem_, HASH_SIZE) == 0) {
            isFindHash = true;
            break;
        }
    }
    if (!isFindHash) {
        ERROR("鍵を見つけられませんでした");
        PUSH_VALUE(hash.to_string());
        return false;
    }
    iv.d_new(AES_SIZE);
    enc_key.d_new(AES_SIZE);
    for (size_t i = 0; i < AES_SIZE; i++) {
        iv.mem_[i]      = read_buf.mem_[i + HASH_SIZE];
        enc_key.mem_[i] = read_buf.mem_[i + HASH_SIZE + AES_SIZE];
    }
    return true;
}

bool master_key_c::push_key(const dynamic_mem_c crypt_key, const dynamic_mem_c iv, const dynamic_mem_c enc_mkey) const
{
    if (crypt_key.size() != AES_SIZE || enc_mkey.size() != AES_SIZE || iv.size() != AES_SIZE) {
        ERROR("引数が不正");
        log::push_value("crypt_key.size()", crypt_key.size());
        log::push_value("enc_mkey.size()", enc_mkey.size());
        log::push_value("iv.size()", iv.size());
        return false;
    }
    // 暗号鍵のハッシュ値
    dynamic_mem_c hash_key(HASH_SIZE);
    SHA_c sha;
    if (!sha.sha2_cal(crypt_key, hash_key, SHA_c::SHA2_bit::SHA_256)) {
        ERROR("ハッシュ計算エラー");
        return false;
    }
    if (hash_key.size() != HASH_SIZE) {
        ERROR("ハッシュサイズエラー");
        log::push_value("hash_key.size()", hash_key.size());
        return false;
    }

    // 鍵をファイルに追加
    file_ptr_c fp;
    if (!fp.open(MASTER_KEY_LIST_FILE, "ab")) {
        ERROR("ファイルが開けません");
        return false;
    }
    fwrite(hash_key.mem_, 1, hash_key.size(), fp.fp_);
    fwrite(iv.mem_, 1, iv.size(), fp.fp_);
    fwrite(enc_mkey.mem_, 1, enc_mkey.size(), fp.fp_);
    return true;
}

bool master_key_c::init(const string usb_id, const string pass_word)
{
    if (usb_id.empty() || pass_word.empty()) {
        ERROR("引数が空");
        PUSH_VALUE(usb_id);
        PUSH_VALUE(pass_word);
        exit(1);
    }

    this->master_key_.d_new(AES_SIZE);
    RAND_bytes(this->master_key_.mem_, AES_SIZE);

    dynamic_mem_c crypt_key = this->generate_crypt_key(usb_id, pass_word);
    if (crypt_key.size() != AES_SIZE) {
        ERROR("mkeyを暗号化する鍵のサイズが違います");
        PUSH_VALUE(crypt_key.size());
        PUSH_VALUE(crypt_key.to_string());
        exit(1);
    }

    dynamic_mem_c enc_mkey = this->enc_mkey(crypt_key);
    if (enc_mkey.size() != AES_SIZE) {
        ERROR("mkey size");
        log::push_value(TO_STRING(enc_mkey.size()), enc_mkey.size());
        exit(1);
    }

    // ファイルを初期化
    file_ptr_c fp;
    fp.open(MASTER_KEY_LIST_FILE, "wb");
    fp.close();

    // mkeyをファイルへ追加
    if (!this->push_key(crypt_key, this->get_iv(), enc_mkey)) {
        ERROR("mkeyをファイルへ追加できませんでした");
        PUSH_VALUE(crypt_key.size());
        PUSH_VALUE(crypt_key.to_string());
        PUSH_VALUE(enc_mkey.size());
        PUSH_VALUE(enc_mkey.to_string());
        PUSH_VALUE(this->get_iv().size());
        PUSH_VALUE(this->get_iv().to_string());
        exit(1);
    }

    return true;
}

dynamic_mem_c master_key_c::generate_crypt_key(const string usb_id, const string password) const
{
    dynamic_mem_c error;
    if (usb_id.empty() || password.empty()) {
        ERROR("引数が空です");
        PUSH_VALUE(usb_id.empty());
        PUSH_VALUE(password.empty());
        return error;
    }
    key_gen_c key_gen;
    if (!key_gen.set_pass(password)) {
        ERROR("パスワードをセットできません");
        PUSH_VALUE(password);
        return error;
    }
    if (!key_gen.set_usbID(usb_id)) {
        ERROR("usbIDがセットできません");
        PUSH_VALUE(usb_id);
        return error;
    }
    if (!key_gen.set_UsbSerial()) {
        ERROR("usb serialがセットできません");
        return error;
    }
    if (!key_gen.key_gen()) {
        ERROR("鍵生成ができませんでした");
        return error;
    }
    return key_gen.get_key();
}

dynamic_mem_c
master_key_c::enc_mkey(const dynamic_mem_c key)
{
    dynamic_mem_c enc_mkey;
    if (this->master_key_.size() != AES_SIZE) {
        ERROR("鍵が格納されていません");
        PUSH_VALUE(this->master_key_.size());
        return enc_mkey;
    }
    this->iv_.d_new(AES_SIZE);
    RAND_bytes(this->iv_.mem_, AES_SIZE);
    aes_c aes;
    aes.set_iv_key(this->get_iv(), key);
    enc_mkey.d_new(AES_SIZE);
    aes.encrypt(enc_mkey, this->get_master_key(), aes_c::AES_bit_e::aes_256);
    if (enc_mkey.size() != AES_SIZE) {
        ERROR("鍵のサイズが不正");
        log::push_value("enc_mkey.size()", enc_mkey.size());
        exit(1);
    }

    return enc_mkey;
}

dynamic_mem_c master_key_c::get_iv() const
{
    return this->iv_;
}

bool master_key_c::add_authorization(const string root_usb_id, const string password, const string new_usb_id)
{
    if (root_usb_id.empty() || password.empty() || new_usb_id.empty()) {
        ERROR("引数が空");
        PUSH_VALUE(root_usb_id.empty());
        PUSH_VALUE(password.empty());
        PUSH_VALUE(new_usb_id.empty());
        return false;
    }
    dynamic_mem_c master_key = this->get_master_key(root_usb_id, password);
    if (master_key.size() != AES_SIZE) {
        ERROR("マスターキーのサイズが不正");
        PUSH_VALUE(master_key.to_string());
        return false;
    }
    dynamic_mem_c new_crypt_key = this->generate_crypt_key(new_usb_id, password);
    if (new_crypt_key.size() != AES_SIZE) {
        ERROR("共通鍵の生成エラー");
        PUSH_VALUE(new_crypt_key.to_string());
        return false;
    }
    dynamic_mem_c enc_master_key = this->enc_mkey(new_crypt_key);
    if (enc_master_key.size() != AES_SIZE) {
        ERROR("mkeyを暗号化できません");
        PUSH_VALUE(enc_master_key.to_string());
        return false;
    }
    if (!this->push_key(new_crypt_key, this->get_iv(), enc_master_key)) {
        ERROR("mkeyをファイルへ追加できませんでした");
        return false;
    }
    return true;
}