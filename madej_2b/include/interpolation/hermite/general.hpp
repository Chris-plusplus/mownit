#pragma once

#include <symengine/expression.h>

namespace interpolation {

fn _hermite(const vec2f& y, const vecf& x);
fn hermite(SymEngine::RCP<const SymEngine::Basic> f_expr, size_t derivative_n, nodegen node_fn, size_t k, flt a = -1, flt b = 1);

}