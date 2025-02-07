#include <approximation/trigonometric.hpp>
#include <matrix/solve.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <numbers>

fn approx::_trig(const vecf& ys, const vecf& xs, size_t m, flt a, flt b) {
	size_t n = ys.size();

	if (m > ((n - 1) / 2)) {
		throw std::invalid_argument("m > floor(flt(n - 1) / 2.0)");
	}

	static constexpr const auto pi = std::numbers::pi_v<flt>;
	static constexpr const flt c = -pi;
	static constexpr const flt d = pi;

	auto new_x = [a, b](flt x) -> flt {
		return (x - a) * (d - c) / (b - a) + c;
	};

	auto ab_k = [&](size_t k) -> std::pair<flt, flt> {
		flt a_k = 0;
		flt b_k = 0;
		for (size_t i = 0; i != n; ++i) {
			a_k += ys[i] * cos(k * xs[i]);
			b_k += ys[i] * sin(k * xs[i]);
		}

		return {2.0 * a_k / (flt)(n), 2.0 * b_k / (flt)(n)};
	};

	auto a_ks = vecf(m + 1);
	auto b_ks = vecf(m + 1);
	for (size_t k = 0; k != m + 1; ++k) {
		auto&& [a_k, b_k] = ab_k(k);
		a_ks[k] = a_k;
		b_ks[k] = b_k;
	}

	return [new_x, m, a_ks = std::move(a_ks), b_ks = std::move(b_ks)](flt x) -> flt {
		x = new_x(x);

		flt sum = a_ks[0] * 0.5;
		for (size_t k = 1; k != m + 1; ++k) {
			sum += a_ks[k] * cos(flt(k) * x) + b_ks[k] * sin(flt(k) * x);
		}

		return sum;
	};
}

fn approx::trig(fn f, nodegen node_fn, size_t n, size_t m, flt a, flt b) {
	static constexpr auto pi = std::numbers::pi_v<flt>;
	static constexpr const flt c = -pi;
	static constexpr const flt d = pi;

	auto xs = node_fn(n, a, b);

	auto ys = vecf(n);
	for (size_t j = 0; j != n; ++j) {
		ys[j] = f(xs[j]);
		xs[j] = (xs[j] - a) * (d - c) / (b - a) + c;
	}

	return _trig(ys, xs, m, a, b);
}
