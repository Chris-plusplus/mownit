#pragma once

#include "gauss_elim_tridiag.hpp"

namespace matrix {

template<class T>
auto thomas = gauss_elim_tridiag<T>;

}