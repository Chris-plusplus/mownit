#include <approximation/least_square.hpp>
#include <matrix/solve.hpp>
#include <iostream>
#include <iomanip>

fn approx::_least_square(const vecf& ys, const vecf& xs, size_t m, const vecf& ws) {
	size_t n = ys.size();

	auto G = matf(m + 1, vecf(m + 1, nan("")));
	auto B = vecf(m + 1, nan(""));

	for (size_t j = 0; j != m + 1; ++j) {
		if (j != m) {
			flt val1 = 0;
			flt val2 = 0;
			for (size_t i = 0; i != n; ++i) {
				val1 += ws[i] * pow(xs[i], j);
				val2 += ws[i] * pow(xs[i], 2.0 * m - j);
			}
			for (size_t i = 0; i != j + 1; ++i) {
				G[i][j - i] = val1;
				G[m - i][m - j + i] = val2;
			}
		}
		else{
			flt val = 0;
			for (size_t i = 0; i != n; ++i) {
				val += ws[i] * pow(xs[i], j);
			}
			for (size_t i = 0; i != j + 1; ++i) {
				G[i][j - i] = val;
			}
		}

		B[j] = 0;
		for (size_t i = 0; i != n; ++i) {
			B[j] += ws[i] * ys[i] * pow(xs[i], j);
		}
	}

	auto&& [as, _G, _B] = matrix::solve(std::move(G), std::move(B));

	return [as = std::move(as)](flt x) -> flt {
		flt result = 0;
		for (size_t i = 0; i != as.size(); ++i) {
			result += as[i] * pow(x, i);
		}

		return result;
	};
}
fn approx::least_square(fn f, nodegen node_fn, size_t n, size_t m, const vecf& ws, flt a, flt b) {
	auto xs = node_fn(n, a, b);

	auto ys = vecf(n);
	for (size_t j = 0; j != n; ++j) {
		ys[j] = f(xs[j]);
	}

	return _least_square(ys, xs, m, ws);
}