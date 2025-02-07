#pragma once

namespace approx {

fn _least_square(const vecf& ys, const vecf& xs, size_t m, const vecf& ws);
fn least_square(fn f, nodegen node_fn, size_t n, size_t m, const vecf& ws, flt a, flt b);

}