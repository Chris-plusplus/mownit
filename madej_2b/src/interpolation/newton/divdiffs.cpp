#include <interpolation/newton/divdiffs.hpp>

vecf interpolation::divdiffs_newton(const vecf& ys, const vecf& xs) {
	size_t n = ys.size();
	auto result = vec2f(n, vecf(n));

	for (size_t i = 0; i != n; ++i) {
		result[i][i] = ys[i];
	}

	for (size_t k = 1; k != n; ++k) {
		for (size_t i = 0; i + k != n; ++i) {
			result[i][i + k] = (result[i + 1][i + k] - result[i][i + k - 1]) / (xs[i + k] - xs[i]);
		}
	}

	return result[0];
}