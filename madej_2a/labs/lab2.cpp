#include <vector>
#include <format>
#include <fstream>
#include <iostream>
#include <cmath>
#include <numbers>
#include <CvPlot/cvplot.h>
#include <future>
#include <ranges>
#include <numeric>
#include <Legend.hpp>
#include <filesystem>

#include <interpolation/lagrange.hpp>
#include <interpolation/newton.hpp>
#include <interpolation/hermite.hpp>

#include <nodes.hpp>
#include <error.hpp>

using namespace std::chrono_literals;
//namespace sym = SymEngine;
namespace plt = CvPlot;

size_t k = 3;
size_t m = 3;

flt a = -2.0 * std::numbers::pi_v<flt>;
flt b = std::numbers::pi_v<flt>;

static auto f (flt x) {
	flt _x = k * sin(m * x);

	return (flt)1 / std::exp(_x);
};

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
auto legend_height_error = 40;

#define NOPRINT 1
#define NOFILE 0
#define NOIMAGE 0

int main() {
	for (auto&& dir : {
		"interpolation_images/uniform/",
		"interpolation_images/chebyshev/",
		"interpolation_images/error_uniform/",
		"interpolation_images/error_chebyshev/",
		"interpolation_results/"
	}) {
		if (not std::filesystem::exists(dir)) {
			std::filesystem::create_directories(dir);
		}
	}

	// evaluates to 'exp(-k*sin(m*x))'
	/*auto f_expr = sym::exp(
		sym::Expression(sym::Expression("-1") *
		std::to_string(k)) *
		sym::sin(sym::Expression(std::to_string(m)) *
		sym::Expression("x")));*/

	auto max_abs_file = std::ofstream("interpolation_results/max_abs.txt");
	auto sum_squared_file = std::ofstream("interpolation_results/sum_squared.txt");

	max_abs_file << "nodes_count\tlagrange_uniform\tnewton_uniform\tlagrange_chebyshev\tnewton_chebyshev\n";
	sum_squared_file << "nodes_count\tlagrange_uniform\tnewton_uniform\tlagrange_chebyshev\tnewton_chebyshev\n";

	vecz nodes_counts = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50};

	vecf max_abs_lagrange_uniform_values;
	vecf sum_squared_lagrange_uniform_values;

	vecf max_abs_newton_uniform_values;
	vecf sum_squared_newton_uniform_values;

	vecf max_abs_lagrange_chebyshev_values;
	vecf sum_squared_lagrange_chebyshev_values;

	vecf max_abs_newton_chebyshev_values;
	vecf sum_squared_newton_chebyshev_values;

	for (auto&& nodes_count : nodes_counts) {
#if not NOFILE
		std::ofstream result_file("interpolation_results/result_" + std::to_string(nodes_count) + ".txt");
		result_file << "x\tf(x)\tlagrange_uniform(x)\tnewton_uniform(x)\tlagrange_chebyshev(x)\tnewton_chebyshev(x)\n";
#endif

		auto lagrange_uniform = interpolation::lagrange(f, nodes::uniform, nodes_count, a, b);
		auto lagrange_chebyshev = interpolation::lagrange(f, nodes::chebyshev, nodes_count, a, b);
		auto newton_uniform = interpolation::newton(f, nodes::uniform, nodes_count, a, b);
		auto newton_chebyshev = interpolation::newton(f, nodes::chebyshev, nodes_count, a, b);

		vecf xs;

		vecf f_values;

		vecf lagrange_uniform_values;
		vecf lagrange_chebyshev_values;

		vecf newton_uniform_values;
		vecf newton_chebyshev_values;

#define push_value(__fn, __val) __fn##_values.push_back(__fn(__val))

		for (flt x = a; x < b; x += (flt)0.001) {
			xs.push_back(x);

			push_value(f, x);

			push_value(lagrange_uniform, x);
			push_value(lagrange_chebyshev, x);

			push_value(newton_uniform, x);
			push_value(newton_chebyshev, x);
#if not NOFILE
			result_file << std::format(
				"{}\t{}\t{}\t{}\t{}\t{}\n",
				x,
				f_values.back(),
				lagrange_uniform_values.back(),
				newton_uniform_values.back(),
				lagrange_chebyshev_values.back(),
				newton_chebyshev_values.back()
			);
#endif
		}
		xs.push_back(b);

		push_value(f, b);

		push_value(lagrange_uniform, b);
		push_value(lagrange_chebyshev, b);

		push_value(newton_uniform, b);
		push_value(newton_chebyshev, b);
#if not NOFILE
		result_file << std::format(
			"{}\t{}\t{}\t{}\t{}\t{}\n",
			b,
			f_values.back(),
			lagrange_uniform_values.back(),
			newton_uniform_values.back(),
			lagrange_chebyshev_values.back(),
			newton_chebyshev_values.back()
		);
#endif
#if not NOIMAGE

		auto f_sett = settings{
			.color = {0, 191, 0},
			.name = "funkcja",
			.line = "-",
			.size = 1
		};
		auto lagrange_sett = settings{
			.color = {0, 0, 255},
			.name = "Lagrange'a",
			.line = "-",
			.size = 2
		};
		auto newton_sett = settings{
			.color = {255, 95, 0},
			.name = "Newton'a",
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

		auto lagrange_error_uniform_values = error::abs(f, lagrange_uniform, xs);
		auto lagrange_error_chebyshev_values = error::abs(f, lagrange_chebyshev, xs);
		auto newton_error_uniform_values = error::abs(f, newton_uniform, xs);
		auto newton_error_chebyshev_values = error::abs(f, newton_chebyshev, xs);

#if not NOFILE
		std::ofstream error_file("interpolation_results/error_" + std::to_string(nodes_count) + ".txt");
		error_file << "x\terror_lagrange_uniform\terror_lagrange_chebyshev\terror_newton_uniform\terror_newton_chebyshev\n";

		for (size_t i = 0; i != xs.size(); ++i) {
			error_file << std::format(
				"{}\t{}\t{}\t{}\t{}\n",
				xs[i],
				lagrange_error_uniform_values[i],
				newton_error_uniform_values[i],
				lagrange_error_chebyshev_values[i],
				newton_error_chebyshev_values[i]
			);
		}

		max_abs_lagrange_uniform_values.push_back(error::max(lagrange_error_uniform_values));
		max_abs_newton_uniform_values.push_back(error::max(newton_error_uniform_values));
		max_abs_lagrange_chebyshev_values.push_back(error::max(lagrange_error_chebyshev_values));
		max_abs_newton_chebyshev_values.push_back(error::max(newton_error_chebyshev_values));
		max_abs_file << std::format(
			"{}\t{}\t{}\t{}\t{}\n",
			nodes_count,
			max_abs_lagrange_uniform_values.back(),
			max_abs_newton_uniform_values.back(),
			max_abs_lagrange_chebyshev_values.back(),
			max_abs_newton_chebyshev_values.back()
		);

		sum_squared_lagrange_uniform_values.push_back(error::sum_squared(lagrange_error_uniform_values));
		sum_squared_newton_uniform_values.push_back(error::sum_squared(newton_error_uniform_values));
		sum_squared_lagrange_chebyshev_values.push_back(error::sum_squared(lagrange_error_chebyshev_values));
		sum_squared_newton_chebyshev_values.push_back(error::sum_squared(newton_error_chebyshev_values));

		sum_squared_file << std::format(
			"{}\t{}\t{}\t{}\t{}\n",
			nodes_count,
			sum_squared_lagrange_uniform_values.back(),
			sum_squared_newton_uniform_values.back(),
			sum_squared_lagrange_chebyshev_values.back(),
			sum_squared_newton_chebyshev_values.back()
		);
#endif

#if not NOIMAGE

#pragma region axes series and settings

		auto&& f_uniform_series = axes_uniform.create<plt::Series>(xs, f_values, f_sett.line)
			.setColor(f_sett.color)
			.setLineWidth(f_sett.size)
			.setName(f_sett.name);
		auto&& lagrange_uniform_series = axes_uniform.create<plt::Series>(xs, lagrange_uniform_values, lagrange_sett.line)
			.setColor(lagrange_sett.color)
			.setLineWidth(lagrange_sett.size)
			.setName(lagrange_sett.name);
		auto&& newton_uniform_series = axes_uniform.create<plt::Series>(xs, newton_uniform_values, newton_sett.line)
			.setColor(newton_sett.color)
			.setLineWidth(newton_sett.size)
			.setName(newton_sett.name);
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
		auto&& lagrange_chebyshev_series = axes_chebyshev.create<plt::Series>(xs, lagrange_chebyshev_values, lagrange_sett.line)
			.setColor(lagrange_sett.color)
			.setLineWidth(lagrange_sett.size)
			.setName(lagrange_sett.name);
		auto&& newton_chebyshev_series = axes_chebyshev.create<plt::Series>(xs, newton_chebyshev_values, newton_sett.line)
			.setColor(newton_sett.color)
			.setLineWidth(newton_sett.size)
			.setName(newton_sett.name);
		auto&& nodes_chebyshev_series = axes_chebyshev.create<plt::Series>(nodes_chebyshev_xs, nodes_chebyshev_ys, nodes_sett.line)
			.setColor(nodes_sett.color)
			.setMarkerSize(nodes_sett.size)
			.setName(nodes_sett.name);
		auto&& legend_chebyshev = axes_chebyshev.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height)
			.setAxes(axes_chebyshev);

		auto&& lagrange_error_uniform_series = axes_error_uniform.create<plt::Series>(xs, lagrange_error_uniform_values, lagrange_sett.line)
			.setColor(lagrange_sett.color)
			.setLineWidth(lagrange_sett.size)
			.setName(lagrange_sett.name);
		auto&& newton_error_uniform_series = axes_error_uniform.create<plt::Series>(xs, newton_error_uniform_values, newton_sett.line)
			.setColor(newton_sett.color)
			.setLineWidth(newton_sett.size)
			.setName(newton_sett.name);
		auto&& legend_error_uniform = axes_error_uniform.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height_error)
			.setAxes(axes_error_uniform);

		auto&& lagrange_error_chebyshev_series = axes_error_chebyshev.create<plt::Series>(xs, lagrange_error_chebyshev_values, lagrange_sett.line)
			.setColor(lagrange_sett.color)
			.setLineWidth(lagrange_sett.size)
			.setName(lagrange_sett.name);
		auto&& newton_error_chebyshev_series = axes_error_chebyshev.create<plt::Series>(xs, newton_error_chebyshev_values, newton_sett.line)
			.setColor(newton_sett.color)
			.setLineWidth(newton_sett.size)
			.setName(newton_sett.name);
		auto&& legend_error_chebyshev = axes_error_chebyshev.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height_error)
			.setAxes(axes_error_chebyshev);

