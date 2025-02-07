#pragma once

namespace interpolation {

fn _clamped_3(const vecf& ys, const vecf& xs);
fn clamped_3(fn f, nodegen node_fn, size_t n, flt a = -1, flt b = 1);

}