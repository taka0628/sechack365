#include "../include/key_gen.hpp"

using namespace std;

key_gen_c::key_gen_c()
{
    this->pass_.clear();
    this->usbID_.clear();
    this->usbSerial_.clear();
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
    if (this->pass_.empty() || this->get_usbSerial().empty()) {
        ERROR("pass or serial is empty");
        log::push_value(TO_STRING(pass_.empty()), this->pass_.empty());
        log::push_value(TO_STRING(get_usbSerial.empty()), this->get_usbSerial().empty());
        return false;
    }
    return true;
}

string key_gen_c::get_usbSerial() const
{
    if (this->usbSerial_.empty()) {
        ERROR("USBのシリアル番号がセットされていません");
        return "";
    }
    return this->usbSerial_;
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
        ERROR("nonceファイルを読み取れません");
        return false;
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

bool key_gen_c::set_UsbSerial()
{
    if (this->usbID_.empty()) {
        ERROR("USBIDが指定されていません");
        return false;
    }

    FILE* fp;
    string id = this->get_usbID();

    string cmdline = "sudo lsusb -d ";
    cmdline += id;
    cmdline += " -v | grep iSerial | awk '{print $3}' ";
    cout << "cmd: " << cmdline << endl;
    if ((fp = popen(cmdline.c_str(), "r")) == NULL) {
        ERROR("can not exec commad");
        return false;
    }
    char buf[256];

    while (!feof(fp)) {
        fgets(buf, sizeof(buf), fp);
        // printf("=> %s", buf);
    }

    (void)pclose(fp);
    this->usbSerial_ = buf;
    return true;
}

bool key_gen_c::set_usbID(string const id)
{
    if (id.empty()) {
        ERROR("idが空");
        return false;
    }
    if (id.find(":") == string::npos) {
        ERROR("不正な引数");
        return false;
    }

    string cmdline;
    cmdline += "lsusb | grep ";
    cmdline += id;
    FILE* fp;
    if ((fp = popen(cmdline.c_str(), "r")) == NULL) {
        ERROR("can not exec commad");
        return false;
    }

    char buf[256] = { "0" };
    string result;
    while (!feof(fp)) {
        fgets(buf, sizeof(buf), fp);
        result += buf;
    }
    if (result.size() < 10) {
        ERROR("USBが検出できません");
        return false;
    }

    this->usbID_ = id;

    return true;
}

string key_gen_c::get_usbID() const
{
    if (this->usbID_.empty()) {
        return "";
    }
    return this->usbID_;
}

dynamic_mem_c key_gen_c::get_key() const
{
    if (this->key_.empty()) {
        ERROR("鍵がありません");
    }

    return this->key_;
}