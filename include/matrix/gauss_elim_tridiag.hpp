#pragma once

#include <tuple>
#include "row_operations.hpp"

namespace matrix {

// aby wykonać obliczenia 'w miejscu' należy przekazać macierz i wektor wyrazów wolnych poprzez std::move
template<class T>
std::tuple<mat<T>, vec<T>> gauss_elim_tridiag(mat<T> A, vec<T> B) noexcept {
	std::size_t n = B.size();

	for (std::size_t row = 0; row != n; ++row) {
		// odejmuję tylko kolejny wiersz, macierz jest trójdiagonalna
		if (std::size_t to_subtract_from = row + 1; to_subtract_from != n) {
			T scalar = A[to_subtract_from][row] / A[row][row];

			subtract_rows(A, B, to_subtract_from, row, scalar, row, row + 2);
		}
	}

	return {std::move(A), std::move(B)};
}

}