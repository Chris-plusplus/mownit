#pragma once

#include <thread>

namespace matrix {

template<class T>
T condition(const mat<T>& A) noexcept {
	auto A_inv = gauss_inv(A);

	T norm_A = 0;
	T norm_A_inv = 0;

	for (size_t i = 0; i != A.size(); ++i) {
		T sum_A = 0;
		T sum_A_inv = 0;
		for (size_t j = 0; j != A.size(); ++j) {
			sum_A += std::fabs(A[i][j]);
			sum_A_inv += std::fabs(A_inv[i][j]);
		}
		norm_A = std::max(norm_A, sum_A);
		norm_A_inv = std::max(norm_A_inv, sum_A_inv);
	}

	std::thread([A_inv = std::move(A_inv)]() noexcept {}).detach();

	return norm_A_inv * norm_A;
}

}