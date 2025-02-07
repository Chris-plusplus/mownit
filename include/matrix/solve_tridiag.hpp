#pragma once

#include "gauss_elim_tridiag.hpp"
#include "back_subst.hpp"

namespace matrix {

template<class T>
std::tuple<vec<T>, mat<T>, vec<T>> solve_tridiag(mat<T> A, vec<T> B) noexcept {
	auto&& [a, b] = gauss_elim_tridiag(std::move(A), std::move(B));
	return back_subst(std::move(a), std::move(b));
}

}