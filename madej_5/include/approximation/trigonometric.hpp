#pragma once

namespace approx {

fn _trig(const vecf& ys, const vecf& xs, size_t m, flt a, flt b);
fn trig(fn f, nodegen node_fn, size_t n, size_t m, flt a, flt b);

}