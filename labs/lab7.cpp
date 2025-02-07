#include <iostream>
#include <fstream>
#include <format>
#include <roots.hpp>
#include <cmath>
#include <filesystem>
#include <Legend.hpp>
#include <CvPlot/cvplot.h>
#include <algorithm>
#include <ranges>
#include <sstream>
#include <nodes.hpp>
#include <future>

// pula wątków
class thread_pool {
public:
	thread_pool(size_t num_threads);
	~thread_pool();

	template<class Lambda>
	auto enqueue(Lambda&& l) -> std::future<typename std::invoke_result<Lambda>::type>;

private:
	std::vector<std::jthread> workers;
	std::queue<std::function<void()>> tasks;
	std::mutex queue_mutex;
	std::condition_variable condition;
	bool stop;
};

thread_pool::thread_pool(size_t num_threads) : stop(false) {
	for (size_t i = 0; i < num_threads; ++i) {
		workers.emplace_back([this] {
			for (;;) {
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> lock(this->queue_mutex);
					this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
					if (this->stop && this->tasks.empty()) return;
					task = this->tasks.front();
					this->tasks.pop();
				}
				task();
			}
		});
	}
}

template<class Lambda>
auto thread_pool::enqueue(Lambda&& l) -> std::future<typename std::invoke_result<Lambda>::type> {
	using return_type = typename std::invoke_result<Lambda>::type;

	auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<Lambda>(l)));

	std::future<return_type> res = task->get_future();
	{
		std::lock_guard<std::mutex> lock(queue_mutex);
		tasks.emplace([task]() { (*task)(); });
	}
	condition.notify_one();
	return res;
}

thread_pool::~thread_pool() {
	{
		std::lock_guard<std::mutex> lock(queue_mutex);
		stop = true;
	}
	condition.notify_all();
}

#ifdef NOPLOT
#undef NOPLOT
#define NOPLOT 1
#endif

#if not NOPLOT

namespace plt = CvPlot;

auto window_height = 400;
auto window_width = 600;

struct settings {
	cv::Scalar color;
	const std::string& name;
	const std::string& line;
	int size;
};

auto legend_width = 175;
auto legend_height = 75;
auto legend_height_error = 50;

#endif

static inline constexpr flt n = 15;
static inline constexpr flt m = 12;

flt f(flt x) {
	return pow(x, n) + pow(x, m);
}
flt df(flt x) {
	return n * pow(x, n - 1) + m * pow(x, m - 1);
}

// real roots are -1 and 0, trivial to show
static inline constexpr flt f_roots[] = {-1.0, 0};
flt dist_from_root(flt x) {
	flt result = std::numeric_limits<flt>::infinity();

	for (auto&& root : f_roots) {
		result = std::min(fabs(root - x), result);
	}

	return result;
}

static inline constexpr flt a = -1.2;
static inline constexpr flt b = 1.2;

#if not NOPLOT

void save_steps(const vecf& xs, const vecf& ys, const vecf& steps, const std::string& path) {
	auto steps_ys = steps;
	for (auto&& y : steps_ys) {
		y = f(y);
	}

	auto&& axes = plt::makePlotAxes();

	static auto f_sett = settings{
		.color = {0, 191, 0},
		.name = "f(x)",
		.line = "-",
		.size = 2
	};
	static auto nodes_sett = settings{
		.color = {0, 0, 255},
		.name = "wezly",
		.line = "o",
		.size = 3
	};

	auto&& series = axes.create<plt::Series>(xs, ys, f_sett.line)
		.setColor(f_sett.color)
		.setLineWidth(f_sett.size)
		.setName(f_sett.name);
	auto&& series_steps = axes.create<plt::Series>(steps, steps_ys, nodes_sett.line)
		.setColor(nodes_sett.color)
		.setMarkerSize(nodes_sett.size)
		.setName(nodes_sett.name);
	auto&& legend = axes.create<plt::Legend>()
		.setWidth(150)
		.setHeigth(50)
		.setAxes(axes);

	cv::imwrite(path, axes.render(window_height, window_width));
}

#endif

