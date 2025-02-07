#include <matrix/solve.hpp>
#include <matrix/back_subst.hpp>
#include <matrix/gauss_elim.hpp>

namespace matrix {

std::tuple<vecf, matf, vecf> solve(matf A, vecf B) {
	auto&& [a, b] = gauss_elim(std::move(A), std::move(B));
	return back_subst(std::move(a), std::move(b));
}

}