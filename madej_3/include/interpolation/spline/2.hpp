#pragma once

#include "2/natural_spline.hpp"
#include "2/clamped.hpp"
#include "boundary_condition.hpp"

namespace interpolation {

fn spline_2_deg(fn f, nodegen node_fn, size_t n, boundary_condition cond, flt a, flt b);

}