#pragma once

#include <tuple>
#include "row_operations.hpp"

namespace matrix {

// aby wykonać obliczenia 'w miejscu' należy przekazać macierz i wektor wyrazów wolnych poprzez std::move
template<class T>
std::tuple<mat<T>, vec<T>> gauss_elim(mat<T> A, vec<T> B) noexcept {
	std::size_t n = B.size();

	for (std::size_t row = 0; row != n; ++row) {
		for (std::size_t max_row = n - 1; max_row != row; --max_row) {
			if (fabs(A[max_row - 1][row]) < fabs(A[max_row][row])) {
				swap_rows(A, B, max_row - 1, max_row);
			}
		}

		divide_rows(A, B, row, A[row][row]);

		for (size_t to_subtract_from = row + 1; to_subtract_from != n; ++to_subtract_from) {
			T scalar = A[to_subtract_from][row] / A[row][row];

			subtract_rows(A, B, to_subtract_from, row, scalar);
		}
	}

	return {std::move(A), std::move(B)};
}

}