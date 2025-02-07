#include <roots/secant.hpp>
#include <roots/stop/dx.hpp>
#include <roots/stop/val.hpp>
#include <stdexcept>
#include <limits>
#include <string>
#include <iostream>

namespace roots {

std::pair<vecf, size_t> secant(fn f, flt x_0, flt x_1, flt a, flt b, flt eps, stop::predicate _stop_predicate) {
	vecf steps = {
		x_0,
		x_1
	};

	flt temp;
	if (_stop_predicate == stop::predicate::val) {
		for (; not stop::val(f(x_1), eps);) {
			temp = x_1;
			x_1 -= f(x_1) * (x_1 - x_0) / (f(x_1) - f(x_0));
			x_0 = temp;

			if (x_0 < a or x_0 > b or std::isnan(x_1)) {
				return {{std::nan("")}, (size_t)-1};
			}

			steps.push_back(x_1);
		}
	}
	else if (_stop_predicate == stop::predicate::dx) {
		for (; not stop::dx(x_1, x_0, eps);) {
			temp = x_1;
			x_1 -= f(x_1) * (x_1 - x_0) / (f(x_1) - f(x_0));
			x_0 = temp;

			if (x_0 < a or x_0 > b or std::isnan(x_1)) {
				return {{std::nan("")}, (size_t)-1};
			}

			steps.push_back(x_1);
		}
	}

	size_t iters = steps.size();
	return {std::move(steps), iters - 2};
}

}