#include <interpolation/spline/2.hpp>
#include <stdexcept>

namespace interpolation {

fn spline_2_deg(fn f, nodegen node_fn, size_t n, boundary_condition cond, flt a, flt b) {
	switch (cond) {
		case boundary_condition::natural_spline:
			return natural_spline_2(f, node_fn, n, a, b);
		case boundary_condition::clamped:
			return clamped_2(f, node_fn, n, a, b);
		default:
			throw std::invalid_argument("Boundary condition not implemented");
	}
}

}