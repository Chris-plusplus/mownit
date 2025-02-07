#pragma once

#include "gauss_elim.hpp"
#include "back_subst.hpp"

namespace matrix {

template<class T>
std::tuple<vec<T>, mat<T>, vec<T>> solve(mat<T> A, vec<T> B) noexcept {
	auto&& [a, b] = gauss_elim(std::move(A), std::move(B));
	return back_subst(std::move(a), std::move(b));
};

}