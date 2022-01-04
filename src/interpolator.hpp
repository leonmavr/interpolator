#ifndef INTERPOLATOR_HPP
#define INTERPOLATOR_HPP 

#include "pointlist.hpp"
#include <string>
#include <map>


class Interpolator: public Pointlist
{
    public:
        Interpolator(): type_("linear") { }
        Interpolator(std::string type): type_(type) { }
        ~Interpolator();
        double interpolate(double x);
    private:
        std::map<std::string, double (Interpolator::*)()> map_str2fun_;
        inline double linear(double t) { return t; }
        const std::string type_; // interpolation type, e.g. linear

};

#endif /* INTERPOLATOR_HPP */
