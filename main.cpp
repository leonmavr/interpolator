#include <iostream>
#include <fstream>
#include <memory> // make_unique
#include <utility> // make_pair
#include "pointlist.hpp"
#include "interpolator.hpp"


int main() {
	// write results to file to visualise them later
	// it shall contain:
	// anchor points as (x, y), newline, interpolated points (x, y)
	std::ofstream file_out;
	file_out.open("out.txt");

    auto interp = std::make_unique<Interpolator>("linear");
	std::vector<std::pair<double, double>> anchors;
	anchors.push_back(std::make_pair(12.0, 8.0));
	anchors.push_back(std::make_pair(-1.0, -5.0));
	anchors.push_back(std::make_pair(1.0, -2.5));
	anchors.push_back(std::make_pair(18.0, 1.0));
	anchors.push_back(std::make_pair(10, 5.0));
	anchors.push_back(std::make_pair(20.0, 0.75));
	anchors.push_back(std::make_pair(5.5, 4.0));

	for (const auto& a: anchors) {
		interp->insert(a.first, a.second);
		file_out << a.first << ", " << a.second << std::endl;
	}
	file_out << std::endl;
	
	double dx = 0.01;
	for (double x = -3.0; x < 22.0; x += dx)
		file_out << x << ", " << interp->interpolate(x) << std::endl;

	file_out.close();
}
