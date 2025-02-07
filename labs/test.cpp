#include <iostream>
#include <format>
#include <CvPlot/cvplot.h>
#include <approximation.hpp>
#include <cmath>
#include <numbers>
#include <nodes.hpp>
#include <ranges>
#include <algorithm>
#include <future>
#include <Legend.hpp>
#include <roots.hpp>
#include <armadillo>

int main() {
	auto A = arma::mat{
		{1, 1},
		{1, 2}
	};
	std::cout << A << '\n';
	size_t n = A.n_rows;
	auto diag = A.diag();
	auto A_wout_diag = A - arma::diagmat(diag);
	auto b = arma::vec{
		1,
		-1
	};
	auto x_curr = b;
	auto x_next = decltype(x_curr)();

	std::cout << (b - (A_wout_diag * x_curr)) << "\n\n";

	x_next = (b - (A_wout_diag * x_curr)) / diag;
	x_curr = x_next;
	std::cout << diag << "\n\n";
	auto xd = arma::vec({-1, -1, -2, -5, -4});

	std::cout << arma::abs(xd) << "\n\n";
	std::cout << arma::abs(xd).max() << "\n\n";
}