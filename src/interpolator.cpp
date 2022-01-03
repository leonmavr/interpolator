#include "interpolator.hpp"


static inline double lerp(const Point& pl, const Point& pr, double t) {
    // linear interpolation
    return pl.second + t*(pr.second - pl.second);
    return (1-t)*pl.second + t*pr.second;
}


Interpolator::~Interpolator() {
    free();
    delete head_;
    delete tail_;
}

double Interpolator::interpolate(double x) {
    // interpolate this given the values left (->prev) and right (->next)
    // this node has no data - only ->prev, ->next do (see query den'n)
    auto node_to_interp = query(x);
    auto pleft = node_to_interp->prev->xy;
    auto pright = node_to_interp->next->xy;
    auto xleft = pleft.first;
    auto xright = pright.first;
    // t for linear interpolation formula; pl + t(pr - pl)
    auto t = (x - xleft) / (xright - xleft);
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


