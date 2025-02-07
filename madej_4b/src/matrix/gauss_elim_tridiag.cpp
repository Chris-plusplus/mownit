#include <matrix/gauss_elim_tridiag.hpp>
#include <matrix/row_operations.hpp>
#include <algorithm>
#include <cmath>
#include <limits>

namespace matrix {

std::tuple<matf, vecf> gauss_elim_tridiag(matf A, vecf B) {
	std::size_t n = B.size();

	for (std::size_t row = 0; row != n; ++row) {
		// odejmuję tylko kolejny wiersz, macierz jest trójdiagonalna
		if (std::size_t to_subtract_from = row + 1; to_subtract_from != n) {
			double scalar = A[to_subtract_from][row] / A[row][row];

			subtract_rows(A, B, to_subtract_from, row, scalar);
		}
	}

	return {std::move(A), std::move(B)};
}
	
}