#pragma once

#include <nodes/uniform.hpp>

std::vector<flt> nodes::uniform(size_t n, flt a, flt b) {
	auto nodes = std::vector<flt>(n);

	for (size_t i = 0; i != n; ++i) {
		nodes[i] = a + (flt)(i) * (b - a) / (n - 1);
	}

	return nodes;
}