#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/interpolator.hpp"
#include "../src/pointlist.hpp"

#include <fstream>
#include <string>
#include <algorithm>
#include <vector>


static constexpr double eps = 0.0001; // tolerance for floating comparison

static inline bool near_zero(double a, double b, double eps) {
    return std::fabs(a-b) < eps;
}

TEST_CASE("Linear interpolator cases") {
	auto interpolator = std::make_unique<Interpolator>();
        interpolator->insert(-1, -1);
        interpolator->insert(1, 1);
        interpolator->insert(2, 1.5);
        interpolator->insert(3, 1.5);
	SECTION("Average cases", "[test1]") {
                REQUIRE(near_zero(interpolator->interpolate(0.0), 0.0, eps));
                REQUIRE(near_zero(interpolator->interpolate(-0.99), -0.99, eps));
                REQUIRE(near_zero(interpolator->interpolate(1.25), 1.125, eps));
	}
	SECTION("Corner cases", "[test2]") {
                REQUIRE(near_zero(interpolator->interpolate(-1.01), -1, eps));
                REQUIRE(near_zero(interpolator->interpolate(-1.2), -1, eps));
                REQUIRE(near_zero(interpolator->interpolate(3000), 1.5, eps));
	}
}
