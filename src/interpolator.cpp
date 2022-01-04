#include "interpolator.hpp"
#include <map>
#include <string>
#include <functional> // function


static double inline linear(double t) { return t; }
static double inline smoothstep(double t) { 
    // https://en.wikipedia.org/wiki/Smoothstep
    return std::min(std::max(0.0, 3*t*t - 2*t*t*t), 1.0);
}

std::map<std::string, std::function<double(double)>>  funcMap =
    {
        { "linear", linear},
        { "smoothstep", smoothstep}
    };

static inline double lerp(const Point& pl, const Point& pr, double t) {
    // linear interpolation
    return (1-t)*pl.second + t*pr.second;
}


Interpolator::~Interpolator() {
    free();
}

double Interpolator::interpolate(double x) {
    // interpolate this given the values left (->prev) and right (->next)
    // this node has no data - only ->prev, ->next do (see query den'n)
    auto node_to_interp = query(x);
    auto pleft = node_to_interp->prev->xy;
    auto pright = node_to_interp->next->xy;
    auto xleft = pleft.first;
    auto xright = pright.first;
    // t for linear interpolation, e.g. linear; pl + t(pr - pl)
    auto t = (x - xleft) / (xright - xleft);
    if (type_.compare("linear") != 0)
        t = funcMap[type_](t);
    int len = length();

    if (len == 1) [[unlikely]]
        return x;
    else if (t < 0.0) [[unlikely]]
        return pleft.second;
    else if (t > 1.0) [[unlikely]]
        return pright.second;
    else [[likely]]
        return lerp(pleft, pright, t);
}
