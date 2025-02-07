#include <interpolation/spline/3/clamped.hpp>
#include <matrix/solve_tridiag.hpp>
#include <map>

namespace interpolation {

fn _clamped_3(const vecf& ys, const vecf& xs) {
	auto n = ys.size();

	auto h = [&xs](size_t i) -> flt {
		return xs[i + 1] - xs[i];
	};

	auto delta = [&h, &ys](size_t i) -> flt {
		return (ys[i + 1] - ys[i]) / h(i);
	};

	auto A = matf(n, vecf(n));
	auto B = vecf(n);

	// clamped boundary
	A[0][0] = (A[n - 1][n - 1] = 2);
	A[0][1] = (A[n - 1][n - 2] = 1);
	for (size_t i = 1; i != n - 1; ++i) {
		A[i][i - 1] = h(i - 1);
		A[i][i] = 2.0 * (h(i - 1) + h(i));
		A[i][i + 1] = h(i);

		B[i] = delta(i) - delta(i - 1);
	}

	auto&& [sigma, _A, _B] = matrix::solve_tridiag(std::move(A), std::move(B));
	A = std::move(_A);
	B = std::move(_B);

	auto fns = std::map<flt, fn>();

	for (size_t i = 0; i != n - 1; ++i) {
		flt d = (sigma[i + 1] - sigma[i]) / h(i);
		flt c = 3.0 * sigma[i];
		flt b = (ys[i + 1] - ys[i]) / h(i) - h(i) * (sigma[i + 1] + 2.0 * sigma[i]);

		fns[xs[i]] = [a_i = ys[i], b_i = b, c_i = c, d_i = d, x_i = xs[i]](flt x) -> flt {
			flt diff = x - x_i;

			return a_i + b_i * diff + c_i * pow(diff, 2.0) + d_i * pow(diff, 3.0);
		};
	}

	return [fns = std::move(fns)](flt x) -> flt {
		auto&& found_fn = fns.upper_bound(x);

		if (found_fn == fns.end()) {
			return fns.rbegin()->second(x);
		}
		else if (found_fn != fns.begin()) {
			return (--found_fn)->second(x);
		}
		else {
			return found_fn->second(x);
		}
	};
}
fn clamped_3(fn f, nodegen node_fn, size_t n, flt a, flt b) {
	auto xs = node_fn(n, a, b);

	auto ys = vecf(n);
	for (size_t j = 0; j != n; ++j) {
		ys[j] = f(xs[j]);
	}

	return _clamped_3(ys, xs);
}

}