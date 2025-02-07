#pragma once

namespace interpolation {

enum class boundary_condition {
	natural_spline,
	free = natural_spline,
	clamped
};

}