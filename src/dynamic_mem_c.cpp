#include "dynamic_mem_c.hpp"

dynamic_mem_c::dynamic_mem_c()
{
    this->size = 0;
    this->mem = nullptr;
}

dynamic_mem_c::~dynamic_mem_c()
{
    if (this->mem)
    {
        delete this->mem;
    }
}

using namespace std;

void dynamic_mem_c::d_new(uint size)
{
    this->mem = new unsigned char[size];
    this->size = size;
}

void dynamic_mem_c::d_free()
{
    if (this->mem)
    {
        delete this->mem;
        this->mem = nullptr;
    }
    this->size = 0;
}

int dynamic_mem_c::get_size() const
{
    return this->size;
}

void dynamic_mem_c::copy(string & dest, const uint size) const{
    if(this->mem){
        for (int i = 0; i < size; i++){
            dest.push_back(this->mem[i]);
        }
    }
}
