#include "array.hpp" 
#include <cstring>


Array::Array(int size):
    size_(size)
{
    for (int i = 0; i < size; ++i)    
        data_[i] = 0.0;
}

Array::Array(int size, double value):
    size_(size)
{
    for (int i = 0; i < size; ++i)    
        data_[i] = value;
}

Array::~Array()
{
   if (data_ != nullptr)
       delete[] data_;
}

// copy constructor
Array::Array(const Array& other):
    size_(other.size_),
    data_(new double[other.size_])
{
   for (int i = 0; i < size_; ++i) 
       data_[i] = other.data_[i];
}


Array& Array::operator=(const Array &arr)
{
    if (this == &arr)
        return *this;

    data_ = new double[arr.size_];
    size_ = arr.size_;
    std::memcpy(data_, arr.data_, sizeof(double) * size_);
    return *this;
}

Array& Array::operator= (Array&& other)
{
    data_ = other.data_;
    size_ = other.size_;
    other.data_ = nullptr;
    other.size_ = 0;
    return *this;
}

Array& Array::operator+(const Array &other)
{
    // TODO: assert sizes are equal
    for (int i = 0; i < size_; ++i)
        data_[i] += other.data_[i];
    return *this;
}

Array& Array::operator+(Array&& other)
{
    // TODO: assert sizes are equal
    for (int i = 0; i < size_; ++i)
        data_[i] += other.data_[i];
    return *this;
}


Array& Array::operator-(const Array &other)
{
    // TODO: assert sizes are equal
    for (int i = 0; i < size_; ++i)
        data_[i] -= other.data_[i];
    return *this;
}

Array& Array::operator-(Array&& other)
{
    // TODO: assert sizes are equal
    for (int i = 0; i < size_; ++i)
        data_[i] -= other.data_[i];
    return *this;
}

Array& Array::operator*=(double k)
{
    for (int i = 0; i < size_; i++)
        data_[i] = data_[i] * k;
    return *this;
}

// scalar multiplication operator
Array operator*(double k, Array& array){
    return array *= k;
}

Array& Array::operator++()
{
    for (int i = 0; i < size_; i++)
        data_[i]++;
    return *this;
}

Array Array::operator++(int junk)
{
    Array ret(*this);
    ++(*this);
    return ret;
}

Array& Array::operator--()
{
    for (int i = 0; i < size_; i++)
        data_[i]--;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Array& obj)
{
    for (int i = 0; i < obj.size_ - 1; i++)
        os << obj.data_[i] << ", ";
    os << obj.data_[obj.size_ - 1];
    return os;
}
