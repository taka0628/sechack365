#include "../include/dynamic_mem_c.hpp"

dynamic_mem_c::dynamic_mem_c() {
    this->size_ = 0;
    this->mem_ = nullptr;
}
dynamic_mem_c::dynamic_mem_c(const uint size) {
    this->size_ = size;
    try {
        this->mem_ = new u_char[size];
    } catch (std::bad_alloc) {
        ERROR("");
    }
    memset(this->mem_, 0, size);
}

dynamic_mem_c::~dynamic_mem_c() {
    if (this->mem_) {
        delete this->mem_;
    }
}

dynamic_mem_c::dynamic_mem_c(const dynamic_mem_c &from) {
    size_ = from.size_;
    if (from.size_ > 0) {
        mem_ = new u_char[size_];
    }
    for (size_t i = 0; i < size_; i++) {
        mem_[i] = from.mem_[i];
    }
    return;
}

using namespace std;

dynamic_mem_c &dynamic_mem_c::operator=(const dynamic_mem_c &from) {
    if (this == &from) {
        return *this;
    }

    if (from.size() == 0) {
        return *this;
    }

    if (this->size() != from.size()) {
        this->size_ = from.size();
        if (this->mem_ != nullptr) {
            delete this->mem_;
        }
        this->mem_ = new u_char[this->size()];
    }
    for (size_t i = 0; i < this->size(); i++) {
        this->mem_[i] = from.mem_[i];
    }
    return *this;
}

void dynamic_mem_c::d_new(const uint size) {
    if (this->mem_) {
        delete this->mem_;
        this->mem_ = nullptr;
    }
    this->mem_ = new unsigned char[size];
    memset(this->mem_, 0, size);
    this->size_ = size;
}

void dynamic_mem_c::d_free() {
    if (this->mem_) {
        delete this->mem_;
        this->mem_ = nullptr;
    }
    this->size_ = 0;
}

size_t dynamic_mem_c::size() const { return this->size_; }

void dynamic_mem_c::copy(string &dest, const uint size) const {
    if (this->mem_) {
        for (uint i = 0; i < size; i++) {
            dest.push_back(this->mem_[i]);
        }
    }
}

void dynamic_mem_c::reset() {
    if (this->mem_) {
        memset(this->mem_, 0, this->size());
    }
}

bool dynamic_mem_c::empty() const {
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
