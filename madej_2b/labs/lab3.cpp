#include <vector>
#include <format>
#include <fstream>
#include <iostream>
#include <cmath>
#include <numbers>
#include <future>
#include <ranges>
#include <numeric>
#include <filesystem>

#include <interpolation/lagrange.hpp>
#include <interpolation/newton.hpp>
#include <interpolation/hermite.hpp>

#include <nodes.hpp>
#include <error.hpp>

using namespace std::chrono_literals;
namespace sym = SymEngine;

size_t k = 3;
size_t m = 3;

flt a = -2.0 * std::numbers::pi_v<flt>;
flt b = 1.0 * std::numbers::pi_v<flt>;

static auto f(flt x) {
	flt _x = k * sin(m * x);

	return (flt)1 / std::exp(_x);
};

#if not NOPLOT
#include <CvPlot/cvplot.h>
#include <Legend.hpp>

namespace plt = CvPlot;

auto window_height = 400;
auto window_width = 600;

struct settings {
	cv::Scalar color;
	const std::string& name;
	const std::string& line;
	int size;
};

auto legend_width = 150;
auto legend_height = 80;
auto legend_height_error = 30;
#endif

int main() {
	for (auto&& dir : {
#if not NOPLOT
		"interpolation_images/uniform/",
		"interpolation_images/chebyshev/",
		"interpolation_images/error_uniform/",
		"interpolation_images/error_chebyshev/",
#endif
		"interpolation_results/"
		 }) {
		if (not std::filesystem::exists(dir)) {
			std::filesystem::create_directories(dir);
		}
	}

	// evaluates to 'exp(-k*sin(m*x))'
	auto f_expr = sym::Expression("exp(-3*sin(3*x))");

#if not NOFILE

	auto max_abs_file = std::ofstream("interpolation_results/max_abs.txt");
	auto sum_squared_file = std::ofstream("interpolation_results/sum_squared.txt");

	max_abs_file << "nodes_count\thermite_uniform\thermite_chebyshev\n";
	sum_squared_file << "nodes_count\thermite_uniform\thermite_chebyshev\n";

#endif

	vecz nodes_counts = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50};
	/*for (size_t i = 2; i != 100 + 1; ++i) {
		nodes_counts.push_back(i);
	}*/
	//vecz nodes_counts = {5};

	vecf max_abs_hermite_uniform_values;
	vecf sum_squared_hermite_uniform_values;

	vecf max_abs_hermite_chebyshev_values;
	vecf sum_squared_hermite_chebyshev_values;
	
	for (auto&& nodes_count : nodes_counts) {
		std::cout << std::format("computing for {} nodes\n", nodes_count);
#if not NOFILE
		std::ofstream result_file("interpolation_results/result_" + std::to_string(nodes_count) + ".txt");
		result_file << "x\tf(x)\thermite_uniform(x)\thermite_chebyshev(x)\n";
#endif

		auto hermite_uniform = interpolation::hermite(f_expr, 1, nodes::uniform, nodes_count, a, b);
		auto hermite_chebyshev = interpolation::hermite(f_expr, 1, nodes::chebyshev, nodes_count, a, b);

		vecf xs;

		vecf f_values;

		vecf hermite_uniform_values;
		vecf hermite_chebyshev_values;

#define push_value(__fn, __val) __fn##_values.push_back(__fn(__val))

		for (flt x = a; x < b; x += (flt)0.001) {
			xs.push_back(x);

			push_value(f, x);

			push_value(hermite_uniform, x);
			push_value(hermite_chebyshev, x);
#if not NOFILE
			result_file << std::format(
				"{}\t{}\t{}\t{}\n",
				x,
				f_values.back(),
				hermite_uniform_values.back(),
				hermite_chebyshev_values.back()
			);
#endif
		}
		xs.push_back(b);

		push_value(f, b);

		push_value(hermite_uniform, b);
		push_value(hermite_chebyshev, b);
#if not NOFILE
		result_file << std::format(
			"{}\t{}\t{}\t{}\n",
			b,
			f_values.back(),
			hermite_uniform_values.back(),
			hermite_chebyshev_values.back()
		);
#endif
#if not NOPLOT

		auto f_sett = settings{
			.color = {0, 191, 0},
			.name = "funkcja",
			.line = "-",
			.size = 1
		};
		auto hermite_sett = settings{
			.color = {200, 100, 0},
			.name = "Hermite'a",
			.line = "-",
			.size = 1
		};
		auto nodes_sett = settings{
			.color = {255, 0, 0},
			.name = "wezly",
			.line = "o",
			.size = 15
		};

		auto nodes_uniform_xs = nodes::uniform(nodes_count, a, b);
		auto nodes_uniform_ys = nodes_uniform_xs;
		std::ranges::for_each(nodes_uniform_ys, [](flt& y) {
			y = f(y);
		});
		auto nodes_chebyshev_xs = nodes::chebyshev(nodes_count, a, b);
		auto nodes_chebyshev_ys = nodes_chebyshev_xs;
		std::ranges::for_each(nodes_chebyshev_ys, [](flt& y) {
			y = f(y);
		});


		auto axes_uniform = plt::makePlotAxes();
		auto axes_chebyshev = plt::makePlotAxes();
		auto axes_error_uniform = plt::makePlotAxes();
		auto axes_error_chebyshev = plt::makePlotAxes();

		axes_uniform.xLabel("x").yLabel("y").title("Interpolacje dla " + std::to_string(nodes_count) + " wezlow jednorodnych");
		axes_chebyshev.xLabel("x").yLabel("y").title("Interpolacje dla " + std::to_string(nodes_count) + " wezlow Czebyszewa");
		axes_error_uniform.xLabel("x").yLabel("y").title("Blad bezwzgledny interpolacji dla " + std::to_string(nodes_count) + " wezlow jednorodnych");
		axes_error_chebyshev.xLabel("x").yLabel("y").title("Blad bezwzgledny interpolacji dla " + std::to_string(nodes_count) + " wezlow Czebyszewa");

#endif

		auto hermite_error_uniform_values = error::abs(f, hermite_uniform, xs);
		auto hermite_error_chebyshev_values = error::abs(f, hermite_chebyshev, xs);

#if not NOFILE
		std::ofstream error_file("interpolation_results/error_" + std::to_string(nodes_count) + ".txt");
		error_file << "x\terror_hermite_uniform\terror_hermite_chebyshev\n";

		for (size_t i = 0; i != xs.size(); ++i) {
			error_file << std::format(
				"{}\t{}\t{}\n",
				xs[i],
				hermite_error_uniform_values[i],
				hermite_error_chebyshev_values[i]
			);
		}

#endif

		max_abs_hermite_uniform_values.push_back(error::max(hermite_error_uniform_values));
		max_abs_hermite_chebyshev_values.push_back(error::max(hermite_error_chebyshev_values));

#if not NOFILE

		max_abs_file << std::format(
			"{}\t{}\t{}\n",
			nodes_count,
			max_abs_hermite_uniform_values.back(),
			max_abs_hermite_chebyshev_values.back()
		);

#endif

		sum_squared_hermite_uniform_values.push_back(error::sum_squared(hermite_error_uniform_values));
		sum_squared_hermite_chebyshev_values.push_back(error::sum_squared(hermite_error_chebyshev_values));

#if not NOFILE

		sum_squared_file << std::format(
			"{}\t{}\t{}\n",
			nodes_count,
			sum_squared_hermite_uniform_values.back(),
			sum_squared_hermite_chebyshev_values.back()
		);

#endif

#if not NOPLOT

		auto&& f_uniform_series = axes_uniform.create<plt::Series>(xs, f_values, f_sett.line)
			.setColor(f_sett.color)
			.setLineWidth(f_sett.size)
			.setName(f_sett.name);
		auto&& lagrange_uniform_series = axes_uniform.create<plt::Series>(xs, hermite_uniform_values, hermite_sett.line)
			.setColor(hermite_sett.color)
			.setLineWidth(hermite_sett.size)
			.setName(hermite_sett.name);
		auto&& nodes_uniform_series = axes_uniform.create<plt::Series>(nodes_uniform_xs, nodes_uniform_ys, nodes_sett.line)
			.setColor(nodes_sett.color)
			.setMarkerSize(nodes_sett.size)
			.setName(nodes_sett.name);
		auto&& legend_uniform = axes_uniform.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height)
			.setAxes(axes_uniform);

		auto&& f_chebyshev_series = axes_chebyshev.create<plt::Series>(xs, f_values, f_sett.line)
			.setColor(f_sett.color)
			.setLineWidth(f_sett.size)
			.setName(f_sett.name);
		auto&& hermite_chebyshev_series = axes_chebyshev.create<plt::Series>(xs, hermite_chebyshev_values, hermite_sett.line)
			.setColor(hermite_sett.color)
			.setLineWidth(hermite_sett.size)
			.setName(hermite_sett.name);
		auto&& nodes_chebyshev_series = axes_chebyshev.create<plt::Series>(nodes_chebyshev_xs, nodes_chebyshev_ys, nodes_sett.line)
			.setColor(nodes_sett.color)
			.setMarkerSize(nodes_sett.size)
			.setName(nodes_sett.name);
		auto&& legend_chebyshev = axes_chebyshev.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height)
			.setAxes(axes_chebyshev);

		auto&& hermite_error_uniform_series = axes_error_uniform.create<plt::Series>(xs, hermite_error_uniform_values, hermite_sett.line)
			.setColor(hermite_sett.color)
			.setLineWidth(hermite_sett.size)
			.setName(hermite_sett.name);
		auto&& legend_error_uniform = axes_error_uniform.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height_error)
			.setAxes(axes_error_uniform);

		auto&& lagrange_error_chebyshev_series = axes_error_chebyshev.create<plt::Series>(xs, hermite_error_chebyshev_values, hermite_sett.line)
			.setColor(hermite_sett.color)
			.setLineWidth(hermite_sett.size)
			.setName(hermite_sett.name);
		auto&& legend_error_chebyshev = axes_error_chebyshev.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height_error)
			.setAxes(axes_error_chebyshev);

		auto x_lim_mul = 1.5;

		axes_uniform.setXLim({a, b * x_lim_mul});
		axes_chebyshev.setXLim({a, b * x_lim_mul});
		axes_error_uniform.setXLim({a, b * x_lim_mul});
		axes_error_chebyshev.setXLim({a, b * x_lim_mul});

		cv::imwrite("interpolation_images/uniform/" + std::to_string(nodes_count) + ".png", axes_uniform.render(window_height, window_width));
		cv::imwrite("interpolation_images/chebyshev/" + std::to_string(nodes_count) + ".png", axes_chebyshev.render(window_height, window_width));
		cv::imwrite("interpolation_images/error_uniform/" + std::to_string(nodes_count) + ".png", axes_error_uniform.render(window_height, window_width));
		cv::imwrite("interpolation_images/error_chebyshev/" + std::to_string(nodes_count) + ".png", axes_error_chebyshev.render(window_height, window_width));

		// odkomentować poniższe dla wyświetlenia okien z wykresami
		/*
		auto window_uniform = std::async(std::launch::async, [&]() { CvPlot::show("Węzły równomierne", axes_uniform, window_height, window_width); });
		auto window_chebyshev = std::async(std::launch::async, [&]() { CvPlot::show("Węzły czebyszewa", axes_chebyshev, window_height, window_width); });
		auto window_error_uniform = std::async(std::launch::async, [&]() { CvPlot::show("Błąd bezwzględny, węzły równomierne", axes_error_uniform, window_height, window_width); });
		auto window_error_chebyshev = std::async(std::launch::async, [&]() { CvPlot::show("Błąd bezwzględny, węzły czebyszewa", axes_error_chebyshev, window_height, window_width); });
		*/

		// to też
		/*
		window_uniform.wait();
		window_chebyshev.wait();
		window_error_uniform.wait();
		window_error_chebyshev.wait();
		*/

