#include <interpolation/newton/uniform.hpp>
#include <interpolation/newton/deltas.hpp>
#include <interpolation/newton/binomcoeffs.hpp>
#include <nodes/uniform.hpp>

fn interpolation::_newton_uniform(const vecf& ys, const vecf& xs) {
	return [
		xs = xs,
		ys = ys,
		h = xs[1] - xs[0],
		deltas = compute_deltas_newton(ys)
	](flt x) -> flt {
		size_t n = ys.size();

		flt s = (x - xs[0]) / h;

		flt sum = 0;
		for (size_t k = 0; k != n; ++k) {
			sum += binomcoeffs_newton(s, k, deltas[k]);
		}

		return sum;
	};
}
fn interpolation::newton_uniform(fn f, size_t n, flt a, flt b) {
	auto xs = nodes::uniform(n, a, b);

	auto ys = std::vector<flt>(n);
	for (size_t j = 0; j != n; ++j) {
		ys[j] = f(xs[j]);
	}

	return _newton_uniform(ys, xs);
}