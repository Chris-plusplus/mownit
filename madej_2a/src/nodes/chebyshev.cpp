#include <nodes/chebyshev.hpp>
#include <cmath>
#include <numbers>

std::vector<flt> nodes::chebyshev(size_t n, flt a, flt b) {
	auto nodes = std::vector<flt>(n);

	for (size_t k = 0; k != n; ++k) {
		nodes[k] = (a + b) / 2.0 + (b - a) * std::cos(std::numbers::pi_v<flt> *((flt)(k + 1) / (flt)(n)) - 1.0 / (2.0 * (flt)(n))) / 2.0;
	}

	return nodes;
}