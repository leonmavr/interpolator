#ifndef INTERPOLATOR_HPP
#define INTERPOLATOR_HPP 

#include "pointlist.hpp"
#include <string>
#include <map>
#include <functional> // std::function


class Interpolator: public Pointlist
{
    public:
        Interpolator(): type_("linear") { }
        Interpolator(std::string type): type_(type) { }
        ~Interpolator();
        double interpolate(double x);
        void help() const;
    private:
        const std::string type_; // interpolation type, e.g. linear
        // function dispatch table
        // https://en.wikipedia.org/wiki/Smoothstep
        std::map< std::string, std::function<double(double)> > interp_functions_ {
            {"linear",      [](double x){ return x; }},
                {"smoothstep",  [](double x){
                                                return std::min(std::max(0.0, 3*x*x - 2*x*x*x), 1.0);}}
        };
        inline double interp_points_(const Point& pl,
            const Point& pr,
            std::function<double(double)> func,
            double t) {
                // general interpolation formula
                return (1-func(t))*pl.second + func(t)*pr.second;
        }



};

#endif /* INTERPOLATOR_HPP */
