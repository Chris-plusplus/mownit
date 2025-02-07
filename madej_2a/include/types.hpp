#pragma once

#include <functional>
#include <vector>

using flt = double;

using nodegen = std::function<std::vector<flt>(size_t, flt, flt)>;
using fn = std::function<flt(flt)>;

using vecf = std::vector<flt>;
using vecz = std::vector<size_t>;
using vec2f = std::vector<std::vector<flt>>;