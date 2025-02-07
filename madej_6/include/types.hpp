#pragma once

#include <functional>
#include <vector>
#include <chrono>

using flt = double;

using f32 = float;
using f64 = double;

using nodegen = std::function<std::vector<flt>(size_t, flt, flt)>;
using fn = std::function<flt(flt)>;

using vecf = std::vector<flt>;
using vecz = std::vector<size_t>;
using vec2f = std::vector<vecf>;
template<class T>
using vec = std::vector<T>;

using matf = vec2f;
template<class T>
using mat = vec<vec<T>>;

using clk = std::chrono::high_resolution_clock;