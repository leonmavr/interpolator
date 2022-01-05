#include "interpolator.hpp"
#include <map>
#include <string>
#include <functional> // std::function
#include <stdexcept>


//----------------------------------------------------------------
// static functions
static inline double Smoothstep(double t) { 
    // https://en.wikipedia.org/wiki/Smoothstep
    return std::min(std::max(0.0, 3*t*t - 2*t*t*t), 1.0);
}

static inline double Linear(double t) {
    return t;
}

static inline double InterpPoints(const Point& pl,
        const Point& pr,
        std::function<double(double)> func,
        double t) {
    // general interpolation formula
    return (1-func(t))*pl.second + func(t)*pr.second;
}


//----------------------------------------------------------------
// class methods 
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
    int len = length();

    Point xy_first; 
    Point xy_last; 
    if (len > 1) {
        xy_first = head_->prev->xy;
        xy_last = tail_->next->xy;
    }
    if (len == 1) [[unlikely]]
        return x;
    else if (x > xy_first.first) [[unlikely]] // .first: x, .second: y
        return xy_first.second;
    else if (x < xy_last.first) [[unlikely]] // .first: x, .second: y
        return xy_last.second;
    else [[likely]] {
        if (type_.compare("linear") == 0)
            return InterpPoints(pleft, pright, &Linear, t);
        else if (type_.compare("smoothstep") == 0)
            return InterpPoints(pleft, pright, &Smoothstep, t);
        else {
            throw std::invalid_argument(
                    "Invalid interpolation type. Use linear or smoothstep");
        }
    }        

}
