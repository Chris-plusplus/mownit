#include <matrix/solve_tridiag.hpp>
#include <matrix/back_subst.hpp>
#include <matrix/gauss_elim_tridiag.hpp>

namespace matrix {

std::tuple<vecf, matf, vecf> solve_tridiag(matf A, vecf B) {
	auto&& [a, b] = gauss_elim_tridiag(std::move(A), std::move(B));
	return back_subst(std::move(a), std::move(b));
}

}