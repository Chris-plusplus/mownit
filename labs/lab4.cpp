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
#include <interpolation/spline.hpp>

#include <nodes.hpp>
#include <error.hpp>

using namespace std::chrono_literals;
namespace plt = CvPlot;

size_t k = 3;
size_t m = 3;

flt a = -2.0 * std::numbers::pi_v<flt>;
flt b = 1.0 * std::numbers::pi_v<flt>;

static auto f(flt x) {
	flt _x = k * sin(m * x);

	return (flt)1 / std::exp(_x);
};

//size_t k = 2;
//size_t m = 2;
//
//flt a = -1.0 * std::numbers::pi_v<flt>;
//flt b = 2.0 * std::numbers::pi_v<flt>;
//
//static auto f(flt x) {
//	flt _x = k * sin(m * x);
//
//	return (flt)1 / std::exp(_x) + _x - 1;
//};

auto window_height = 400;
auto window_width = 600;

struct settings {
	cv::Scalar color;
	const std::string& name;
	const std::string& line;
	int size;
};

auto legend_width = 175;
auto legend_height = 100;
auto legend_height_error = 50;

#define spline(__b, __d, __n) __b ## _ ## __d ## _ ## __n
#define get_spline(__b, __d, __n) interpolation::spline_ ## __d ## _deg(f, nodes:: ## __n, nodes_count, interpolation::boundary_condition:: ## __b, a, b)

#define __tostring2nd(x) #x
#define tostring(x) __tostring2nd(x)

int main() {
	for (auto&& dir : {
		"interpolation_images/spline/uniform_2/",
		"interpolation_images/spline/uniform_3/",
		"interpolation_images/spline/uniform_mixed/",
		"interpolation_images/spline/error_uniform_2/",
		"interpolation_images/spline/error_uniform_3/",
		"interpolation_images/spline/error_uniform_mixed/",
		"interpolation_results/spline/"
		 }) {
		if (not std::filesystem::exists(dir)) {
			std::filesystem::create_directories(dir);
		}
	}

	auto max_abs_file = std::ofstream("interpolation_results/spline/__max_abs.txt");
	auto sum_squared_file = std::ofstream("interpolation_results/spline/__sum_squared.txt");

	max_abs_file <<
		"nodes_count\t"
		tostring(spline(natural_spline, 2, uniform))
		"\t"
		tostring(spline(clamped, 2, uniform))
		"\t"
		tostring(spline(natural_spline, 3, uniform))
		"\t"
		tostring(spline(clamped, 3, uniform))
		"\t"
		tostring(spline(cubic, 3, uniform))
		"\n";
	sum_squared_file <<
		"nodes_count\t"
		tostring(spline(natural_spline, 2, uniform))
		"\t"
		tostring(spline(clamped, 2, uniform))
		"\t"
		tostring(spline(natural_spline, 3, uniform))
		"\t"
		tostring(spline(clamped, 3, uniform))
		"\t"
		tostring(spline(cubic, 3, uniform))
		"\n";

	//vecz nodes_counts = {5};
	//vecz nodes_counts;
	vecz nodes_counts = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50};
	for (size_t i = 100; i <= 1000; i += 50) {
		nodes_counts.push_back(i);
	}
	nodes_counts.push_back(10000);

