#include "interpolator.hpp"
#include <map>
#include <string>
#include <functional> // std::function


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
    else [[likely]]
        return interp_points_(pleft, pright, interp_functions_[type_], t);
}


void Interpolator::help() const{
    std::cout << "The interpolation functions supported are:" << std::endl;;
    for (const auto& kv: interp_functions_) 
        std::cout << "\t * " << kv.first << std::endl;
}
