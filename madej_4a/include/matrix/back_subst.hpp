#pragma once

#include <tuple>

namespace matrix {

std::tuple<vecf, matf, vecf> back_subst(matf A, vecf B);

}