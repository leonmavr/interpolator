#include <iostream>
#include <memory>
#include "pointlist.hpp"
#include "interpolator.hpp"


int main()
{
    auto lerp = std::make_unique<Interpolator>("smoothstep");
    lerp->insert(100, 10);
    lerp->insert(42, 4.2);
#if 1
    lerp->insert(69, 6.9);
    lerp->insert(1000, 100);
    lerp->insert(420, 42.0);
    lerp->insert(10001, 1002);
    lerp->insert(10000, 1001);
#endif
    std::cout << lerp->interpolate(40) << std::endl;
    std::cout << lerp->interpolate(76) << std::endl;
    std::cout << lerp->interpolate(-100000) << std::endl;
    std::cout << lerp->interpolate(100000) << std::endl;
    //std::cout << lerp->begin()->next->xy.first;
    std::cout << "\n----" << std::endl;
    for (const auto& it: *lerp)
        std::cout << it.xy.first << ", ";
    std::cout << "\n----" << std::endl;

    auto pl = std::make_unique<Pointlist>();
    pl->insert(5, 0);
    pl->insert(3, 0);
    pl->insert(10, 0);
    pl->insert(0, 0);
    for (const auto& it: *pl)
        std::cout << it.xy.first << ", ";


}
