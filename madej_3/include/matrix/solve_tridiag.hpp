#pragma once

namespace matrix {

std::tuple<vecf, matf, vecf> solve_tridiag(matf A, vecf B);

}