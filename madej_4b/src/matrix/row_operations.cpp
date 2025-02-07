#include <matrix/row_operations.hpp>

namespace matrix {

void add_rows(matf& A, vecf& B, size_t to_add_to, std::size_t added, double scalar) {
	for (std::size_t i = 0; i != B.size(); ++i) {
		A[to_add_to][i] += scalar * A[added][i];
	}
	B[to_add_to] += scalar * B[added];
}
void subtract_rows(matf& A, vecf& B, std::size_t to_subtracted_from, std::size_t subtracted, double scalar) {
	add_rows(A, B, to_subtracted_from, subtracted, -scalar);
}
void multiply_rows(matf& L, vecf& P, size_t row, double scalar) {
	for (auto&& x : L[row]) {
		x *= scalar;
	}
	P[row] *= scalar;
}
void divide_rows(matf& L, vecf& P, size_t row, double scalar) {
	for (auto&& x : L[row]) {
		x /= scalar;
	}
	P[row] /= scalar;
}
void swap_rows(matf& L, vecf& P, size_t row1, size_t row2) {
	std::swap(L[row1], L[row2]);
	std::swap(P[row1], P[row2]);
}

}