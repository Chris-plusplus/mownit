#include <interpolation/newton/binomcoeffs.hpp>

flt interpolation::binomcoeffs_newton(flt n, size_t k, flt start) {
	for (; k > 0; --k, --n/* -= 1*/) {
		start *= n / (flt)k;
	}

	return start;
}