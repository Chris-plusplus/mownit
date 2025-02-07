#pragma once

namespace interpolation {

fn _lagrange(const vecf& ys, const vecf& xs);
fn lagrange(fn f, nodegen node_fn, size_t n, flt a = -1, flt b = 1);

}