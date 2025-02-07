#include <error/sum_squared.hpp>
#include <error/abs.hpp>
#include <numeric>

flt error::sum_squared(const vecf& abs) {
	flt sum = 0;
	for (auto&& v : abs) {
		sum += v * v;
	}
	return sum;
}
flt error::sum_squared(fn f, fn W, const vecf& x) {
	return error::sum_squared(error::abs(f, W, x));
}