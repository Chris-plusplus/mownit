#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <format>
#include <fstream>
#include <chrono>
#include <matrix.hpp>
#include <fstream>
#include <future>

constexpr int m = 2;
constexpr int k = 6;

constexpr size_t di = 1;
constexpr size_t nontridiag_limit = 1000;
constexpr size_t limit = 1000;

template<class T>
T avg_error(const vec<T>& expected, const vec<T>& got) noexcept {
	T result = 0;
	for (size_t i = 0; i != expected.size(); ++i) {
		result += std::fabs(expected[i] - got[i]);
	}
	return result / (T)expected.size();
}


int main() {
	std::future<void> future;
	std::cout << "f32/f64: ";
	std::string in;
	std::cin >> in;
	if (in == "f32") {
		future = std::async(std::launch::async, []() noexcept {
			auto fulltime_start = clk::now();

			auto rng = std::mt19937(1234);

			auto times_file_f32 = std::ofstream("times_f32.txt");
			auto errors_file_f32 = std::ofstream("errors_f32.txt");
			auto conditions_file_f32 = std::ofstream("conditions_f32.txt");

			std::cout << "n\tA_1\tA_2\tA_3 gauss\tA_3 thomas\ttimes sum\tuser time\n";
			times_file_f32 << "n\tA_1\tA_2\tA_3 gauss\tA_3 thomas\ttimes sum\tuser time\n";
			errors_file_f32 << "n\tA_1\tA_2\tA_3 gauss\tA_3 thomas\n";
			conditions_file_f32 << "n\tA_1\tA_2\tA_3\n";

			for (size_t n = 1; n <= limit; ++n) {
				auto usertime_start = clk::now();

				auto A_1 = mat<f32>();
				auto A_1_for_condition = mat<f32>();
				auto A_2 = mat<f32>();
				auto A_2_for_condition = mat<f32>();
				auto A_3 = mat<f32>();
				auto A_3_for_condition = mat<f32>();
				auto A_3_copy = mat<f32>();
				auto x = vec<f32>();

				auto x_future = std::async(std::launch::async, [&n, &rng, &x]() noexcept {
					x = vec<f32>(n, 0);
					for (size_t i = 0; i != x.size(); ++i) {
						if (rng() % 2) {
							x[i] = -1.0;
						}
						else {
							x[i] = 1.0;
						}
					}
				});
				auto A_1_future = std::async(std::launch::async, [&n, &A_1]() noexcept {
					if (n <= nontridiag_limit) {
						A_1 = mat<f32>(n, vec<f32>(n, 0));
						for (size_t i = 1; i <= n; ++i) {
							if (i == 1) {
								for (size_t j = 1; j <= n; ++j) {
									A_1[0][j - 1] = 1.0;
								}
							}
							else {
								for (size_t j = 1; j <= n; ++j) {
									A_1[i - 1][j - 1] = 1.0 / ((f32)i + (f32)j - 1.0);
								}
							}
						}
					}
				});
				auto A_2_future = std::async(std::launch::async, [&n, &A_2]() noexcept {
					if (n <= nontridiag_limit) {
						A_2 = mat<f32>(n, vec<f32>(n, 0));
						for (size_t i = 1; i <= n; ++i) {
							for (size_t j = i; j <= n; ++j) {
								A_2[i - 1][j - 1] = 2.0 * (f32)i / (f32)j;
							}
						}
						for (size_t i = 1; i <= n; ++i) {
							for (size_t j = 1; j < i; ++j) {
								A_2[i - 1][j - 1] = A_2[j - 1][i - 1];
							}
						}
					}
				});
				auto A_3_future = std::async(std::launch::async, [&n, &A_3]() noexcept {
					// b)
					A_3 = mat<f32>(n, vec<f32>(n, 0));
					for (size_t i = 1; i <= n; ++i) {
						if (i - 1 >= 1) {
							A_3[i - 1][i - 1 - 1] = (f32)m / (f32)i;
						}
						A_3[i - 1][i - 1] = -(f32)m * (f32)i - (f32)k;
						if (i + 1 <= n) {
							A_3[i - 1][i + 1 - 1] = (f32)i;
						}
					}
				});
				auto A_1_for_condition_future = std::async(std::launch::async, [&n, &A_1_for_condition]() noexcept {
					if (n <= nontridiag_limit) {
						A_1_for_condition = mat<f32>(n, vec<f32>(n, 0));
						for (size_t i = 1; i <= n; ++i) {
							if (i == 1) {
								for (size_t j = 1; j <= n; ++j) {
									A_1_for_condition[0][j - 1] = 1.0;
								}
							}
							else {
								for (size_t j = 1; j <= n; ++j) {
									A_1_for_condition[i - 1][j - 1] = 1.0 / ((f32)i + (f32)j - 1.0);
								}
							}
						}
					}
				});
				auto A_2_for_condition_future = std::async(std::launch::async, [&n, &A_2_for_condition]() noexcept {
					if (n <= nontridiag_limit) {
						A_2_for_condition = mat<f32>(n, vec<f32>(n, 0));
						for (size_t i = 1; i <= n; ++i) {
							for (size_t j = i; j <= n; ++j) {
								A_2_for_condition[i - 1][j - 1] = 2.0 * (f32)i / (f32)j;
							}
						}
						for (size_t i = 1; i <= n; ++i) {
							for (size_t j = 1; j < i; ++j) {
								A_2_for_condition[i - 1][j - 1] = A_2_for_condition[j - 1][i - 1];
							}
						}
					}
				});
				auto A_3_for_condition_future = std::async(std::launch::async, [&n, &A_3_for_condition]() noexcept {
					// b)
					A_3_for_condition = mat<f32>(n, vec<f32>(n, 0));
					for (size_t i = 1; i <= n; ++i) {
						if (i - 1 >= 1) {
							A_3_for_condition[i - 1][i - 1 - 1] = (f32)m / (f32)i;
						}
						A_3_for_condition[i - 1][i - 1] = -(f32)m * (f32)i - (f32)k;
						if (i + 1 <= n) {
							A_3_for_condition[i - 1][i + 1 - 1] = (f32)i;
						}
					}
				});
				auto A_3_copy_future = std::async(std::launch::async, [&n, &A_3_copy]() noexcept {
					// b)
					A_3_copy = mat<f32>(n, vec<f32>(n, 0));
					for (size_t i = 1; i <= n; ++i) {
						if (i - 1 >= 1) {
							A_3_copy[i - 1][i - 1 - 1] = (f32)m / (f32)i;
						}
						A_3_copy[i - 1][i - 1] = -(f32)m * (f32)i - (f32)k;
						if (i + 1 <= n) {
							A_3_copy[i - 1][i + 1 - 1] = (f32)i;
						}
					}
				});


				auto b_1 = vec<f32>();
				auto b_2 = vec<f32>();
				auto b_3 = vec<f32>();
				auto b_3_copy = vec<f32>();

				auto b_1_future = std::async(std::launch::async, [&n, &A_1_future, &A_1, &x_future, &x, &b_1]() noexcept {
					x_future.wait();
					A_1_future.wait();
					b_1 = n <= nontridiag_limit ? matrix::mul_by_vec(A_1, x) : vec<f32>();
				});
				auto b_2_future = std::async(std::launch::async, [&n, &A_2_future, &A_2, &x_future, &x, &b_2]() noexcept {
					x_future.wait();
					A_2_future.wait();
					b_2 = n <= nontridiag_limit ? matrix::mul_by_vec(A_2, x) : vec<f32>();
				});
				auto b_3_future = std::async(std::launch::async, [&n, &A_3_future, &A_3, &x_future, &x, &b_3]() noexcept {
					x_future.wait();
					A_3_future.wait();
					b_3 = matrix::mul_by_vec(A_3, x);
				});
				auto b_3_copy_future = std::async(std::launch::async, [&n, &A_3_copy_future, &A_3_copy, &x_future, &x, &b_3_copy]() noexcept {
					x_future.wait();
					A_3_copy_future.wait();
					b_3_copy = matrix::mul_by_vec(A_3_copy, x);
				});

				f32 A_1_condition;
				f32 A_2_condition;
				f32 A_3_condition;

				auto A_1_condition_future = std::async(std::launch::async, [&n, &A_1_for_condition_future, &A_1_for_condition, &A_1_condition]() noexcept {
					A_1_for_condition_future.wait();
					A_1_condition = n <= nontridiag_limit ? matrix::condition(std::move(A_1_for_condition)) : std::nan("");
				});
				auto A_2_condition_future = std::async(std::launch::async, [&n, &A_2_for_condition_future, &A_2_for_condition, &A_2_condition]() noexcept {
					A_2_for_condition_future.wait();
					A_2_condition = n <= nontridiag_limit ? matrix::condition(std::move(A_2_for_condition)) : std::nan("");
				});
				auto A_3_condition_future = std::async(std::launch::async, [&n, &A_3_for_condition_future, &A_3_for_condition, &A_3_condition]() noexcept {
					A_3_for_condition_future.wait();
					A_3_condition = matrix::condition(std::move(A_3_for_condition));
				});

				auto result_1 = vec<f32>();
				auto result_2 = vec<f32>();
				auto result_3_gauss = vec<f32>();
				auto result_3_thomas = vec<f32>();

				auto A_1_time_future = std::async(std::launch::async, [&n, &result_1, &A_1, &b_1, &b_1_future, &A_1_condition_future]() noexcept {
					b_1_future.wait();
					auto start = clk::now();
					auto&& [result, _A, _b] = n <= nontridiag_limit ? matrix::solve(std::move(A_1), std::move(b_1)) : std::make_tuple(vec<f32>(), mat<f32>(), vec<f32>());
					auto end = clk::now();
					std::thread([_A = std::move(_A), _b = std::move(_b)]() noexcept {}).detach();
					result_1 = std::move(result);
					return n <= nontridiag_limit ? (f32)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6 : std::nan("");
				});
				auto A_2_time_future = std::async(std::launch::async, [&n, &result_2, &A_2, &b_2, &b_2_future, &A_2_condition_future]() noexcept {
					b_2_future.wait();
					auto start = clk::now();
					auto&& [result, _A, _b] = n <= nontridiag_limit ? matrix::solve(std::move(A_2), std::move(b_2)) : std::make_tuple(vec<f32>(), mat<f32>(), vec<f32>());
					auto end = clk::now();
					std::thread([_A = std::move(_A), _b = std::move(_b)]() noexcept {}).detach();
					result_2 = std::move(result);
					return n <= nontridiag_limit ? (f32)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6 : std::nan("");
				});
				auto A_3_gauss_time_future = std::async(std::launch::async, [&n, &result_3_gauss, &A_3, &b_3, &b_3_future, &A_3_condition_future]() noexcept {
					b_3_future.wait();
					auto start = clk::now();
					auto&& [result, _A, _b] = matrix::solve(std::move(A_3), std::move(b_3));
					auto end = clk::now();
					std::thread([_A = std::move(_A), _b = std::move(_b)]() noexcept {}).detach();
					result_3_gauss = std::move(result);
					return (f32)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6;
				});
				auto A_3_thomas_time_future = std::async(std::launch::async, [&n, &result_3_thomas, &A_3_copy, &b_3_copy, &b_3_copy_future]() noexcept {
					b_3_copy_future.wait();
					auto start = clk::now();
					auto&& [result, _A, _b] = matrix::solve_tridiag(std::move(A_3_copy), std::move(b_3_copy));
					auto end = clk::now();
					std::thread([_A = std::move(_A), _b = std::move(_b)]() noexcept {}).detach();
					result_3_thomas = std::move(result);
					return (f32)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6;
				});

				auto A_1_error_future = std::async(std::launch::async, [&n, &x, &result_1, &A_1_time_future]() noexcept {
					A_1_time_future.wait();
					return n <= nontridiag_limit ? avg_error(x, result_1) : std::nan("");
				});
				auto A_2_error_future = std::async(std::launch::async, [&n, &x, &result_2, &A_2_time_future]() noexcept {
					A_2_time_future.wait();
					return n <= nontridiag_limit ? avg_error(x, result_2) : std::nan("");
				});
				auto A_3_gauss_error_future = std::async(std::launch::async, [&n, &x, &result_3_gauss, &A_3_gauss_time_future]() noexcept {
					A_3_gauss_time_future.wait();
					return n <= nontridiag_limit ? avg_error(x, result_3_gauss) : std::nan("");
				});
				auto A_3_thomas_error_future = std::async(std::launch::async, [&n, &x, &result_3_thomas, &A_3_thomas_time_future]() noexcept {
					A_3_thomas_time_future.wait();
					return n <= nontridiag_limit ? avg_error(x, result_3_thomas) : std::nan("");
				});

				A_1_condition_future.wait();
				A_2_condition_future.wait();
				A_3_condition_future.wait();

				conditions_file_f32 << std::format("{}\t{:.15f}\t{:.15f}\t{:.15f}\n", n, A_1_condition, A_2_condition, A_3_condition);
				errors_file_f32 << std::format("{}\t{:.15f}\t{:.15f}\t{:.15f}\t{:.15f}\n", n, A_1_error_future.get(), A_2_error_future.get(), A_3_gauss_error_future.get(), A_3_thomas_error_future.get());
				auto usertime_end = clk::now();
				auto A_1_time = A_1_time_future.get();
				auto A_2_time = A_2_time_future.get();
				auto A_3_gauss_time = A_3_gauss_time_future.get();
				auto A_3_thomas_time = A_3_thomas_time_future.get();
				auto usertime_ms = (f32)std::chrono::duration_cast<std::chrono::nanoseconds>(usertime_end - usertime_start).count() * 1e-6;

				std::thread([result_1 = std::move(result_1), result_2 = std::move(result_2), result_3_gauss = std::move(result_3_gauss), result_3_thomas = std::move(result_3_thomas)]() noexcept {}).detach();

				auto times_str = std::format("{}\t{:.2f}\t{:.2f}\t{:.2f}\t{:.2f}\t{:.2f}\t{:.2f}\n", n, A_1_time, A_2_time, A_3_gauss_time, A_3_thomas_time, A_1_time + A_2_time + A_3_gauss_time + A_3_thomas_time, usertime_ms);

				times_file_f32 << times_str;
				if (n % 25 == 0) {
					std::cout << times_str;
				}
			}

			auto fulltime_end = clk::now();

			std::cout << std::format("all computing + filesaving + etc. took {:.2f}ms\n", (f32)std::chrono::duration_cast<std::chrono::nanoseconds>(fulltime_end - fulltime_start).count() * 1e-6);
		});
	}
	else if (in == "f64") {
		future = std::async(std::launch::async, []() noexcept {
			auto fulltime_start = clk::now();

			auto rng = std::mt19937(1234);

			auto times_file_f64 = std::ofstream("times_f64.txt");
			auto errors_file_f64 = std::ofstream("errors_f64.txt");
			auto conditions_file_f64 = std::ofstream("conditions_f64.txt");

			std::cout << "n\tA_1\tA_2\tA_3 gauss\tA_3 thomas\ttimes sum\tuser time\n";
			times_file_f64 << "n\tA_1\tA_2\tA_3 gauss\tA_3 thomas\ttimes sum\tuser time\n";
			errors_file_f64 << "n\tA_1\tA_2\tA_3 gauss\tA_3 thomas\n";
			conditions_file_f64 << "n\tA_1\tA_2\tA_3\n";

			for (size_t n = 1; n <= limit; ++n) {
				auto usertime_start = clk::now();

				auto A_1 = mat<f64>();
				auto A_1_for_condition = mat<f64>();
				auto A_2 = mat<f64>();
				auto A_2_for_condition = mat<f64>();
				auto A_3 = mat<f64>();
				auto A_3_for_condition = mat<f64>();
				auto A_3_copy = mat<f64>();
				auto x = vec<f64>();

				auto x_future = std::async(std::launch::async, [&n, &rng, &x]() noexcept {
					x = vec<f64>(n, 0);
					for (size_t i = 0; i != x.size(); ++i) {
						if (rng() % 2) {
							x[i] = -1.0;
						}
						else {
							x[i] = 1.0;
						}
					}
				});
				auto A_1_future = std::async(std::launch::async, [&n, &A_1]() noexcept {
					if (n <= nontridiag_limit) {
						A_1 = mat<f64>(n, vec<f64>(n, 0));
						for (size_t i = 1; i <= n; ++i) {
							if (i == 1) {
								for (size_t j = 1; j <= n; ++j) {
									A_1[0][j - 1] = 1.0;
								}
							}
							else {
								for (size_t j = 1; j <= n; ++j) {
									A_1[i - 1][j - 1] = 1.0 / ((f64)i + (f64)j - 1.0);
								}
							}
						}
					}
				});
				auto A_2_future = std::async(std::launch::async, [&n, &A_2]() noexcept {
					if (n <= nontridiag_limit) {
						A_2 = mat<f64>(n, vec<f64>(n, 0));
						for (size_t i = 1; i <= n; ++i) {
							for (size_t j = i; j <= n; ++j) {
								A_2[i - 1][j - 1] = 2.0 * (f64)i / (f64)j;
							}
						}
						for (size_t i = 1; i <= n; ++i) {
							for (size_t j = 1; j < i; ++j) {
								A_2[i - 1][j - 1] = A_2[j - 1][i - 1];
							}
						}
					}
				});
				auto A_3_future = std::async(std::launch::async, [&n, &A_3]() noexcept {
					// b)
					A_3 = mat<f64>(n, vec<f64>(n, 0));
					for (size_t i = 1; i <= n; ++i) {
						if (i - 1 >= 1) {
							A_3[i - 1][i - 1 - 1] = (f64)m / (f64)i;
						}
						A_3[i - 1][i - 1] = -(f64)m * (f64)i - (f64)k;
						if (i + 1 <= n) {
							A_3[i - 1][i + 1 - 1] = (f64)i;
						}
					}
				});
				auto A_1_for_condition_future = std::async(std::launch::async, [&n, &A_1_for_condition]() noexcept {
					if (n <= nontridiag_limit) {
						A_1_for_condition = mat<f64>(n, vec<f64>(n, 0));
						for (size_t i = 1; i <= n; ++i) {
							if (i == 1) {
								for (size_t j = 1; j <= n; ++j) {
									A_1_for_condition[0][j - 1] = 1.0;
								}
							}
							else {
								for (size_t j = 1; j <= n; ++j) {
									A_1_for_condition[i - 1][j - 1] = 1.0 / ((f64)i + (f64)j - 1.0);
								}
							}
						}
					}
				});
				auto A_2_for_condition_future = std::async(std::launch::async, [&n, &A_2_for_condition]() noexcept {
					if (n <= nontridiag_limit) {
						A_2_for_condition = mat<f64>(n, vec<f64>(n, 0));
						for (size_t i = 1; i <= n; ++i) {
							for (size_t j = i; j <= n; ++j) {
								A_2_for_condition[i - 1][j - 1] = 2.0 * (f64)i / (f64)j;
							}
						}
						for (size_t i = 1; i <= n; ++i) {
							for (size_t j = 1; j < i; ++j) {
								A_2_for_condition[i - 1][j - 1] = A_2_for_condition[j - 1][i - 1];
							}
						}
					}
				});
				auto A_3_for_condition_future = std::async(std::launch::async, [&n, &A_3_for_condition]() noexcept {
					// b)
					A_3_for_condition = mat<f64>(n, vec<f64>(n, 0));
					for (size_t i = 1; i <= n; ++i) {
						if (i - 1 >= 1) {
							A_3_for_condition[i - 1][i - 1 - 1] = (f64)m / (f64)i;
						}
						A_3_for_condition[i - 1][i - 1] = -(f64)m * (f64)i - (f64)k;
						if (i + 1 <= n) {
							A_3_for_condition[i - 1][i + 1 - 1] = (f64)i;
						}
					}
				});
				auto A_3_copy_future = std::async(std::launch::async, [&n, &A_3_copy]() noexcept {
					// b)
					A_3_copy = mat<f64>(n, vec<f64>(n, 0));
					for (size_t i = 1; i <= n; ++i) {
						if (i - 1 >= 1) {
							A_3_copy[i - 1][i - 1 - 1] = (f64)m / (f64)i;
						}
						A_3_copy[i - 1][i - 1] = -(f64)m * (f64)i - (f64)k;
						if (i + 1 <= n) {
							A_3_copy[i - 1][i + 1 - 1] = (f64)i;
						}
					}
				});


				auto b_1 = vec<f64>();
				auto b_2 = vec<f64>();
				auto b_3 = vec<f64>();
				auto b_3_copy = vec<f64>();

				auto b_1_future = std::async(std::launch::async, [&n, &A_1_future, &A_1, &x_future, &x, &b_1]() noexcept {
					x_future.wait();
					A_1_future.wait();
					b_1 = n <= nontridiag_limit ? matrix::mul_by_vec(A_1, x) : vec<f64>();
				});
				auto b_2_future = std::async(std::launch::async, [&n, &A_2_future, &A_2, &x_future, &x, &b_2]() noexcept {
					x_future.wait();
					A_2_future.wait();
					b_2 = n <= nontridiag_limit ? matrix::mul_by_vec(A_2, x) : vec<f64>();
				});
				auto b_3_future = std::async(std::launch::async, [&n, &A_3_future, &A_3, &x_future, &x, &b_3]() noexcept {
					x_future.wait();
					A_3_future.wait();
					b_3 = matrix::mul_by_vec(A_3, x);
				});
				auto b_3_copy_future = std::async(std::launch::async, [&n, &A_3_copy_future, &A_3_copy, &x_future, &x, &b_3_copy]() noexcept {
					x_future.wait();
					A_3_copy_future.wait();
					b_3_copy = matrix::mul_by_vec(A_3_copy, x);
				});

				f64 A_1_condition;
				f64 A_2_condition;
				f64 A_3_condition;

				auto A_1_condition_future = std::async(std::launch::async, [&n, &A_1_for_condition_future, &A_1_for_condition, &A_1_condition]() noexcept {
					A_1_for_condition_future.wait();
					A_1_condition = n <= nontridiag_limit ? matrix::condition(std::move(A_1_for_condition)) : std::nan("");
				});
				auto A_2_condition_future = std::async(std::launch::async, [&n, &A_2_for_condition_future, &A_2_for_condition, &A_2_condition]() noexcept {
					A_2_for_condition_future.wait();
					A_2_condition = n <= nontridiag_limit ? matrix::condition(std::move(A_2_for_condition)) : std::nan("");
				});
				auto A_3_condition_future = std::async(std::launch::async, [&n, &A_3_for_condition_future, &A_3_for_condition, &A_3_condition]() noexcept {
					A_3_for_condition_future.wait();
					A_3_condition = matrix::condition(std::move(A_3_for_condition));
				});

				auto result_1 = vec<f64>();
				auto result_2 = vec<f64>();
				auto result_3_gauss = vec<f64>();
				auto result_3_thomas = vec<f64>();

				auto A_1_time_future = std::async(std::launch::async, [&n, &result_1, &A_1, &b_1, &b_1_future, &A_1_condition_future]() noexcept {
					b_1_future.wait();
					auto start = clk::now();
					auto&& [result, _A, _b] = n <= nontridiag_limit ? matrix::solve(std::move(A_1), std::move(b_1)) : std::make_tuple(vec<f64>(), mat<f64>(), vec<f64>());
					auto end = clk::now();
					std::thread([_A = std::move(_A), _b = std::move(_b)]() noexcept {}).detach();
					result_1 = std::move(result);
					return n <= nontridiag_limit ? (f64)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6 : std::nan("");
				});
				auto A_2_time_future = std::async(std::launch::async, [&n, &result_2, &A_2, &b_2, &b_2_future, &A_2_condition_future]() noexcept {
					b_2_future.wait();
					auto start = clk::now();
					auto&& [result, _A, _b] = n <= nontridiag_limit ? matrix::solve(std::move(A_2), std::move(b_2)) : std::make_tuple(vec<f64>(), mat<f64>(), vec<f64>());
					auto end = clk::now();
					std::thread([_A = std::move(_A), _b = std::move(_b)]() noexcept {}).detach();
					result_2 = std::move(result);
					return n <= nontridiag_limit ? (f64)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6 : std::nan("");
				});
				auto A_3_gauss_time_future = std::async(std::launch::async, [&n, &result_3_gauss, &A_3, &b_3, &b_3_future, &A_3_condition_future]() noexcept {
					b_3_future.wait();
					auto start = clk::now();
					auto&& [result, _A, _b] = matrix::solve(std::move(A_3), std::move(b_3));
					auto end = clk::now();
					std::thread([_A = std::move(_A), _b = std::move(_b)]() noexcept {}).detach();
					result_3_gauss = std::move(result);
					return (f64)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6;
				});
				auto A_3_thomas_time_future = std::async(std::launch::async, [&n, &result_3_thomas, &A_3_copy, &b_3_copy, &b_3_copy_future]() noexcept {
					b_3_copy_future.wait();
					auto start = clk::now();
					auto&& [result, _A, _b] = matrix::solve_tridiag(std::move(A_3_copy), std::move(b_3_copy));
					auto end = clk::now();
					std::thread([_A = std::move(_A), _b = std::move(_b)]() noexcept {}).detach();
					result_3_thomas = std::move(result);
					return (f64)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6;
				});

				auto A_1_error_future = std::async(std::launch::async, [&n, &x, &result_1, &A_1_time_future]() noexcept {
					A_1_time_future.wait();
					return n <= nontridiag_limit ? avg_error(x, result_1) : std::nan("");
				});
				auto A_2_error_future = std::async(std::launch::async, [&n, &x, &result_2, &A_2_time_future]() noexcept {
					A_2_time_future.wait();
					return n <= nontridiag_limit ? avg_error(x, result_2) : std::nan("");
				});
				auto A_3_gauss_error_future = std::async(std::launch::async, [&n, &x, &result_3_gauss, &A_3_gauss_time_future]() noexcept {
					A_3_gauss_time_future.wait();
					return n <= nontridiag_limit ? avg_error(x, result_3_gauss) : std::nan("");
				});
				auto A_3_thomas_error_future = std::async(std::launch::async, [&n, &x, &result_3_thomas, &A_3_thomas_time_future]() noexcept {
					A_3_thomas_time_future.wait();
					return n <= nontridiag_limit ? avg_error(x, result_3_thomas) : std::nan("");
				});

				A_1_condition_future.wait();
				A_2_condition_future.wait();
				A_3_condition_future.wait();

				conditions_file_f64 << std::format("{}\t{:.30f}\t{:.30f}\t{:.30f}\n", n, A_1_condition, A_2_condition, A_3_condition);
				errors_file_f64 << std::format("{}\t{:.30f}\t{:.30f}\t{:.30f}\t{:.30f}\n", n, A_1_error_future.get(), A_2_error_future.get(), A_3_gauss_error_future.get(), A_3_thomas_error_future.get());
				auto usertime_end = clk::now();
				auto A_1_time = A_1_time_future.get();
				auto A_2_time = A_2_time_future.get();
				auto A_3_gauss_time = A_3_gauss_time_future.get();
				auto A_3_thomas_time = A_3_thomas_time_future.get();
				auto usertime_ms = (f64)std::chrono::duration_cast<std::chrono::nanoseconds>(usertime_end - usertime_start).count() * 1e-6;

				std::thread([result_1 = std::move(result_1), result_2 = std::move(result_2), result_3_gauss = std::move(result_3_gauss), result_3_thomas = std::move(result_3_thomas)]() noexcept {}).detach();

				auto times_str = std::format("{}\t{:.2f}\t{:.2f}\t{:.2f}\t{:.2f}\t{:.2f}\t{:.2f}\n", n, A_1_time, A_2_time, A_3_gauss_time, A_3_thomas_time, A_1_time + A_2_time + A_3_gauss_time + A_3_thomas_time, usertime_ms);

				times_file_f64 << times_str;
				if (n % 25 == 0) {
					std::cout << times_str;
				}
			}

			auto fulltime_end = clk::now();

			std::cout << std::format("all computing + filesaving + etc. took {:.2f}ms\n", (f64)std::chrono::duration_cast<std::chrono::nanoseconds>(fulltime_end - fulltime_start).count() * 1e-6);
		});
	}

	future.wait();
	std::cout << "Calculations completed\n";

	getchar();
	getchar();
}