#define max_abs_values(__b, __d, __n) max_abs_ ## __b ## _ ## __d ## _ ## __n ## _values
#define sum_squared_values(__b, __d, __n) sum_squared_ ## __b ## _ ## __d ## _ ## __n ## _values

	vecf max_abs_values(natural_spline, 2, uniform);
	vecf max_abs_values(clamped, 2, uniform);
	vecf max_abs_values(natural_spline, 3, uniform);
	vecf max_abs_values(clamped, 3, uniform);
	vecf max_abs_values(cubic, 3, uniform);
	vecf sum_squared_values(natural_spline, 2, uniform);
	vecf sum_squared_values(clamped, 2, uniform);
	vecf sum_squared_values(natural_spline, 3, uniform);
	vecf sum_squared_values(clamped, 3, uniform);
	vecf sum_squared_values(cubic, 3, uniform);

	for (auto&& nodes_count : nodes_counts) {
		std::cout << nodes_count;
#if not NOFILE
		std::ofstream result_file("interpolation_results/spline/result_" + std::to_string(nodes_count) + ".txt");
		result_file <<
			"x\t"
			tostring(spline(natural_spline, 2, uniform))
			"\t"
			tostring(spline(clamped, 2, uniform))
			"\t"
			tostring(spline(natural_spline, 3, uniform))
			"\t"
			tostring(spline(clamped, 3, uniform))
			"\t"
			tostring(spline(cubic, 3, uniform))
			"\n";
#endif

		auto spline(natural_spline, 2, uniform) = get_spline(natural_spline, 2, uniform);
		auto spline(clamped, 2, uniform) = get_spline(clamped, 2, uniform);
		auto spline(natural_spline, 3, uniform) = get_spline(natural_spline, 3, uniform);
		auto spline(clamped, 3, uniform) = get_spline(clamped, 3, uniform);
		auto spline(cubic, 3, uniform) = get_spline(cubic, 3, uniform);

		std::cout << " gotowe\n";

		vecf xs;

#define values(__b, __d, __n) __b ## _ ## __d ## _ ## __n ## _values

		vecf f_values;

		vecf values(natural_spline, 2, uniform);
		vecf values(clamped, 2, uniform);
		vecf values(natural_spline, 3, uniform);
		vecf values(clamped, 3, uniform);
		vecf values(cubic, 3, uniform);

#define push(__b, __d, __n, __val) values(__b, __d, __n).push_back(spline(__b, __d, __n)(__val))

		for (flt x = a; x < b; x += (flt)0.001) {
			xs.push_back(x);

			f_values.push_back(f(x));

			push(natural_spline, 2, uniform, x);
			push(clamped, 2, uniform, x);
			push(natural_spline, 3, uniform, x);
			push(clamped, 3, uniform, x);
			push(cubic, 3, uniform, x);

#if not NOFILE
			result_file << std::format(
				"{}\t{}\t{}\t{}\t{}\t{}\t{}\n",
				x,
				f_values.back(),
				values(natural_spline, 2, uniform).back(),
				values(clamped, 2, uniform).back(),
				values(natural_spline, 3, uniform).back(),
				values(clamped, 3, uniform).back(),
				values(cubic, 3, uniform).back()
			);
#endif
		}
		xs.push_back(b);

		f_values.push_back(f(b));

		push(natural_spline, 2, uniform, b);
		push(clamped, 2, uniform, b);
		push(natural_spline, 3, uniform, b);
		push(clamped, 3, uniform, b);
		push(cubic, 3, uniform, b);
#if not NOFILE
		result_file << std::format(
			"{}\t{}\t{}\t{}\t{}\t{}\t{}\n",
			b,
			f_values.back(),
			values(natural_spline, 2, uniform).back(),
			values(clamped, 2, uniform).back(),
			values(natural_spline, 3, uniform).back(),
			values(clamped, 3, uniform).back(),
			values(cubic, 3, uniform).back()
		);
#endif
#if not NOPLOT

#define sett(__b, __d) __b ## _ ## __d ## _sett

		auto f_sett = settings{
			.color = {0, 191, 0},
			.name = "funkcja",
			.line = "-",
			.size = 1
		};
		auto sett(natural_spline, 2) = settings{
			.color = {0, 0, 191},
			.name = "natural spline 2gi st.",
			.line = "-",
			.size = 1
		};
		auto sett(natural_spline, 3) = settings{
			.color = {0, 110, 191},
			.name = "natural spline 3ci st.",
			.line = "-",
			.size = 2
		};
		auto sett(clamped, 2) = settings{
			.color = {191, 0, 0},
			.name = "clamped 2gi st.",
			.line = "-",
			.size = 1
		};
		auto sett(clamped, 3) = settings{
			.color = {191, 110, 0},
			.name = "clamped 3ci st.",
			.line = "-",
			.size = 2
		};
		auto sett(cubic, 3) = settings{
			.color = {191, 0, 191},
			.name = "cubic 3ci st.",
			.line = "-",
			.size = 2
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

		auto axes_uniform_2 = plt::makePlotAxes();
		auto axes_uniform_3 = plt::makePlotAxes();
		auto axes_uniform_mixed = plt::makePlotAxes();
		auto axes_error_uniform_2 = plt::makePlotAxes();
		auto axes_error_uniform_3 = plt::makePlotAxes();
		auto axes_error_uniform_mixed = plt::makePlotAxes();

		axes_uniform_2.xLabel("x").yLabel("y").title("Interpolacje dla " + std::to_string(nodes_count) + " wezlow jednorodnych");
		axes_uniform_3.xLabel("x").yLabel("y").title("Interpolacje dla " + std::to_string(nodes_count) + " wezlow jednorodnych");
		axes_uniform_mixed.xLabel("x").yLabel("y").title("Interpolacje dla " + std::to_string(nodes_count) + " wezlow jednorodnych");
		axes_error_uniform_2.xLabel("x").yLabel("y").title("Blad bezwzgledny interpolacji dla " + std::to_string(nodes_count) + " wezlow jednorodnych");
		axes_error_uniform_3.xLabel("x").yLabel("y").title("Blad bezwzgledny interpolacji dla " + std::to_string(nodes_count) + " wezlow jednorodnych");
		axes_error_uniform_mixed.xLabel("x").yLabel("y").title("Blad bezwzgledny interpolacji dla " + std::to_string(nodes_count) + " wezlow jednorodnych");

#endif

#define err_values(__b, __d, __n) __b ## _ ## __d ## _ ## __n ## _error_values
#define get_err_values(__b, __d, __n) error::abs(f, spline(__b, __d, __n), xs)

		auto err_values(natural_spline, 2, uniform) = get_err_values(natural_spline, 2, uniform);
		auto err_values(clamped, 2, uniform) = get_err_values(clamped, 2, uniform);
		auto err_values(natural_spline, 3, uniform) = get_err_values(natural_spline, 3, uniform);
		auto err_values(clamped, 3, uniform) = get_err_values(clamped, 3, uniform);
		auto err_values(cubic, 3, uniform) = get_err_values(cubic, 3, uniform);

#if not NOFILE

		std::ofstream error_file("interpolation_results/spline/error_" + std::to_string(nodes_count) + ".txt");
		error_file <<
			"x\t"
			tostring(spline(natural_spline, 2, uniform))
			"\t"
			tostring(spline(clamped, 2, uniform))
			"\t"
			tostring(spline(natural_spline, 3, uniform))
			"\t"
			tostring(spline(clamped, 3, uniform))
			"\t"
			tostring(spline(cubic, 3, uniform))
			"\n";

		for (size_t i = 0; i != xs.size(); ++i) {
			error_file << std::format(
				"{}\t{}\t{}\t{}\t{}\t{}\t{}\n",
				xs[i],
				f_values[i],
				err_values(natural_spline, 2, uniform)[i],
				err_values(clamped, 2, uniform)[i],
				err_values(natural_spline, 3, uniform)[i],
				err_values(clamped, 3, uniform)[i],
				err_values(cubic, 3, uniform)[i]
			);
		}

#define err_push(__b, __d, __n) \
max_abs_values(__b, __d, __n).push_back(error::max(err_values(__b, __d, __n))); \
sum_squared_values(__b, __d, __n).push_back(error::sum_squared(err_values(__b, __d, __n)))

		err_push(natural_spline, 2, uniform);
		err_push(clamped, 2, uniform);
		err_push(natural_spline, 3, uniform);
		err_push(clamped, 3, uniform);
		err_push(cubic, 3, uniform);

		max_abs_file << std::format(
			"{}\t{}\t{}\t{}\t{}\t{}\n",
			nodes_count,
			max_abs_values(natural_spline, 2, uniform).back(),
			max_abs_values(clamped, 2, uniform).back(),
			max_abs_values(natural_spline, 3, uniform).back(),
			max_abs_values(clamped, 3, uniform).back(),
			max_abs_values(cubic, 3, uniform).back()
		);

		sum_squared_file << std::format(
			"{}\t{}\t{}\t{}\t{}\t{}\n",
			nodes_count,
			sum_squared_values(natural_spline, 2, uniform).back(),
			sum_squared_values(clamped, 2, uniform).back(),
			sum_squared_values(natural_spline, 3, uniform).back(),
			sum_squared_values(clamped, 3, uniform).back(),
			sum_squared_values(cubic, 3, uniform).back()
		);
#endif

#if not NOPLOT

#pragma region axes series and settings

#define series(__b, __d, __n) auto&& __b ## _ ## __d ## _ ## __n ## _series = axes_ ## __n ## _ ## __d.create<plt::Series>( \
		xs, \
		values(__b, __d, __n), \
		sett(__b, __d).line \
		) \
		.setColor(sett(__b, __d).color) \
		.setLineWidth(sett(__b, __d).size) \
		.setName(sett(__b, __d).name) 
#define error_series(__b, __d, __n) auto&& __b ## _ ## __d ## _ ## __n ## _error_series = axes_error_ ## __n ## _ ## __d.create<plt::Series>( \
		xs, \
		err_values(__b, __d, __n), \
		sett(__b, __d).line \
		) \
		.setColor(sett(__b, __d).color) \
		.setLineWidth(sett(__b, __d).size) \
		.setName(sett(__b, __d).name) 

