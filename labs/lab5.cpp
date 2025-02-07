#include <vector>
#include <format>
#include <fstream>
#include <iostream>
#include <cmath>
#include <numbers>
#if not NOPLOT
#include <CvPlot/cvplot.h>
#include <Legend.hpp>
#endif
#include <future>
#include <ranges>
#include <numeric>
#include <filesystem>

#include <approximation/least_square.hpp>

#include <nodes.hpp>
#include <error.hpp>

using namespace std::chrono_literals;
#if not NOPLOT
namespace plt = CvPlot;
#endif

size_t k = 3;
size_t m = 3;

flt a = -2.0 * std::numbers::pi_v<flt>;
flt b = 1.0 * std::numbers::pi_v<flt>;

static auto f(flt x) {
	flt _x = k * sin(m * x);

	return (flt)1 / std::exp(_x);
};

flt dx = 0.01;

#if not NOPLOT

auto window_height = 400;
auto window_width = 600;

struct settings {
	cv::Scalar color;
	const std::string& name;
	const std::string& line;
	int size;
};

auto legend_width = 200;
auto legend_height = 80;
auto legend_height_error = 50;

#endif

#define __tostring2nd(x) #x
#define tostring(x) __tostring2nd(x)

int main() {
	for (auto&& dir : {
		"approximation_images/least_square/uniform/",
		"approximation_images/least_square/error_uniform/",
		"approximation_results/least_square/"
		 }) {
		if (not std::filesystem::exists(dir)) {
			std::filesystem::create_directories(dir);
		}
	}

	auto max_abs_file = std::ofstream("approximation_results/least_square/__max_abs.txt");
	auto max_abs_log_file = std::ofstream("approximation_results/least_square/__max_abs_log.txt");
	auto sum_squared_file = std::ofstream("approximation_results/least_square/__sum_squared.txt");
	auto sum_squared_log_file = std::ofstream("approximation_results/least_square/__sum_squared_log.txt");

	max_abs_file <<
		"n\\m";
	max_abs_log_file <<
		"n\\m";
	sum_squared_file <<
		"n\\m";
	sum_squared_log_file <<
		"n\\m";

	//vecz nodes_counts = {5};
	vecz nodes_counts;
	//vecz nodes_counts = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50};
	for (size_t i = 3; i <= 200; i += 1) {
		nodes_counts.push_back(i);
	}
	//nodes_counts.push_back(10000);

	for (size_t i = 2; i != 100; ++i) {
		max_abs_file << '\t' << i;
		max_abs_log_file << '\t' << i;
		sum_squared_file << '\t' << i;
		sum_squared_log_file << '\t' << i;
	}
	max_abs_file << '\n';
	max_abs_log_file << '\n';
	sum_squared_file << '\n';
	sum_squared_log_file << '\n';

	vecf ls_max_abs_values;
	vecf ls_sum_squared_values;

	auto ls_ws = vecf(nodes_counts.back(), 1.0);

	auto ls_max_abs_values_log = matf(nodes_counts.back() + 1, vecf(100, nan("")));
	auto ls_sum_squared_values_log = matf(nodes_counts.back() + 1, vecf(100, nan("")));

	// {m, nodes_count}
	std::set<std::pair<flt, flt>> save_whitelist{
		{15, 16},
		{15, 20},
		{15, 30},
	};

	for (auto&& nodes_count : nodes_counts) {
		std::cout << nodes_count << '\n';

		max_abs_file << nodes_count;
		max_abs_log_file << nodes_count;
		sum_squared_file << nodes_count;
		sum_squared_log_file << nodes_count;

		for (size_t m = nodes_counts.front() - 1; m < nodes_count and m < 100; ++m) {
			if (m % 10 == 0) {
				std::cout << '\t' << m << '\n';
			}
#if not NOFILE
			std::ofstream result_file;
			if (save_whitelist.contains({m, nodes_count})) {
				result_file = std::ofstream("approximation_results/least_square/result_" + std::to_string(m) + '_' + std::to_string(nodes_count) + ".txt");
				result_file <<
					"x\tleast_squares\n";
			}
#endif

			auto ls = approx::least_square(f, nodes::uniform, nodes_count, m, ls_ws, a, b);

			vecf xs;

			vecf f_values;

			vecf ls_values;

			for (flt x = a; x < b; x += dx) {
				xs.push_back(x);

				f_values.push_back(f(x));

				ls_values.push_back(ls(x));

#if not NOFILE
				if (save_whitelist.contains({m, nodes_count})) {
					result_file << std::format(
						"{}\t{}\t{}\n",
						x,
						f_values.back(),
						ls_values.back()
					);
				}
#endif
			}
			xs.push_back(b);

			f_values.push_back(f(b));

			ls_values.push_back(ls(b));
#if not NOFILE
			if (save_whitelist.contains({m, nodes_count})) {
				result_file << std::format(
					"{}\t{}\t{}\n",
					b,
					f_values.back(),
					ls_values.back()
				);
			}
#endif
#if not NOPLOT

			auto f_sett = settings{
				.color = {0, 191, 0},
				.name = "funkcja",
				.line = "-",
				.size = 1
			};
			auto ls_sett = settings{
				.color = {0, 0, 191},
				.name = "aproksymacja",
				.line = "-",
				.size = 1
			};
			auto nodes_sett = settings{
				.color = {255, 0, 0},
				.name = "wezly",
				.line = "o",
				.size = 12
			};

			auto nodes_uniform_xs = nodes::uniform(nodes_count, a, b);
			auto nodes_uniform_ys = nodes_uniform_xs;
			std::ranges::for_each(nodes_uniform_ys, [](flt& y) {
				y = f(y);
			});

			auto axes_uniform = plt::makePlotAxes();
			auto axes_error_uniform = plt::makePlotAxes();

			axes_uniform.xLabel("x").yLabel("y").title("Aproksymacja dla " + std::to_string(nodes_count) + " wezlow jednorodnych i " + std::to_string(m) + " funkcji bazowych");
			axes_error_uniform.xLabel("x").yLabel("y").title("Blad bezwzgledny interpolacji dla " + std::to_string(nodes_count) + " wezlow jednorodnych i " + std::to_string(m) + " funkcji bazowych");

#endif

			auto ls_err_values = error::abs(f, ls, xs);

#if not NOFILE

			std::ofstream error_file;

			if (save_whitelist.contains({m, nodes_count})) {
				error_file = std::ofstream("approximation_results/least_square/error_" + std::to_string(m) + '_' + std::to_string(nodes_count) + ".txt");
				error_file <<
					"x\tf(x)\tleast_squares\n";
				for (size_t i = 0; i != xs.size(); ++i) {
					error_file << std::format(
						"{}\t{}\t{}\n",
						xs[i],
						f_values[i],
						ls_err_values[i]
					);
				}
			}

			ls_max_abs_values.push_back(error::max(ls_err_values));
			ls_sum_squared_values.push_back(error::sum_squared(ls_err_values));

			ls_max_abs_values_log[nodes_count][m] = log(ls_max_abs_values.back());
			ls_sum_squared_values_log[nodes_count][m] = log(ls_sum_squared_values.back());

			max_abs_file << std::format(
				"\t{}",
				ls_max_abs_values.back()
			);
			max_abs_log_file << std::format(
				"\t{}",
				log(ls_max_abs_values.back())
			);

			sum_squared_file << std::format(
				"\t{}",
				ls_sum_squared_values.back()
			);
			sum_squared_log_file << std::format(
				"\t{}",
				log(ls_sum_squared_values.back())
			);
#endif

#if not NOPLOT

#pragma region axes series and settings

			auto&& f_uniform_series = axes_uniform.create<plt::Series>(xs, f_values, f_sett.line)
				.setColor(f_sett.color)
				.setLineWidth(f_sett.size)
				.setName(f_sett.name);

			auto&& ls_uniform_series = axes_uniform.create<plt::Series>(xs, ls_values, ls_sett.line)
				.setColor(ls_sett.color)
				.setLineWidth(ls_sett.size)
				.setName(ls_sett.name);

			auto&& nodes_uniform_series = axes_uniform.create<plt::Series>(nodes_uniform_xs, nodes_uniform_ys, nodes_sett.line)
				.setColor(nodes_sett.color)
				.setMarkerSize(nodes_sett.size)
				.setName(nodes_sett.name);
			auto&& legend_uniform = axes_uniform.create<plt::Legend>()
				.setWidth(legend_width)
				.setHeigth(legend_height)
				.setAxes(axes_uniform);

			auto&& ls_error_series = axes_error_uniform.create<plt::Series>(xs, ls_err_values, ls_sett.line)
				.setColor(ls_sett.color)
				.setLineWidth(ls_sett.size)
				.setName(ls_sett.name);

			auto&& legend_error_uniform = axes_error_uniform.create<plt::Legend>()
				.setWidth(legend_width)
				.setHeigth(legend_height_error)
				.setAxes(axes_error_uniform);

#pragma endregion

			auto x_lim_mul = 1.5;

			axes_uniform.setXLim({a, b * x_lim_mul});
			axes_error_uniform.setXLim({a, b * x_lim_mul});

			if (save_whitelist.contains({m, nodes_count})) {
				cv::imwrite("approximation_images/least_square/uniform/" + std::to_string(m) + '_' + std::to_string(nodes_count) + ".png", axes_uniform.render(window_height, window_width));
				cv::imwrite("approximation_images/least_square/error_uniform/" + std::to_string(m) + '_' + std::to_string(nodes_count) + ".png", axes_error_uniform.render(window_height, window_width));
			}

#endif

		}

		max_abs_file << '\n';
		max_abs_log_file << '\n';
		sum_squared_file << '\n';
		sum_squared_log_file << '\n';
	}

#if not NOFILE

	auto ls_max_abs_log_dat = std::ofstream("approximation_results/least_square/__max_abs_log.dat");
	auto ls_sum_squared_log_dat = std::ofstream("approximation_results/least_square/__sum_squared_log.dat");

	auto temp_nan = nan("");
	for (size_t m = nodes_counts.front() - 1; m < 100; ++m) {
		for (auto&& n : nodes_counts) {
			ls_max_abs_log_dat << m << ' ' << n << ' ' << ls_max_abs_values_log[n][m] << '\n';
			ls_sum_squared_log_dat << m << ' ' << n << ' ' << ls_sum_squared_values_log[n][m] << '\n';
		}

		ls_max_abs_log_dat << '\n';
		ls_sum_squared_log_dat << '\n';
	}

#endif

}