int main() {
	// pula wątków
	std::cout << std::format("using {} threads to save images\n", (std::thread::hardware_concurrency() - 1 == 0 ? 1 : std::thread::hardware_concurrency() - 1));
	auto tpool = thread_pool((std::thread::hardware_concurrency() - 1 == 0 ? 1 : std::thread::hardware_concurrency() - 1));
	std::vector<std::future<void>> images_futures;

	for (auto&& dir : {
		"roots_images/",
		"roots_images/newton/",
		"roots_images/secant/",
		"roots_results/",
		"roots_results/newton/",
		"roots_results/secant/",
		 }) {
		if (not std::filesystem::exists(dir)) {
			std::filesystem::create_directories(dir);
		}
	}

	auto&& xs = nodes::uniform(10000, a, b);
	auto ys = xs;
	for (auto&& y : ys) {
		y = f(y);
	};

	flt dx = 0.1;
	auto rhos = {
		1e-2,
		1e-3,
		1e-5,
		1e-7,
		1e-10,
		1e-12,
		1e-15,
	};

#if not NOFILE

	auto newton_dx_diff_file = std::ofstream("roots_results/newton/newton_dx_diff_file.txt");
	auto newton_dx_val_file = std::ofstream("roots_results/newton/newton_dx_val_file.txt");
	auto newton_dx_iter_file = std::ofstream("roots_results/newton/newton_dx_iter_file.txt");

	auto newton_val_diff_file = std::ofstream("roots_results/newton/newton_val_diff_file.txt");
	auto newton_val_val_file = std::ofstream("roots_results/newton/newton_val_val_file.txt");
	auto newton_val_iter_file = std::ofstream("roots_results/newton/newton_val_iter_file.txt");

	auto secant_a_dx_diff_file = std::ofstream("roots_results/secant/secant_a_dx_diff_file.txt");
	auto secant_a_dx_val_file = std::ofstream("roots_results/secant/secant_a_dx_val_file.txt");
	auto secant_a_dx_iter_file = std::ofstream("roots_results/secant/secant_a_dx_iter_file.txt");

	auto secant_a_val_diff_file = std::ofstream("roots_results/secant/secant_a_val_diff_file.txt");
	auto secant_a_val_val_file = std::ofstream("roots_results/secant/secant_a_val_val_file.txt");
	auto secant_a_val_iter_file = std::ofstream("roots_results/secant/secant_a_val_iter_file.txt");

	auto secant_b_dx_diff_file = std::ofstream("roots_results/secant/secant_b_dx_diff_file.txt");
	auto secant_b_dx_val_file = std::ofstream("roots_results/secant/secant_b_dx_val_file.txt");
	auto secant_b_dx_iter_file = std::ofstream("roots_results/secant/secant_b_dx_iter_file.txt");

	auto secant_b_val_diff_file = std::ofstream("roots_results/secant/secant_b_val_diff_file.txt");
	auto secant_b_val_val_file = std::ofstream("roots_results/secant/secant_b_val_val_file.txt");
	auto secant_b_val_iter_file = std::ofstream("roots_results/secant/secant_b_val_iter_file.txt");

#endif

	{
		auto file_header = std::format(
			"x_0\\rho"
		);
		for (auto&& rho : rhos) {
			file_header += std::format("\t{:.1e}", rho);
		}
		file_header += '\n';

#if not NOFILE

		newton_dx_diff_file << file_header;
		newton_dx_val_file << file_header;
		newton_dx_iter_file << file_header;

		newton_val_diff_file << file_header;
		newton_val_val_file << file_header;
		newton_val_iter_file << file_header;

		secant_a_dx_diff_file << "x_1\t" << file_header;
		secant_a_dx_val_file << "x_1\t" << file_header;
		secant_a_dx_iter_file << "x_1\t" << file_header;

		secant_a_val_diff_file << "x_1\t" << file_header;
		secant_a_val_val_file << "x_1\t" << file_header;
		secant_a_val_iter_file << "x_1\t" << file_header;

		secant_b_dx_diff_file << "x_1\t" << file_header;
		secant_b_dx_val_file << "x_1\t" << file_header;
		secant_b_dx_iter_file << "x_1\t" << file_header;

		secant_b_val_diff_file << "x_1\t" << file_header;
		secant_b_val_val_file << "x_1\t" << file_header;
		secant_b_val_iter_file << "x_1\t" << file_header;

#endif

		std::cout << file_header;
	}

	flt x_0s[] = {
		-1.2,
		-1.1,
		-1.0,
		-0.9,
		-0.8,
		-0.7,
		-0.6,
		-0.5,
		-0.4,
		-0.3,
		-0.2,
		-0.1,
		0.0,
		0.1,
		0.2,
		0.3,
		0.4,
		0.5,
		0.6,
		0.7,
		0.8,
		0.9,
		1.0,
		1.1,
	};


	for (auto&& x_0 : x_0s) {

#if not NOFILE

		newton_dx_diff_file << std::format("{:.1f}", x_0);
		newton_dx_val_file << std::format("{:.1f}", x_0);
		newton_dx_iter_file << std::format("{:.1f}", x_0);

		newton_val_diff_file << std::format("{:.1f}", x_0);
		newton_val_val_file << std::format("{:.1f}", x_0);
		newton_val_iter_file << std::format("{:.1f}", x_0);

		secant_a_dx_diff_file << std::format("{:.1f}\t", a) << std::format("{:.1f}", b - x_0 + a);
		secant_a_dx_val_file << std::format("{:.1f}\t", a) << std::format("{:.1f}", b - x_0 + a);
		secant_a_dx_iter_file << std::format("{:.1f}\t", a) << std::format("{:.1f}", b - x_0 + a);

		secant_a_val_diff_file << std::format("{:.1f}\t", a) << std::format("{:.1f}", b - x_0 + a);
		secant_a_val_val_file << std::format("{:.1f}\t", a) << std::format("{:.1f}", b - x_0 + a);
		secant_a_val_iter_file << std::format("{:.1f}\t", a) << std::format("{:.1f}", b - x_0 + a);

		secant_b_dx_diff_file << std::format("{:.1f}\t", b) << std::format("{:.1f}", x_0);
		secant_b_dx_val_file << std::format("{:.1f}\t", b) << std::format("{:.1f}", x_0);
		secant_b_dx_iter_file << std::format("{:.1f}\t", b) << std::format("{:.1f}", x_0);

		secant_b_val_diff_file << std::format("{:.1f}\t", b) << std::format("{:.1f}", x_0);
		secant_b_val_val_file << std::format("{:.1f}\t", b) << std::format("{:.1f}", x_0);
		secant_b_val_iter_file << std::format("{:.1f}\t", b) << std::format("{:.1f}", x_0);

#endif

		std::cout << std::format("{:.1f}", x_0);

		for (auto&& rho : rhos) {
			auto&& [newton_iters_vals_dx, newton_iters_dx] = roots::newton(f, df, x_0, a, b, rho, roots::stop::predicate::dx);
			auto&& [newton_iters_vals_val, newton_iters_val] = roots::newton(f, df, x_0, a, b, rho, roots::stop::predicate::val);

			auto&& [secant_a_iters_vals_dx, secant_a_iters_dx] = roots::secant(f, b - x_0 + a, a, a, b, rho, roots::stop::predicate::dx);
			auto&& [secant_a_iters_vals_val, secant_a_iters_val] = roots::secant(f, b - x_0 + a, a, a, b, rho, roots::stop::predicate::val);
			auto&& [secant_b_iters_vals_dx, secant_b_iters_dx] = roots::secant(f, x_0, b, a, b, rho, roots::stop::predicate::dx);
			auto&& [secant_b_iters_vals_val, secant_b_iters_val] = roots::secant(f, x_0, b, a, b, rho, roots::stop::predicate::val);

#if not NOFILE

			newton_dx_diff_file << std::format("\t{1:.{0}f}", DBL_DIG, dist_from_root(newton_iters_vals_dx.back()));
			newton_dx_val_file << std::format("\t{1:.{0}f}", DBL_DIG, newton_iters_vals_dx.back());
			newton_dx_iter_file << std::format("\t{}", newton_iters_dx == (size_t)-1 ? -1 : (int)newton_iters_dx);

			newton_val_diff_file << std::format("\t{1:.{0}f}", DBL_DIG, dist_from_root(newton_iters_vals_val.back()));
			newton_val_val_file << std::format("\t{1:.{0}f}", DBL_DIG, newton_iters_vals_val.back());
			newton_val_iter_file << std::format("\t{}", newton_iters_val == (size_t)-1 ? -1 : (int)newton_iters_val);

			secant_a_dx_diff_file << std::format("\t{1:.{0}f}", DBL_DIG, dist_from_root(secant_a_iters_vals_dx.back()));
			secant_a_dx_val_file << std::format("\t{1:.{0}f}", DBL_DIG, secant_a_iters_vals_dx.back());
			secant_a_dx_iter_file << std::format("\t{}", secant_a_iters_dx == (size_t)-1 ? -1 : (int)secant_a_iters_dx);

			secant_a_val_diff_file << std::format("\t{1:.{0}f}", DBL_DIG, dist_from_root(secant_a_iters_vals_val.back()));
			secant_a_val_val_file << std::format("\t{1:.{0}f}", DBL_DIG, secant_a_iters_vals_val.back());
			secant_a_val_iter_file << std::format("\t{}", secant_a_iters_val == (size_t)-1 ? -1 : (int)secant_a_iters_val);

			secant_b_dx_diff_file << std::format("\t{1:.{0}f}", DBL_DIG, dist_from_root(secant_b_iters_vals_dx.back()));
			secant_b_dx_val_file << std::format("\t{1:.{0}f}", DBL_DIG, secant_b_iters_vals_dx.back());
			secant_b_dx_iter_file << std::format("\t{}", secant_b_iters_dx == (size_t)-1 ? -1 : (int)secant_b_iters_dx);

			secant_b_val_diff_file << std::format("\t{1:.{0}f}", DBL_DIG, dist_from_root(secant_b_iters_vals_val.back()));
			secant_b_val_val_file << std::format("\t{1:.{0}f}", DBL_DIG, secant_b_iters_vals_val.back());
			secant_b_val_iter_file << std::format("\t{}", secant_b_iters_val == (size_t)-1 ? -1 : (int)secant_b_iters_val);

#endif

#if not NOPLOT

			images_futures.emplace_back(tpool.enqueue([&xs, &ys, newton_iters_vals_dx = std::move(newton_iters_vals_dx), x_0 = x_0, rho = rho]() {
				save_steps(xs, ys, newton_iters_vals_dx, std::format("roots_images/newton/newton_iters_dx_{:.1f}_{:.1f}.png", x_0, rho));
			}));
			images_futures.emplace_back(tpool.enqueue([&xs, &ys, newton_iters_vals_val = std::move(newton_iters_vals_val), x_0 = x_0, rho = rho]() {
				save_steps(xs, ys, newton_iters_vals_val, std::format("roots_images/newton/newton_iters_val_{:.1f}_{:.1e}.png", x_0, rho));
			}));
			images_futures.emplace_back(tpool.enqueue([&xs, &ys, secant_a_iters_vals_dx = std::move(secant_a_iters_vals_dx), x_0 = x_0, rho = rho]() {
				save_steps(xs, ys, secant_a_iters_vals_dx, std::format("roots_images/secant/secant_a_iters_dx_{:.1f}_{:.1e}.png", b - x_0 + a, rho));
			}));
			images_futures.emplace_back(tpool.enqueue([&xs, &ys, secant_a_iters_vals_val = std::move(secant_a_iters_vals_val), x_0 = x_0, rho = rho]() {
				save_steps(xs, ys, secant_a_iters_vals_val, std::format("roots_images/secant/secant_a_iters_val_{:.1f}_{:.1e}.png", b - x_0 + a, rho));
			}));
			images_futures.emplace_back(tpool.enqueue([&xs, &ys, secant_b_iters_vals_dx = std::move(secant_b_iters_vals_dx), x_0 = x_0, rho = rho]() {
				save_steps(xs, ys, secant_b_iters_vals_dx, std::format("roots_images/secant/secant_b_iters_dx_{:.1f}_{:.1e}.png", x_0, rho));
			}));
			images_futures.emplace_back(tpool.enqueue([&xs, &ys, secant_b_iters_vals_val = std::move(secant_b_iters_vals_val), x_0 = x_0, rho = rho]() {
				save_steps(xs, ys, secant_b_iters_vals_val, std::format("roots_images/secant/secant_b_iters_val_{:.1f}_{:.1e}.png", x_0, rho));
			}));

#endif

			std::cout << "\tOK";
		}

#if not NOFILE

		newton_dx_diff_file << '\n';
		newton_dx_val_file << '\n';
		newton_dx_iter_file << '\n';

		newton_val_diff_file << '\n';
		newton_val_val_file << '\n';
		newton_val_iter_file << '\n';

		secant_a_dx_diff_file << '\n';
		secant_a_dx_val_file << '\n';
		secant_a_dx_iter_file << '\n';

		secant_a_val_diff_file << '\n';
		secant_a_val_val_file << '\n';
		secant_a_val_iter_file << '\n';

		secant_b_dx_diff_file << '\n';
		secant_b_dx_val_file << '\n';
		secant_b_dx_iter_file << '\n';

		secant_b_val_diff_file << '\n';
		secant_b_val_val_file << '\n';
		secant_b_val_iter_file << '\n';

#endif

		std::cout << '\n';
	}
	{
		flt x_0 = b;

#if not NOFILE

		newton_dx_diff_file << std::format("{:.1f}", x_0);
		newton_dx_val_file << std::format("{:.1f}", x_0);
		newton_dx_iter_file << std::format("{:.1f}", x_0);

		newton_val_diff_file << std::format("{:.1f}", x_0);
		newton_val_val_file << std::format("{:.1f}", x_0);
		newton_val_iter_file << std::format("{:.1f}", x_0);

#endif

		std::cout << std::format("{:.1f}", x_0);

		for (auto&& rho : rhos) {
			auto&& [iters_vals_dx, iters_dx] = roots::newton(f, df, x_0, a, b, rho, roots::stop::predicate::dx);
			auto&& [iters_vals_val, iters_val] = roots::newton(f, df, x_0, a, b, rho, roots::stop::predicate::val);


#if not NOFILE

			newton_dx_diff_file << std::format("\t{1:.{0}f}", DBL_DIG, dist_from_root(iters_vals_dx.back()));
			newton_dx_val_file << std::format("\t{1:.{0}f}", DBL_DIG, iters_vals_dx.back());
			newton_dx_iter_file << std::format("\t{}", iters_dx == (size_t)-1 ? -1 : (int)iters_dx);

			newton_val_diff_file << std::format("\t{1:.{0}f}", DBL_DIG, dist_from_root(iters_vals_val.back()));
			newton_val_val_file << std::format("\t{1:.{0}f}", DBL_DIG, iters_vals_val.back());
			newton_val_iter_file << std::format("\t{}", iters_val == (size_t)-1 ? -1 : (int)iters_val);

#endif

#if not NOPLOT

			images_futures.emplace_back(tpool.enqueue([&xs, &ys, iters_vals_dx = std::move(iters_vals_dx), x_0 = x_0, rho = rho]() {
				save_steps(xs, ys, iters_vals_dx, std::format("roots_images/newton/newton_iters_dx_{:.1f}_{:.1e}.png", x_0, rho));
			}));
			images_futures.emplace_back(tpool.enqueue([&xs, &ys, iters_vals_val = std::move(iters_vals_val), x_0 = x_0, rho = rho]() {
				save_steps(xs, ys, iters_vals_val, std::format("roots_images/newton/newton_iters_val_{:.1f}_{:.1e}.png", x_0, rho));
			}));

#endif

			std::cout << "\tOK";
		}

#if not NOFILE

		newton_dx_diff_file << '\n';
		newton_dx_val_file << '\n';
		newton_dx_iter_file << '\n';

		newton_val_diff_file << '\n';
		newton_val_val_file << '\n';
		newton_val_iter_file << '\n';

#endif

		std::cout << '\n';
	}

	for (size_t i = 0; i != images_futures.size(); ++i) {
		images_futures[i].wait();

		std::cout << std::format("\rsaved {}/{} images", i, images_futures.size());
	}
	std::cout << '\n';
	images_futures.clear();
}