#define series_mixed(__b, __d, __n) auto&& __b ## _ ## __d ## _ ## __n ## _series_mixed = axes_ ## __n ## _mixed.create<plt::Series>( \
		xs, \
		values(__b, __d, __n), \
		sett(__b, __d).line \
		) \
		.setColor(sett(__b, __d).color) \
		.setLineWidth(sett(__b, __d).size) \
		.setName(sett(__b, __d).name) 
#define error_series_mixed(__b, __d, __n) auto&& __b ## _ ## __d ## _ ## __n ## _error_series_mixed = axes_error_ ## __n ## _mixed.create<plt::Series>( \
		xs, \
		err_values(__b, __d, __n), \
		sett(__b, __d).line \
		) \
		.setColor(sett(__b, __d).color) \
		.setLineWidth(sett(__b, __d).size) \
		.setName(sett(__b, __d).name) 


		auto&& f_uniform_series_2 = axes_uniform_2.create<plt::Series>(xs, f_values, f_sett.line)
			.setColor(f_sett.color)
			.setLineWidth(f_sett.size)
			.setName(f_sett.name);
		auto&& f_uniform_series_3 = axes_uniform_3.create<plt::Series>(xs, f_values, f_sett.line)
			.setColor(f_sett.color)
			.setLineWidth(f_sett.size)
			.setName(f_sett.name);
		auto&& f_uniform_series_mixed = axes_uniform_mixed.create<plt::Series>(xs, f_values, f_sett.line)
			.setColor(f_sett.color)
			.setLineWidth(f_sett.size)
			.setName(f_sett.name);

		series(natural_spline, 3, uniform);
		series(clamped, 3, uniform);
		series(cubic, 3, uniform);
		series(natural_spline, 2, uniform);
		series(clamped, 2, uniform);

		series_mixed(natural_spline, 3, uniform);
		series_mixed(clamped, 3, uniform);
		series_mixed(cubic, 3, uniform);
		series_mixed(natural_spline, 2, uniform);
		series_mixed(clamped, 2, uniform);

		auto&& nodes_uniform_series_2 = axes_uniform_2.create<plt::Series>(nodes_uniform_xs, nodes_uniform_ys, nodes_sett.line)
			.setColor(nodes_sett.color)
			.setMarkerSize(nodes_sett.size)
			.setName(nodes_sett.name);
		auto&& nodes_uniform_series_3 = axes_uniform_3.create<plt::Series>(nodes_uniform_xs, nodes_uniform_ys, nodes_sett.line)
			.setColor(nodes_sett.color)
			.setMarkerSize(nodes_sett.size)
			.setName(nodes_sett.name);
		auto&& nodes_uniform_series_mixed = axes_uniform_mixed.create<plt::Series>(nodes_uniform_xs, nodes_uniform_ys, nodes_sett.line)
			.setColor(nodes_sett.color)
			.setMarkerSize(nodes_sett.size)
			.setName(nodes_sett.name);
		auto&& legend_uniform_2 = axes_uniform_2.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height)
			.setAxes(axes_uniform_2);
		auto&& legend_uniform_3 = axes_uniform_3.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height)
			.setAxes(axes_uniform_3);
		auto&& legend_uniform_mixed = axes_uniform_mixed.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height)
			.setAxes(axes_uniform_mixed);

		error_series(natural_spline, 3, uniform);
		error_series(clamped, 3, uniform);
		error_series(cubic, 3, uniform);
		error_series(natural_spline, 2, uniform);
		error_series(clamped, 2, uniform);

		error_series_mixed(natural_spline, 3, uniform);
		error_series_mixed(clamped, 3, uniform);
		error_series_mixed(cubic, 3, uniform);
		error_series_mixed(natural_spline, 2, uniform);
		error_series_mixed(clamped, 2, uniform);

		auto&& legend_error_uniform_2 = axes_error_uniform_2.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height_error)
			.setAxes(axes_error_uniform_2);
		auto&& legend_error_uniform_3 = axes_error_uniform_3.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height_error)
			.setAxes(axes_error_uniform_3);
		auto&& legend_error_uniform_mixed = axes_error_uniform_mixed.create<plt::Legend>()
			.setWidth(legend_width)
			.setHeigth(legend_height_error)
			.setAxes(axes_error_uniform_mixed);

