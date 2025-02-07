#include <interpolation/spline/2/natural_spline.hpp>
#include <map>
#include <iostream>

namespace interpolation {

fn _natural_spline_2(const vecf& ys, const vecf& xs) {
	auto n = ys.size();

	auto delta = [&ys, &xs](size_t i) -> flt {
		return (ys[i] - ys[i - 1]) / (xs[i] - xs[i - 1]);
	};

	auto bs = vecf(n);
	bs[0] = 0; // natural spline
	for (size_t i = 1; i != n; ++i) {
		bs[i] = 2.0 * delta(i) - bs[i - 1];
	}

	// mapa podfunkcji {<początek-zakresu>, <funkcja>}
	std::map<flt, fn> fns;
	for (size_t i = 0; i != n - 1; ++i) {
		flt c = (bs[i + 1] - bs[i]) / (2.0 * (xs[i + 1] - xs[i]));

		fns[xs[i]] = [a_i = ys[i], b_i = bs[i], c_i = c, x_i = xs[i]](flt x) -> flt {
			flt diff = x - x_i;

			return a_i + b_i * diff + c_i * pow(diff, 2.0);
		};
	}

	return [fns = std::move(fns)](flt x) -> flt {
		auto&& found_fn = fns.upper_bound(x);

		if (found_fn == fns.end()) {
			//std::cout << x << ' ' << fns.rbegin()->first << '\n';
			return fns.rbegin()->second(x);
		}
		else if (found_fn != fns.begin()) {
			--found_fn;
			//std::cout << x << ' ' << found_fn->first << '\n';
			return found_fn->second(x);
		}
		else {
			//std::cout << x << ' ' << found_fn->first << '\n';
			return found_fn->second(x);
		}
	};
}
fn natural_spline_2(fn f, nodegen node_fn, size_t n, flt a, flt b) {
	auto xs = node_fn(n, a, b);

	auto ys = vecf(n);
	for (size_t j = 0; j != n; ++j) {
		ys[j] = f(xs[j]);
	}

	return _natural_spline_2(ys, xs);
}

}