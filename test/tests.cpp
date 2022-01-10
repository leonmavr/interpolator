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

    SECTION("x's sorted", "[test1]") {
        auto pointlist = std::make_unique<Pointlist>();
        std::vector<std::pair<double, double>> pts_input;
        pts_input.push_back(std::make_pair(-1.0, 5.0));
        pts_input.push_back(std::make_pair(42.0, 10.0));
        pts_input.push_back(std::make_pair(50.0, 9.0));
        pts_input.push_back(std::make_pair(43.0, 7.0));
        pts_input.push_back(std::make_pair(-100.0, -20.1));
        std::vector<std::pair<double, double>> pts_output;
        std::vector<double> pts_input_x;
        bool equal = true;
        // TODO: assert the points of Pointlist are sorted
        REQUIRE(equal);
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
            REQUIRE(near_zero(interpolator->interpolate(-1.01), -1, eps));
            REQUIRE(near_zero(interpolator->interpolate(-1.2), -1, eps));
            REQUIRE(near_zero(interpolator->interpolate(3000), 1.5, eps));
    }
}
