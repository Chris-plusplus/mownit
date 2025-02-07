#include <error/abs.hpp>
#include <ranges>
#include <algorithm>

vecf error::abs(fn f, fn W, const vecf& xs) {
	auto result = xs;

	std::ranges::for_each(result, [f, W](flt& x) {
		x = fabs(f(x) - W(x));
	});

	return result;
}