#endif

	}

#if not NOPLOT

	auto axes_max_abs = plt::makePlotAxes();
	auto axes_sum_squared = plt::makePlotAxes();

	legend_width = 250;

	axes_max_abs
		.xLabel("x")
		.yLabel("y")
		.title("Maksymalne bledy bezwzgledne");
	axes_sum_squared
		.xLabel("x")
		.yLabel("y")
		.title("Sumy kwadratow bledow bezwzglednych");

	while (not nodes_counts.empty() and nodes_counts.back() > 20) { // ograniczenie wykresu
		nodes_counts.pop_back();

		max_abs_hermite_uniform_values.pop_back();
		max_abs_hermite_chebyshev_values.pop_back();

		sum_squared_hermite_uniform_values.pop_back();
		sum_squared_hermite_chebyshev_values.pop_back();
	}
	auto nodes_counts_flt = vecf(nodes_counts.begin(), nodes_counts.end());

	auto hermite_uniform_sett = settings{
		.color = {255, 0, 255},
		.name = "Hermite'a, rownomierne",
		.line = "-",
		.size = 1
	};
	auto hermite_chebyshev_sett = settings{
		.color = {127, 0, 127},
		.name = "Hermite'a, Czebyszewa",
		.line = "-",
		.size = 1
	};

	auto&& max_abs_hermite_uniform_series = axes_max_abs.create<plt::Series>(nodes_counts_flt, max_abs_hermite_uniform_values, hermite_uniform_sett.line)
		.setColor(hermite_uniform_sett.color)
		.setLineWidth(hermite_uniform_sett.size)
		.setName(hermite_uniform_sett.name);
	auto&& max_abs_hermite_chebyshev_series = axes_max_abs.create<plt::Series>(nodes_counts_flt, max_abs_hermite_chebyshev_values, hermite_chebyshev_sett.line)
		.setColor(hermite_chebyshev_sett.color)
		.setLineWidth(hermite_chebyshev_sett.size)
		.setName(hermite_chebyshev_sett.name);
	auto&& legend_max_abs = axes_max_abs.create<plt::Legend>()
		.setWidth(legend_width)
		.setHeigth(legend_height)
		.setAxes(axes_max_abs);

	auto&& sum_squared_hermite_uniform_series = axes_sum_squared.create<plt::Series>(nodes_counts_flt, sum_squared_hermite_uniform_values, hermite_uniform_sett.line)
		.setColor(hermite_uniform_sett.color)
		.setLineWidth(hermite_uniform_sett.size)
		.setName(hermite_uniform_sett.name);
	auto&& sum_squared_hermite_chebyshev_series = axes_sum_squared.create<plt::Series>(nodes_counts_flt, sum_squared_hermite_chebyshev_values, hermite_chebyshev_sett.line)
		.setColor(hermite_chebyshev_sett.color)
		.setLineWidth(hermite_chebyshev_sett.size)
		.setName(hermite_chebyshev_sett.name);
	auto&& legend_sum_squared = axes_sum_squared.create<plt::Legend>()
		.setWidth(legend_width)
		.setHeigth(legend_height)
		.setAxes(axes_sum_squared);

	cv::imwrite("interpolation_images/max_abs.png", axes_max_abs.render(window_height, window_width));
	cv::imwrite("interpolation_images/sum_squared.png", axes_sum_squared.render(window_height, window_width));

#endif

}