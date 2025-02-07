#pragma once

namespace interpolation {

fn _clamped_2(const vecf& ys, const vecf& xs);
fn clamped_2(fn f, nodegen node_fn, size_t n, flt a = -1, flt b = 1);

}