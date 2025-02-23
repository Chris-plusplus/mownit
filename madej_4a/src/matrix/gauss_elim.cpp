#include <matrix/gauss_elim.hpp>
#include <matrix/row_operations.hpp>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>

namespace matrix {

std::tuple<matf, vecf> gauss_elim(matf A, vecf B) {
	std::size_t n = B.size();

	for (std::size_t row = 0; row != n; ++row) {
		for (std::size_t max_row = n - 1; max_row != row; --max_row) {
			if (fabs(A[max_row - 1][row]) < fabs(A[max_row][row])) {
				swap_rows(A, B, max_row - 1, max_row);
			}
		}

		divide_rows(A, B, row, A[row][row]);

		for (size_t to_subtract_from = row + 1; to_subtract_from != n; ++to_subtract_from) {
			double scalar = A[to_subtract_from][row] / A[row][row];

			subtract_rows(A, B, to_subtract_from, row, scalar);
		}
	}

	return {std::move(A), std::move(B)};
}

}