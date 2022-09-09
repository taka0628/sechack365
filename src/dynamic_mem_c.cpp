#include "../include/dynamic_mem_c.hpp"

dynamic_mem_c::dynamic_mem_c()
{
    this->size_ = 0;
    this->mem_  = nullptr;
}
dynamic_mem_c::dynamic_mem_c(const uint size)
{
    if (size == 0) {
        this->mem_  = nullptr;
        this->size_ = size;
        return;
    }
    this->size_ = size;
    try {
        this->mem_ = new u_char[size];
    } catch (std::bad_alloc& e) {
        ERROR(e.what());
    }
    memset(this->mem_, 0, size);
}

dynamic_mem_c::~dynamic_mem_c()
{
    if (this->mem_) {
        delete[] this->mem_;
        this->mem_ = nullptr;
    }
    this->size_ = 0;
}

dynamic_mem_c::dynamic_mem_c(const dynamic_mem_c& from)
{
    if (from.size() == 0) {
        this->size_ = 0;
        this->mem_  = nullptr;
        return;
    }
    this->mem_  = new u_char[from.size()];
    this->size_ = from.size();
    for (size_t i = 0; i < this->size(); i++) {
        this->mem_[i] = from.mem_[i];
    }
    return;
}

using namespace std;

dynamic_mem_c& dynamic_mem_c::operator=(const dynamic_mem_c& from)
{
    if (this == &from) {
        return *this;
    }

    if (from.size() == 0) {
        return *this;
    }

    if (this->size() != from.size()) {
        this->size_ = from.size();
        if (this->mem_ != nullptr) {
            this->d_free();
        }
        this->d_new(from.size());
    }
    for (size_t i = 0; i < this->size(); i++) {
        this->mem_[i] = from.mem_[i];
    }
    return *this;
}

void dynamic_mem_c::d_new(const uint size)
{
    if (this->mem_) {
        delete[] this->mem_;
        this->mem_ = nullptr;
    }
    this->mem_ = new unsigned char[size];
    memset(this->mem_, 0, size);
    this->size_ = size;
}

void dynamic_mem_c::d_free()
{
    this->reset();
    if (this->mem_) {
        delete[] this->mem_;
        this->mem_ = nullptr;
    }
    this->size_ = 0;
}

size_t dynamic_mem_c::size() const { return this->size_; }

void dynamic_mem_c::copy(const dynamic_mem_c from, const uint size)
{
    if (from.size() == 0 || size == 0) {
        return;
    }
    if (this->mem_) {
        this->d_free();
    }
    this->d_new(size);
    for (size_t i = 0; i < size; i++) {
        this->mem_[i] = from.mem_[i];
    }
}

void dynamic_mem_c::copy(const dynamic_mem_c from)
{
    if (from.size() == 0) {
        return;
    }
    if (this->mem_) {
        this->d_free();
    }
    this->d_new(from.size());
    for (size_t i = 0; i < from.size(); i++) {
        this->mem_[i] = from.mem_[i];
    }
}

void dynamic_mem_c::reset()
{
    if (this->mem_) {
        memset(this->mem_, 0, this->size());
    }
}

bool dynamic_mem_c::empty() const
{
    if (this->size() == 0 || this->mem_ == nullptr) {
        return true;
    }
    bool isEmpty = true;
    for (size_t i = 0; i < this->size(); i++) {
        if (this->mem_[i] != 0) {
            isEmpty = false;
            break;
        }
    }
    if (isEmpty == true) {
        return true;
    }
    return false;
}

vector<u_char> dynamic_mem_c::to_vector() const
{
    vector<u_char> result;
    if (this->size() == 0) {
        result.clear();
        return result;
    }
    for (size_t i = 0; i < this->size(); i++) {
        result.push_back(this->mem_[i]);
    }
    return result;
}

bool dynamic_mem_c::from_vector(const std::vector<u_char>& src)
{
    if (src.empty()) {
        return false;
    }
    if (this->size() != 0) {
        this->d_free();
    }
    this->d_new(src.size());
    for (size_t i = 0; i < src.size(); i++) {
        this->mem_[i] = src[i];
    }
    return true;
}

std::string dynamic_mem_c::to_string_table(const u_int i) const
{
    if (i > 15) {
        ERROR("index error");
        exit(1);
    }
    switch (i) {
    case 0:
        return "0";
    case 1:
        return "1";
    case 2:
        return "2";
    case 3:
        return "3";
    case 4:
        return "4";
    case 5:
        return "5";
    case 6:
        return "6";
    case 7:
        return "7";
    case 8:
        return "8";
    case 9:
        return "9";
    case 10:
        return "A";
    case 11:
        return "B";
    case 12:
        return "C";
    case 13:
        return "D";
    case 14:
        return "E";
    case 15:
        return "F";

    default:
        ERROR("unexpected arg");
        cout << "mem_: " << (u_int)this->mem_[i] << endl;
        exit(1);
    }
}

string dynamic_mem_c::to_string() const
{
    if (this->size() == 0) {
        return "";
    }
    string result(this->size(), 0);
    for (size_t i = 0; i < this->size(); i++) {
        int temp = this->mem_[i];
        result += this->to_string_table((temp >> 4));
        result += this->to_string_table((temp & 0x0F));
    }
    return result;
}

bool dynamic_mem_c::equal(const dynamic_mem_c& arg) const
{
    if (this->size() != arg.size()) {
        return false;
    }
    // どちらかのサイズが0の場合はメモリへにアクセスするのは危険
    // 確保されていることが保証されていない
    if (this->size() == 0 || arg.size() == 0) {
        return true;
    }
    assert(this->size() == arg.size());
    for (size_t i = 0; i < this->size(); i++) {
        if (this->mem_[i] != arg.mem_[i]) {
            return false;
        }
    }
    return true;
}

bool dynamic_mem_c::from_string(const string& src)
{
    if (src.empty()) {
        return false;
    }
    if (this->size() != src.size()) {
        this->d_free();
        this->d_new(src.size());
    }
    for (size_t i = 0; i < this->size(); i++) {
        this->mem_[i] = static_cast<u_char>(src[i]);
    }
    return true;
}