#pragma endregion

		auto x_lim_mul = 1.5;

		axes_uniform_2.setXLim({a, b * x_lim_mul});
		axes_uniform_3.setXLim({a, b * x_lim_mul});
		axes_uniform_mixed.setXLim({a, b * x_lim_mul});
		axes_error_uniform_2.setXLim({a, b * x_lim_mul});
		axes_error_uniform_3.setXLim({a, b * x_lim_mul});
		axes_error_uniform_mixed.setXLim({a, b * x_lim_mul});

		cv::imwrite("interpolation_images/spline/uniform_2/" + std::to_string(nodes_count) + ".png", axes_uniform_2.render(window_height, window_width));
		cv::imwrite("interpolation_images/spline/uniform_3/" + std::to_string(nodes_count) + ".png", axes_uniform_3.render(window_height, window_width));
		cv::imwrite("interpolation_images/spline/uniform_mixed/" + std::to_string(nodes_count) + ".png", axes_uniform_mixed.render(window_height, window_width));
		cv::imwrite("interpolation_images/spline/error_uniform_2/" + std::to_string(nodes_count) + ".png", axes_error_uniform_2.render(window_height, window_width));
		cv::imwrite("interpolation_images/spline/error_uniform_3/" + std::to_string(nodes_count) + ".png", axes_error_uniform_3.render(window_height, window_width));
		cv::imwrite("interpolation_images/spline/error_uniform_mixed/" + std::to_string(nodes_count) + ".png", axes_error_uniform_mixed.render(window_height, window_width));

