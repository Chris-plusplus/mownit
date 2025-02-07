#include <derivative.hpp>

//fn derivative(SymEngine::RCP<const SymEngine::Basic> f_expr) {
//	return nth_derivative(f_expr, 1);
//}
//fn nth_derivative(SymEngine::RCP<const SymEngine::Basic> f_expr, size_t n) {
//	auto df = f_expr;
//	for (size_t i = 0; i != n; ++i) {
//		df = df->diff(SymEngine::symbol("x"));
//	}
//
//	return [df, _x = SymEngine::symbol("x")](double x) -> flt {
//		return SymEngine::eval_double(*df->subs({{_x, SymEngine::Expression(std::to_string(x))}}));
//	};
//}