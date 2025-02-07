#include <interpolation/hermite/general.hpp>
#include <interpolation/hermite/precompute.hpp>
//
//fn interpolation::_hermite(const vec2f& ys, const vecf& xs) {
//	auto&& [b, m, m_sum] = interpolation::precompute_hermite(ys, xs);
//
//	return [b = b, m = m, m_sum = m_sum, xs = xs](flt x) -> flt {
//		auto x_diffs = std::vector<flt>(xs.size());
//		for (size_t i = 0; i != x_diffs.size(); ++i) {
//			x_diffs[i] = x - xs[i];
//		}
//
//		flt sum = 0;
//		flt p = 1;
//		size_t bi = 0;
//
//		for (size_t i = 0; i != m.size(); ++i) {
//			for (size_t j = 0; j != m[i] and bi != m_sum; ++j, ++bi) {
//				sum += b[bi] * p;
//				p *= x_diffs[i];
//			}
//		}
//
//		return sum;
//	};
//}
//fn interpolation::hermite(SymEngine::RCP<const SymEngine::Basic> f_expr, size_t derivative_n, nodegen node_fn, size_t k, flt a, flt b) {
//	auto xs = node_fn(k, a, b);
//
//	auto df = std::vector<decltype(f_expr)>(derivative_n);
//
//	auto ys = vec2f(k, vecf(k));
//	for (auto&& yi : ys) {
//		for (size_t i = 0; i != derivative_n; ++i);
//	}
//
//	// todo: dokończyć
//
//	return fn();
//}