#pragma once

#include <tuple>

namespace matrix {

// aby wykonać obliczenia 'w miejscu' należy przekazać macierz i wektor wyrazów wolnych poprzez std::move
std::tuple<matf, vecf> gauss_elim(matf A, vecf B);

}