#pragma once

namespace roots::stop {

inline bool dx(flt x_1, flt x_0, flt eps) noexcept {
	return std::fabs(x_1 - x_0) < eps;
}

}