#endif

	}

#if not NOPLOT

	auto axes_max_abs = plt::makePlotAxes();
	auto axes_sum_squared = plt::makePlotAxes();

	legend_width = 250;

	axes_max_abs
		.xLabel("x")
		.yLabel("y")
		.title("Maksymalne bledy bezwzgledne dla wezlow rownoodleglych");
	axes_sum_squared
		.xLabel("x")
		.yLabel("y")
		.title("Sumy kwadratow bledow bezwzglednych dla wezlow rownoodleglych");

	while (not nodes_counts.empty() and nodes_counts.back() > 20) { // ograniczenie wykresu
		nodes_counts.pop_back();

		max_abs_values(natural_spline, 2, uniform).pop_back();
		max_abs_values(clamped, 2, uniform).pop_back();
		max_abs_values(natural_spline, 3, uniform).pop_back();
		max_abs_values(clamped, 3, uniform).pop_back();
		max_abs_values(cubic, 3, uniform).pop_back();

		sum_squared_values(natural_spline, 2, uniform).pop_back();
		sum_squared_values(clamped, 2, uniform).pop_back();
		sum_squared_values(natural_spline, 3, uniform).pop_back();
		sum_squared_values(clamped, 3, uniform).pop_back();
		sum_squared_values(cubic, 3, uniform).pop_back();
	}
	auto nodes_counts_flt = vecf(nodes_counts.begin(), nodes_counts.end());


	auto sett(natural_spline, 2) = settings{
		.color = {0, 0, 191},
		.name = "natural spline 2gi stopnien",
		.line = "-",
		.size = 1
	};
	auto sett(natural_spline, 3) = settings{
		.color = {0, 110, 191},
		.name = "natural spline 3ci stopnien",
		.line = "-",
		.size = 1
	};
	auto sett(clamped, 2) = settings{
		.color = {191, 0, 0},
		.name = "clamped 2gi stopnien",
		.line = "-",
		.size = 1
	};
	auto sett(clamped, 3) = settings{
		.color = {191, 110, 0},
		.name = "clamped 3ci stopnien",
		.line = "-",
		.size = 1
	};
	auto sett(cubic, 3) = settings{
		.color = {191, 0, 191},
		.name = "cubic 3ci stopnien",
		.line = "-",
		.size = 1
	};

