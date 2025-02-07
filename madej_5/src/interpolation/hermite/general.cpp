#include <interpolation/hermite/general.hpp>
#include <interpolation/hermite/precompute.hpp>

fn interpolation::_hermite(const vec2f& ys, const vecf& xs) {
	auto&& [b, m, m_sum] = interpolation::precompute_hermite(ys, xs);

	return [b = b, m = m, m_sum = m_sum, xs = xs](flt x) -> flt {
		auto x_diffs = vecf(xs.size());
		for (size_t i = 0; i != x_diffs.size(); ++i) {
			x_diffs[i] = x - xs[i];
		}

		flt sum = 0;
		flt p = 1;
		size_t bi = 0;

		for (size_t i = 0; i != m.size(); ++i) {
			for (size_t j = 0; j != m[i] and bi != m_sum; ++j, ++bi) {
				sum += b[bi] * p;
				p *= x_diffs[i];
			}
		}

		return sum;
	};
}
#include <format>
fn interpolation::hermite(SymEngine::RCP<const SymEngine::Basic> f_expr, size_t derivative_n, nodegen node_fn, size_t k, flt a, flt b) {
	auto xs = node_fn(k, a, b);

	auto xsym = SymEngine::symbol("x");

	auto df = std::vector<SymEngine::RCP<const SymEngine::Basic>>();
	df.emplace_back(f_expr);
	for (size_t i = 0; i != derivative_n; ++i) {
		df.emplace_back(df.back()->diff(xsym));
	}

	auto ys = vec2f(k);
	for (size_t i = 0; i != k; ++i) {
		auto&& curr_x = SymEngine::Expression(xs[i]);
		auto&& subs_map = SymEngine::map_basic_basic({{xsym, curr_x}});
		for (auto&& d : df) {
			ys[i].push_back(SymEngine::eval_double(*d->subs(subs_map)));
		}
	}

	return _hermite(ys, xs);
}