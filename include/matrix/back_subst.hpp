#pragma once

#include <tuple>

namespace matrix {

template<class T>
std::tuple<vec<T>, mat<T>, vec<T>> back_subst(mat<T> A, vec<T> B) noexcept {
	std::size_t n = B.size();
	auto result = vec<T>(n);

	// subtracts rows upwards, starting from last row
	for (std::size_t row = n - 1; row != (std::size_t)-1; --row) {
		result[row] = B[row];
		for (std::size_t row2 = row + 1; row2 != n; ++row2) {
			result[row] -= B[row2] * A[row][row2];
		}
		result[row] /= A[row][row];

		B[row] = result[row];
	}

	return {std::move(result), std::move(A), std::move(B)};
}

}