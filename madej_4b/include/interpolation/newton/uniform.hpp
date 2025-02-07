#pragma once

namespace interpolation {

fn _newton_uniform(const vecf& ys, const vecf& xs);
fn newton_uniform(fn f, size_t n, flt a = -1, flt b = 1);

}