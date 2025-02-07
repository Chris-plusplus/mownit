#pragma once

namespace matrix {

template<class T>
vec<T> mul_by_vec(const mat<T>& A, const vec<T>& x) noexcept {
	size_t n = A.size();
	auto result = vec<T>(n, 0);

	for (size_t i = 0; i != n; ++i) {
		for (size_t j = 0; j != n; ++j) {
			result[i] += A[i][j] * x[j];
		}
	}

	return std::move(result);
};

}