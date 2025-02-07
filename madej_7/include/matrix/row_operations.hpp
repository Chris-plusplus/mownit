#pragma once

namespace matrix {

template<class T>
void add_rows(mat<T>& A, vec<T>& B, size_t to_add_to, std::size_t added, T scalar) noexcept {
	for (std::size_t i = 0; i != B.size(); ++i) {
		A[to_add_to][i] += scalar * A[added][i];
	}
	B[to_add_to] += scalar * B[added];
}
template<class T>
void subtract_rows(mat<T>& A, vec<T>& B, std::size_t to_subtracted_from, std::size_t subtracted, T scalar, size_t from = 0, size_t to = (size_t)-1) noexcept {
	size_t max = std::min(B.size(), to);
	for (std::size_t i = from; i != max; ++i) {
		A[to_subtracted_from][i] -= scalar * A[subtracted][i];
	}
	B[to_subtracted_from] -= scalar * B[subtracted];
}
template<class T>
void multiply_rows(mat<T>& L, vec<T>& P, size_t row, T scalar) noexcept {
	for (auto&& x : L[row]) {
		x *= scalar;
	}
	P[row] *= scalar;
}
template<class T>
void divide_rows(mat<T>& L, vec<T>& P, size_t row, T scalar) noexcept {
	for (auto&& x : L[row]) {
		x /= scalar;
	}
	P[row] /= scalar;
}
template<class T>
void swap_rows(mat<T>& L, vec<T>& P, size_t row1, size_t row2) noexcept {
	std::swap(L[row1], L[row2]);
	std::swap(P[row1], P[row2]);
}

template<class T>
void add_rows(mat<T>& A, mat<T>& B, size_t to_add_to, std::size_t added, T scalar) noexcept {
	for (std::size_t i = 0; i != B.size(); ++i) {
		A[to_add_to][i] += scalar * A[added][i];
		B[to_add_to][i] += scalar * B[added][i];
	}
}
template<class T>
void subtract_rows(mat<T>& A, mat<T>& B, std::size_t to_subtracted_from, std::size_t subtracted, T scalar, size_t from = 0, size_t to = (size_t)-1) noexcept {
	size_t max = std::min(B.size(), to);
	for (std::size_t i = from; i != max; ++i) {
		A[to_subtracted_from][i] -= scalar * A[subtracted][i];
		B[to_subtracted_from][i] -= scalar * B[subtracted][i];
	}
}
template<class T>
void multiply_rows(mat<T>& A, mat<T>& B, size_t row, T scalar) noexcept {
	for (size_t i = 0; i != A.size(); ++i) {
		A[row][i] *= scalar;
		B[row][i] *= scalar;
	}
}
template<class T>
void divide_rows(mat<T>& A, mat<T>& B, size_t row, T scalar) noexcept {
	for (size_t i = 0; i != A.size(); ++i) {
		A[row][i] /= scalar;
		B[row][i] /= scalar;
	}
}
template<class T>
void swap_rows(mat<T>& A, mat<T>& B, size_t row1, size_t row2) noexcept {
	std::swap(A[row1], A[row2]);
	std::swap(B[row1], B[row2]);
}

}