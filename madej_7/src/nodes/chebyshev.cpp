#include <nodes/chebyshev.hpp>
#include <cmath>
#include <numbers>
#include <algorithm>
#include <ranges>

std::vector<flt> nodes::chebyshev(size_t n, flt a, flt b) {
	auto nodes = std::vector<flt>(n);

	for (size_t k = 0; k != n; ++k) {
		nodes[k] = 0.5 * (a + b) + 0.5 * (b - a) * std::cos(std::numbers::pi_v<flt> *(2 * k + 1.0) / (2.0 * (flt)n));
	}

	std::ranges::sort(nodes);

	return nodes;
}