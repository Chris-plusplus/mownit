#include <roots/newton.hpp>
#include <roots/stop/dx.hpp>
#include <roots/stop/val.hpp>
#include <stdexcept>
#include <limits>
#include <string>
#include <iostream>

namespace roots {

std::pair<vecf, size_t> newton(fn f, fn df, flt x_0, flt a, flt b, flt eps, stop::predicate _stop_predicate) {
	vecf steps = {
		x_0
	};

	if (_stop_predicate == stop::predicate::val) {
		for (; not stop::val(f(x_0), eps);) {
			x_0 -= f(x_0) / df(x_0);

			if (x_0 < a or x_0 > b or std::isnan(x_0)) {
				return {{std::nan("")}, (size_t)-1};
			}

			steps.push_back(x_0);
		}
	}
	else if (_stop_predicate == stop::predicate::dx) {
		flt x_prev = -std::numeric_limits<flt>::infinity();
		for (; not stop::dx(x_0, x_prev, eps);) {
			x_prev = x_0;
			x_0 -= f(x_0) / df(x_0);

			if (x_0 < a or x_0 > b or std::isnan(x_0)) {
				return {{std::nan("")}, (size_t)-1};
			}

			steps.push_back(x_0);
		}
	}

	size_t iters = steps.size();
	return {std::move(steps), iters - 1};
}

}