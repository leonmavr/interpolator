#ifndef INTERPOLATOR_HPP
#define INTERPOLATOR_HPP 

#include "pointlist.hpp"


class Interpolator: public Pointlist
{
    public:
        Interpolator() { }
        ~Interpolator();
        double interpolate(double x);
};

#endif /* INTERPOLATOR_HPP */
