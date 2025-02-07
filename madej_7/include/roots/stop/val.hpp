#pragma once

#include <cmath>

namespace roots::stop {

inline bool val(flt fx, flt eps) noexcept {
	return std::fabs(fx) < eps;
}

}