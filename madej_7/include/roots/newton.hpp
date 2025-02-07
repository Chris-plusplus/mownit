#pragma once

#include "stop/predicate.hpp"
#include <utility>

namespace roots {

std::pair<vecf, size_t> newton(fn f, fn df, flt x_0, flt a, flt b, flt eps, stop::predicate _stop_predicate);

}