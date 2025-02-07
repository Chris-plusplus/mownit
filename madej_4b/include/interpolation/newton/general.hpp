#pragma once

namespace interpolation {

fn _newton(const vecf& ys, const vecf& xs);
fn newton(fn f, nodegen node_fn, size_t n, flt a = -1, flt b = 1);

}