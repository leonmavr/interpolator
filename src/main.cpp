#include <iostream>
#include <memory>
#include "pointlist.hpp"
#include "interpolator.hpp"


int main()
{
    auto pl = std::make_unique<Pointlist>();
    auto lerp = std::make_unique<Interpolator>("smoothstep");
    lerp->insert(100, 10);
    lerp->insert(42, 4.2);
#if 1
    lerp->insert(69, 6.9);
    lerp->insert(1000, 100);
    lerp->insert(10000, 1001);
#endif
    std::cout << lerp->interpolate(40) << std::endl;
    std::cout << lerp->interpolate(76) << std::endl;
    std::cout << lerp->interpolate(-100000) << std::endl;
    std::cout << lerp->interpolate(100000) << std::endl;

}
