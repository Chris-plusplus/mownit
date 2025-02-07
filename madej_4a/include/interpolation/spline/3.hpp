#pragma once

#include "3/natural_spline.hpp"
#include "3/clamped.hpp"
#include "3/cubic.hpp"
#include "boundary_condition.hpp"

namespace interpolation {

fn spline_3_deg(fn f, nodegen node_fn, size_t n, boundary_condition cond, flt a, flt b);

}