#include <interpolation/hermite/precompute.hpp>
//#include <symengine/eval_double.h>
//#include <symengine/ntheory.h>
//
//std::tuple<vecf, vecz, size_t> interpolation::precompute_hermite(const vec2f& ys, const vecf& xs) {
//	auto m = vecz();
//	size_t m_sum = 0;
//	for (size_t i = 0; i != ys.size(); ++i) {
//		m.push_back(ys[i].size());
//		m_sum += m.back();
//	}
//
//	auto extended_y = vec2f();
//	auto extended_x = vecf();
//
//	size_t n = m_sum - 1;
//	auto b = vec2f(m_sum, vecf(m_sum));
//
//	size_t extension_count = 0;
//	for (size_t i = 0; i != m.size(); ++i) {
//		for (size_t j = 0; j != m[i]; ++j, ++extension_count) {
//			extended_x.push_back(xs[i]); // to te kilka linijek wyżej
//			extended_y.push_back(ys[i]);
//			extended_y.back().insert(extended_y.back().begin(), extension_count, {});
//		}
//	}
//
//	for (size_t i = 0, yi = 0; i != m_sum and yi != ys.size(); ++yi) {
//		for (size_t j = 0; j != m[yi]; ++j, ++i) {
//			b[i][i] = ys[yi][0];
//		}
//	}
//
//	for (size_t k = 1; k != m_sum; ++k) {
//		for (size_t i = 0; i + k != m_sum; ++i) {
//			if (extended_x[i + k] == extended_x[i] and i + k < extended_y[i].size()) { // można użyć takiego porównania, bo do extended_x były wpisywane te same wartości, patrz kilka linijek wyżej
//				b[i][i + k] = extended_y[i][i + k] / SymEngine::eval_double(*SymEngine::factorial(k));
//			}
//			else if (extended_x[i + k] != extended_x[i]) {
//				b[i][i + k] = (b[i + 1][i + k] - b[i][i + k - 1]) / (extended_x[i + k] - extended_x[i]);
//			}
//		}
//	}
//
//	return std::make_tuple(std::move(b[0]), std::move(m), std::move(m_sum));
//}