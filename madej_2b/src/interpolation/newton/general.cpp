#include <interpolation/newton/general.hpp>
#include <interpolation/newton/divdiffs.hpp>
#include <interpolation/newton/uniform.hpp>
#include <nodes/uniform.hpp>

fn interpolation::_newton(const vecf& ys, const vecf& xs) {
	return [ys = ys, xs = xs, divdiff = divdiffs_newton(ys, xs)](flt x) -> flt {
		size_t n = ys.size();

		auto x_diffs = std::vector<flt>(n);
		x_diffs[0] = 1;
		for (size_t i = 0; i != n - 1; ++i) {
			x_diffs[i + 1] = x - xs[i];
		}

		flt sum = 0;
		flt x_coeff = 1;
		for (size_t i = 0; i != n; ++i) {
			x_coeff *= x_diffs[i];
			sum += divdiff[i] * x_coeff;
		}

		return sum;
	};
}
fn interpolation::newton(fn f, nodegen node_fn, size_t n, flt a, flt b) {
	if (*node_fn.target<decltype(&nodes::uniform)>() == nodes::uniform) { // typ węzłów to równomierny
		return interpolation::newton_uniform(f, n, a, b);
	}

	auto xs = node_fn(n, a, b);

	auto ys = vecf(n);
	for (size_t j = 0; j != n; ++j) {
		ys[j] = f(xs[j]);
	}

	return _newton(ys, xs);
}