#define max_abs_series(__b, __d, __n) auto&& __b ## _ ## __d ## _ ## __n ## _max_abs_series = axes_max_abs.create<plt::Series>( \
		nodes_counts_flt, \
		max_abs_values(__b, __d, __n), \
		sett(__b, __d).line \
		) \
		.setColor(sett(__b, __d).color) \
		.setLineWidth(sett(__b, __d).size) \
		.setName(sett(__b, __d).name) 

	max_abs_series(natural_spline, 3, uniform);
	max_abs_series(clamped, 3, uniform);
	max_abs_series(cubic, 3, uniform);
	max_abs_series(natural_spline, 2, uniform);
	max_abs_series(clamped, 2, uniform);
	auto&& legend_max_abs = axes_max_abs.create<plt::Legend>()
		.setWidth(legend_width)
		.setHeigth(legend_height)
		.setAxes(axes_max_abs);

#define sum_squared_series(__b, __d, __n) auto&& __b ## _ ## __d ## _ ## __n ## _sum_squared_series = axes_sum_squared.create<plt::Series>( \
		nodes_counts_flt, \
		sum_squared_values(__b, __d, __n), \
		sett(__b, __d).line \
		) \
		.setColor(sett(__b, __d).color) \
		.setLineWidth(sett(__b, __d).size) \
		.setName(sett(__b, __d).name) 

	sum_squared_series(natural_spline, 3, uniform);
	sum_squared_series(clamped, 3, uniform);
	sum_squared_series(cubic, 3, uniform);
	sum_squared_series(natural_spline, 2, uniform);
	sum_squared_series(clamped, 2, uniform);
	auto&& legend_sum_squared = axes_sum_squared.create<plt::Legend>()
		.setWidth(legend_width)
		.setHeigth(legend_height)
		.setAxes(axes_sum_squared);

	std::cout << cv::imwrite("interpolation_images/spline/max_abs.png", axes_max_abs.render(window_height, window_width)) << '\n';
	std::cout << cv::imwrite("interpolation_images/spline/sum_squared.png", axes_sum_squared.render(window_height, window_width)) << '\n';

#endif

}