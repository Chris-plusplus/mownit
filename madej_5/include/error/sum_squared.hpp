#pragma once

namespace error {

flt sum_squared(const vecf& abs);
flt sum_squared(fn f, fn W, const vecf& xs);

}