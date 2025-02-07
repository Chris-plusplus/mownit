#pragma once

#include <thread>
#include "row_operations.hpp"
#include "eye.hpp"

namespace matrix {

template<class T>
mat<T> gauss_inv(mat<T> A) noexcept {
	auto n = A.size();
	auto B = eye<T>(n);

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

	std::thread([A = std::move(A)]() noexcept {}).detach();

	return std::move(B);
}

}