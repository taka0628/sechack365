#include "../include/master_key_c.hpp"
#include "../include/error.hpp"

master_key_c::master_key_c(/* args */)
{
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

bool master_key_c::add_authorization(const vector<u_char> current_key, const vector<u_char> new_key)
{
    if (current_key.empty() || current_key.size() != AES_SIZE) {
        ERROR("与えられた鍵のサイズが不正");
        log::push_value(TO_STRING(current_key), current_key);
        return false;
    }
}
