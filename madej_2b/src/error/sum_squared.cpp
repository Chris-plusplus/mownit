#include <error/sum_squared.hpp>
#include <error/abs.hpp>
#include <numeric>

flt error::sum_squared(const vecf& abs) {
	return std::accumulate(abs.begin(), abs.end(), (flt)0);
}
flt error::sum_squared(fn f, fn W, const vecf& x) {
	return error::sum_squared(error::abs(f, W, x));
}