#include "../include/dynamic_mem_c.hpp"

dynamic_mem_c::dynamic_mem_c()
{
    this->size = 0;
    this->mem = nullptr;
}
dynamic_mem_c::dynamic_mem_c(const uint size)
{
    this->size = size;
    try
    {
        this->mem = new u_char[size];
    }
    catch (std::bad_alloc)
    {
        ERROR("");
    }
    memset(this->mem, 0, size);
}

dynamic_mem_c::~dynamic_mem_c()
{
    if (this->mem)
    {
        delete this->mem;
    }
}

dynamic_mem_c::dynamic_mem_c(const dynamic_mem_c &from)
{
    if (this == &from)
    {
        return;
    }
    this->size = from.size;
    if (from.size > 0)
    {
        this->mem = new u_char[this->size];
    }
    for (size_t i = 0; i < this->size; i++)
    {
        this->mem[i] = from.mem[i];
    }
    return;
}

using namespace std;

dynamic_mem_c &dynamic_mem_c::operator=(const dynamic_mem_c &from)
{
    if (this == &from)
    {
        return *this;
    }

    if (this->size != from.size)
    {
        this->size = from.size;
        if (this->mem != nullptr)
        {
            delete mem;
        }
        mem = new u_char[this->size];
    }
    for (size_t i = 0; i < this->size; i++)
    {
        this->mem[i] = from.mem[i];
    }
    return *this;
}

void dynamic_mem_c::d_new(const uint size)
{
    if (this->mem)
    {
        delete this->mem;
        this->mem = nullptr;
    }
    this->mem = new unsigned char[size];
    memset(this->mem, 0, size);
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

size_t dynamic_mem_c::get_size() const
{
    return this->size;
}

void dynamic_mem_c::copy(string &dest, const uint size) const
{
    if (this->mem)
    {
        for (uint i = 0; i < size; i++)
        {
            dest.push_back(this->mem[i]);
        }
    }
}

void dynamic_mem_c::reset()
{
    if (this->mem)
    {
        memset(this->mem, 0, this->get_size());
    }
}

bool dynamic_mem_c::is_empty() const
{
    if (this->get_size() == 0 || this->mem == nullptr)
    {
        ERROR("領域が確保されていません");
        return true;
    }
    bool isEmpty = true;
    for (size_t i = 0; i < this->get_size(); i++)
    {
        if (this->mem[i] != 0)
        {
            isEmpty = false;
            break;
        }
    }
    if (isEmpty == true)
    {
        return true;
    }
    return false;
}
