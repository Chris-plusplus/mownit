#include <interpolation/lagrange/general.hpp>

fn interpolation::_lagrange(const vecf& ys, const vecf& xs) {
	return [ys = ys, xs = xs](flt x) -> flt {
		flt sum = 0;
		size_t n = ys.size();

		auto l = [&](size_t k, flt x) -> flt {
			flt result = 1;

			for (size_t i = 0; i != n; ++i) {
				if (i != k) {
					result *= (x - xs[i]) / (xs[k] - xs[i]);
				}
			}

			return result;
		};

		for (size_t k = 0; k != n; ++k) {
			sum += ys[k] * l(k, x);
		}

		return sum;
	};
}
fn interpolation::lagrange(fn f, nodegen node_fn, size_t n, flt a, flt b) {
	auto xs = node_fn(n, a, b);

	auto ys = vecf(n);
	for (size_t j = 0; j != n; ++j) {
		ys[j] = f(xs[j]);
	}

	return _lagrange(ys, xs);
}