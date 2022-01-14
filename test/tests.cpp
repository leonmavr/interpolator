#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/interpolator.hpp"
#include "../src/pointlist.hpp"

#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility> // pair


static constexpr double eps = 0.0001; // tolerance for floating comparison

static inline bool near_zero(double a, double b, double eps) {
    return std::fabs(a-b) < eps;
}


TEST_CASE("Pointlist cases") {
	auto pointlist = std::make_unique<Pointlist>();
	pointlist->insert(-1.0, 5.0);
	pointlist->insert(42.0, -5.0);
	pointlist->insert(50.1, 9.0);
	pointlist->insert(34.0, 7.0);
	pointlist->insert(-100.0, 50.0);

    SECTION("Iteration test", "[test1]") {
		int len = 0;
		for (const auto& it: *pointlist)
			len++;
		REQUIRE(len == 5);
	}

    SECTION("x's sorted", "[test2]") {
        std::vector<double> pts_x;
		for (const auto& it: *pointlist)
			pts_x.push_back(it.xy.first);
        REQUIRE(std::is_sorted(pts_x.begin(), pts_x.end()));
    }
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
            REQUIRE(near_zero(interpolator->interpolate(-1.01), -1.0, eps));
            REQUIRE(near_zero(interpolator->interpolate(-1.2), -1.0, eps));
            REQUIRE(near_zero(interpolator->interpolate(3000), 1.5, eps));
    }
}
