#include <error/max.hpp>
#include <ranges>
#include <error/abs.hpp>

flt error::max(const vecf& abs) {
	return *std::ranges::max_element(abs);
}
flt error::max(fn f, fn W, const vecf& x) {
	return error::max(error::abs(f, W, x));
}