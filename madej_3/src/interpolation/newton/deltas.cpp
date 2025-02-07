#include <interpolation/newton/deltas.hpp>

vecf interpolation::compute_deltas_newton(const vecf& ys) {
	size_t n = ys.size();
	auto result = vec2f(n, vecf(n));
	for (size_t i = 0; i != n; ++i) {
		result[i][0] = ys[i];
	}

	for (size_t k = 1; k != n; ++k) {
		for (size_t i = 0; i != n - k; ++i) {
			result[i][k] = result[i + 1][k - 1] - result[i][k - 1];
		}
	}

	return result[0];
}