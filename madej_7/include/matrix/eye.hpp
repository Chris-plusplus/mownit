#pragma once

namespace matrix {

template<class T>
mat<T> eye(size_t n) noexcept {
	auto result = mat<T>(n, vec<T>(n, 0));
	for (size_t i = 0; i != n; ++i) {
		result[i][i] = 1.0;
	}
	return std::move(result);
}

}