#pragma once

namespace interpolation {

fn _cubic_3(const vecf& ys, const vecf& xs);
fn cubic_3(fn f, nodegen node_fn, size_t n, flt a = -1, flt b = 1);

}