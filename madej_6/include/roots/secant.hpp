#pragma once

#include "stop/predicate.hpp"
#include <utility>

namespace roots {

std::pair<vecf, size_t> secant(fn f, flt x_0, flt x_1, flt a, flt b, flt eps, stop::predicate _stop_predicate);

}