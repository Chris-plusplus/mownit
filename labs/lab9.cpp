#include <iostream>
#include <sstream>
#include <format>
#include <random>
#include <fstream>
#include <thread>
#include <future>
#include <queue>
#include <armadillo>
#include <matrix/jacobi.hpp>

#ifdef _MSC_VER
#pragma runtime_checks( "", off )
#endif

class thread_pool {
public:
	inline thread_pool(size_t num_threads);
	inline ~thread_pool();

	template<class Lambda>
	inline auto enqueue(Lambda&& l) -> std::future<typename std::invoke_result<Lambda>::type>;

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

constexpr int k = 10;
constexpr int m = 3;

inline arma::mat create_matrix(size_t n) noexcept {
	arma::Mat<f64> x;
	auto matrix = arma::mat(n, n, arma::fill::zeros);
	for (size_t i = 1; i <= n; ++i) {
		matrix.at(i - 1, i - 1) = k;
		auto val = (f64)m / (f64)i;
		if (i != 1) {
			matrix.at(i - 1, i - 2) = val;
		}
		for (size_t j = i + 1; j <= n; ++j) {
			matrix.at(i - 1, j - 1) = (j % 2 == 0 ? (f64)m / (f64)j : -(f64)m / (f64)j);
		}
	}

	return matrix;
}

inline f64 spectral_radius(const arma::mat& A) noexcept {
	size_t n = A.n_rows;

	arma::mat B = arma::diagmat(A.diag());
	arma::mat I = arma::eye(n, n);

	arma::mat M = I - B.i() * A;

	return arma::abs(arma::eig_gen(M)).max();
}

int main() {
	using sc = matrix::stop_criterion;
	namespace chr = std::chrono;

	std::cout << "sr/jcb: ";
	std::string in;
	std::cin >> in;

	if (in == "jcb") {

		size_t limit;
		std::cout << "limit: ";
		std::cin >> limit;

		auto rhos = std::vector{
			1e-3,
			1e-5,
			1e-7,
			1e-10,
			1e-15
		};

		std::string file_header = "n\\rho";
		for (auto&& rho : rhos) {
			file_header += std::format("\t{:.0e}", rho);
		}

		std::map<std::tuple<std::string, sc, std::string>, std::ofstream> files;
		for (auto&& type : {"err", "iters", "time"}) {
			for (auto&& stop_criterion : {sc::step, sc::value}) {
				for (auto&& vec_type : {"start_nonzero", "start_zero"}) {
					files[{type, stop_criterion, vec_type}] = std::ofstream(std::format(
						"{}_sc_{}_{}.txt",
						type,
						stop_criterion == sc::step ? "step" : "value",
						vec_type
					));
				}
			}
		}

		for (auto&& [key, file] : files) {
			file << file_header << '\n';
		}
		std::cout << file_header << '\n';

		for (size_t n = 2; n <= limit; n += (n < 100 ? 1 : (n < 250 ? 10 : (n < 500 ? 25 : 50)))) {
			auto A = create_matrix(n);

			auto x = arma::vec(n);
			x.at(0) = 1;
			for (size_t i = 1; i != n; ++i) {
				x.at(i) = -x.at(i - 1);
			}

			auto start_nonzero = arma::vec(n);
			for (size_t i = 0; i != n; ++i) {
				start_nonzero.at(i) = (i % 2 == 0 ? 100.0 : -100.0);
			}
			auto start_zero = arma::vec(n);
			for (auto&& x_i : start_zero) {
				start_zero = 0.0;
			}

			auto b = A * x;

			for (auto&& stop_criterion : {sc::step, sc::value}) {
				for (auto&& vec_type : {&start_nonzero, &start_zero}) {
					auto&& err_file = files[{"err", stop_criterion, vec_type == &start_nonzero ? "start_nonzero" : "start_zero"}];
					auto&& iters_file = files[{"iters", stop_criterion, vec_type == &start_nonzero ? "start_nonzero" : "start_zero"}];
					auto&& time_file = files[{"time", stop_criterion, vec_type == &start_nonzero ? "start_nonzero" : "start_zero"}];

					for (auto&& type : {"err", "iters", "time"}) {
						files[{type, stop_criterion, vec_type == &start_nonzero ? "start_nonzero" : "start_zero"}] << std::format("{}", n);
					}
					std::cout << std::format("{}", n);
					std::cout << std::format(":{:.0f}", (*vec_type).at(0));
					for (auto&& rho : rhos) {
						auto&& [time, result, iters] = matrix::jacobi(A, b, *vec_type, stop_criterion, rho);

						auto err_vec = arma::abs(x - result);
						auto err = arma::norm(err_vec);

						auto time_ms = (f64)chr::duration_cast<chr::nanoseconds>(time).count() * 1e-6;

						err_file << std::format("\t{}", err);
						iters_file << (iters == (size_t)-1 ? std::format("\t{}", std::nan("")) : std::format("\t{}", iters));
						time_file << std::format("\t{:.3f}", time_ms);
						std::cout << std::format("\t{:.3f}", time_ms);
					}

					for (auto&& type : {"err", "iters", "time"}) {
						files[{type, stop_criterion, vec_type == &start_nonzero ? "start_nonzero" : "start_zero"}] << '\n';
					}
					std::cout << '\n';
				}
			}
		}
	}
	else if (in == "sr") {
		std::cout << "limit: ";
		size_t limit;
		std::cin >> limit;

		auto file = std::ofstream("spectral_radius.txt");
		auto tp = thread_pool(std::thread::hardware_concurrency() - 1);
		std::cout << std::format("working on {} threads\n", std::thread::hardware_concurrency() - 1);

		file << std::format("n\tsr\n");
		std::cout << std::format("n\tsr\n");

		auto srs = vec<f64>(limit - 1);
		auto futures = vec<std::future<void>>(limit - 1);

		for (size_t n = 2; n <= limit; ++n) {
			futures[n - 2] = tp.enqueue([n, &srs]() {
				auto A = create_matrix(n);
				srs[n - 2] = spectral_radius(A);
				//std::cout << std::format("{}\t{}\n", n, srs[n - 1]);
			});
		}

		for (size_t i = 0; i != futures.size(); ++i) {
			futures[i].wait();
			file << std::format("{}\t{}\n", i + 1, srs[i]);
			std::cout << std::format("{}\t{}\n", i + 1, srs[i]);
		}
	}
}