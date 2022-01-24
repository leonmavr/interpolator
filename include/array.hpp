#ifndef ARRAY_HPP
#define ARRAY_HPP 

/*
 * Based on Wenox's Array class.
 * Some methods and operators were added.
 * https://gist.github.com/Wenox/c59f8215cda5c1fe66039471db6db416
 */
#include <iostream>
#include <memory> // std::unique_ptr, std::make_unique

class Array
{
    public:
        // constructors/destructor
        Array (int size);
        Array (int size, double value);
        Array (const Array& other);
        Array (Array&& other);
        ~Array ();

        // assignment operator
        Array& operator= (const Array& other);
        // move operator
        Array& operator= (Array&& other);
        // increment/decrement operators
        Array& operator++();
        Array operator++(int junk);
        Array& operator--();
        Array& operator--(int junk);
        // maths operators
        Array& operator *=(double k);
        Array& operator +(const Array& other);
        Array& operator +(Array&& other);
        Array& operator -(const Array& other);
        Array& operator -(Array&& other);
        // subscript operator
        double& operator[] (int index) { return data_[index]; }; 
        // stream operator for printing - has full access to the class
        friend std::ostream& operator<<(std::ostream& os, const Array& obj);
        // methods
        size_t size() const { return size_; }
        inline bool empty() { return size_ == 0; }

    private:
        std::size_t size_;
        //std::unique_ptr<double[]> data_;
        double* data_ = new double[size_];
        //std::unique_ptr<double[]> data_;
};
#endif /* ARRAY_HPP */