#pragma endregion

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

#if not NOIMAGE

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

		max_abs_lagrange_uniform_values.pop_back();
		max_abs_newton_uniform_values.pop_back();
		max_abs_lagrange_chebyshev_values.pop_back();
		max_abs_newton_chebyshev_values.pop_back();

		sum_squared_lagrange_uniform_values.pop_back();
		sum_squared_newton_uniform_values.pop_back();
		sum_squared_lagrange_chebyshev_values.pop_back();
		sum_squared_newton_chebyshev_values.pop_back();
	}
	auto nodes_counts_flt = vecf(nodes_counts.begin(), nodes_counts.end());

	auto lagrange_uniform_sett = settings{
		.color = {0, 0, 255},
		.name = "Lagrange'a, rownomierne",
		.line = "-",
		.size = 2
	};
	auto newton_uniform_sett = settings{
		.color = {255, 0, 0},
		.name = "Newtona, rownomierne",
		.line = "-",
		.size = 1
	};
	auto lagrange_chebyshev_sett = settings{
		.color = {0, 100, 200},
		.name = "Lagrange'a, Czebyszewa",
		.line = "-",
		.size = 2
	};
	auto newton_chebyshev_sett = settings{
		.color = {200, 100, },
		.name = "Newtona, Czebyszewa",
		.line = "-",
		.size = 1
	};

	auto&& max_abs_lagrange_uniform_series = axes_max_abs.create<plt::Series>(nodes_counts_flt, max_abs_lagrange_uniform_values, lagrange_uniform_sett.line)
		.setColor(lagrange_uniform_sett.color)
		.setLineWidth(lagrange_uniform_sett.size)
		.setName(lagrange_uniform_sett.name);
	auto&& max_abs_newton_uniform_series = axes_max_abs.create<plt::Series>(nodes_counts_flt, max_abs_newton_uniform_values, newton_uniform_sett.line)
		.setColor(newton_uniform_sett.color)
		.setLineWidth(newton_uniform_sett.size)
		.setName(newton_uniform_sett.name);
	auto&& max_abs_lagrange_chebyshev_series = axes_max_abs.create<plt::Series>(nodes_counts_flt, max_abs_lagrange_chebyshev_values, lagrange_chebyshev_sett.line)
		.setColor(lagrange_chebyshev_sett.color)
		.setLineWidth(lagrange_chebyshev_sett.size)
		.setName(lagrange_chebyshev_sett.name);
	auto&& max_abs_newton_chebyshev_series = axes_max_abs.create<plt::Series>(nodes_counts_flt, max_abs_newton_chebyshev_values, newton_chebyshev_sett.line)
		.setColor(newton_chebyshev_sett.color)
		.setLineWidth(newton_chebyshev_sett.size)
		.setName(newton_chebyshev_sett.name);
	auto&& legend_max_abs = axes_max_abs.create<plt::Legend>()
		.setWidth(legend_width)
		.setHeigth(legend_height)
		.setAxes(axes_max_abs);

	auto&& sum_squared_lagrange_uniform_series = axes_sum_squared.create<plt::Series>(nodes_counts_flt, sum_squared_lagrange_uniform_values, lagrange_uniform_sett.line)
		.setColor(lagrange_uniform_sett.color)
		.setLineWidth(lagrange_uniform_sett.size)
		.setName(lagrange_uniform_sett.name);
	auto&& sum_squared_newton_uniform_series = axes_sum_squared.create<plt::Series>(nodes_counts_flt, sum_squared_newton_uniform_values, newton_uniform_sett.line)
		.setColor(newton_uniform_sett.color)
		.setLineWidth(newton_uniform_sett.size)
		.setName(newton_uniform_sett.name);
	auto&& sum_squared_lagrange_chebyshev_series = axes_sum_squared.create<plt::Series>(nodes_counts_flt, sum_squared_lagrange_chebyshev_values, lagrange_chebyshev_sett.line)
		.setColor(lagrange_chebyshev_sett.color)
		.setLineWidth(lagrange_chebyshev_sett.size)
		.setName(lagrange_chebyshev_sett.name);
	auto&& sum_squared_newton_chebyshev_series = axes_sum_squared.create<plt::Series>(nodes_counts_flt, sum_squared_newton_chebyshev_values, newton_chebyshev_sett.line)
		.setColor(newton_chebyshev_sett.color)
		.setLineWidth(newton_chebyshev_sett.size)
		.setName(newton_chebyshev_sett.name);
	auto&& legend_sum_squared = axes_sum_squared.create<plt::Legend>()
		.setWidth(legend_width)
		.setHeigth(legend_height)
		.setAxes(axes_sum_squared);

	cv::imwrite("interpolation_images/max_abs.png", axes_max_abs.render(window_height, window_width));
	cv::imwrite("interpolation_images/sum_squared.png", axes_sum_squared.render(window_height, window_width));

#endif

}