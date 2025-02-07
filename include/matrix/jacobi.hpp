#pragma once

#include <tuple>
#include <armadillo>

namespace matrix {

enum class stop_criterion {
	step,
	value
};

std::tuple<decltype(clk::now() - clk::now()), arma::vec, size_t> jacobi(const arma::mat& A, const arma::vec& b, const arma::vec& start, stop_criterion sc, f64 rho, size_t max_iters = 10000) noexcept {
	auto clk_start = clk::now();

	size_t n = A.n_rows;
	auto diag = A.diag();
	auto A_wout_diag = A - arma::diagmat(diag);

	auto x_curr = b;
	auto x_next = decltype(x_curr)();

	size_t i = 0;
	for (; i != max_iters; ++i) {
		x_next = (b - (A_wout_diag * x_curr)) / diag;
		if (sc == stop_criterion::step and arma::norm(x_next - x_curr) < rho) {
			return {clk::now() - clk_start, std::move(x_next), i + 1};
		}
		else if (sc == stop_criterion::value and arma::norm(A * x_next - b) < rho) {
			return {clk::now() - clk_start, std::move(x_next), i + 1};
		}
		x_curr = x_next;
	}

	return {clk::now() - clk_start, std::move(x_curr), (size_t)-1};
}

}