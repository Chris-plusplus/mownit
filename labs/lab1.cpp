#include <vector>
#include <format>
#include <cfloat>
#include <fstream>
#include <iostream>

template<class F>
struct init_value_pair {
	bool initialized;
	F value;

	init_value_pair() :
		initialized{false},
		value{(F)0} {}
	init_value_pair(F val) :
		initialized{true},
		value{val} {}
};

template<class F>
static F a = (F)3;

static void set_a(float new_a) {
	a<float> = new_a;
	a<double> = new_a;
	a<long double> = new_a;
}

static inline constexpr std::size_t k = 45;

namespace fwd {
template<class F>
static auto init_x() {
	auto to_return = std::vector<init_value_pair<F>>(k + 2);

	to_return[0] = {(F)1};
	to_return[1] = {(F)1 / a<F>};

	return to_return;
}

template<class F>
static auto x = init_x<F>();

static void reset() {
	x<float> = init_x<float>();
	x<double> = init_x<double>();
	x<long double> = init_x<long double>();
}

template<class F>
static F& get_x(std::size_t k) {
	if (not x<F>[k].initialized) {
		x<F>[k] = {(F)10 / a<F> * get_x<F>(k - 1) - get_x<F>(k - 2)};
	}

	return x<F>[k].value;
}
}

namespace bwd {
template<class F>
static auto init_x() {
	fwd::x<F> = fwd::init_x<F>();

	auto to_return = std::vector<init_value_pair<F>>(k + 2);

	to_return[k] = {fwd::get_x<F>(k)};
	to_return[k + 1] = {fwd::get_x<F>(k + 1)};

	return to_return;
}

template<class F>
static std::vector<init_value_pair<F>> x;

static void reset() {
	x<float> = init_x<float>();
	x<double> = init_x<double>();
	x<long double> = init_x<long double>();
}

template<class F>
static F& get_x(std::size_t k) {
	if (not x<F>[k].initialized) {
		x<F>[k] = {(F)10 / a<F> * get_x<F>(k + 1) - get_x<F>(k + 2)};
	}

	return x<F>[k].value;
}
}

int main() {
	std::cout << std::format(
		"Równanie: a*x[k-1] - 10*x[k] + a*x[k+1] = 0\n"
		"Zgodność ze standardem IEEE 754:\n"
		"    float:       {16}\n"
		"    double:      {17}\n"
		"    long double: {18}\n"
		"Rozmiary typów zmiennoprzecinkowych (w bajtach):\n"
		"    sizeof(float)       = {13}\n"
		"    sizeof(double)      = {14}\n"
		"    sizeof(long double) = {15}\n"
		"Dokładność typów zmiennoprzecinkowych (w miejscach po przecinku):\n"
		"    float:       {1}\n"
		"    double:      {2}\n"
		"    long double: {3}\n"
		"Parametry początkowe:\n"
		"    k = {0}\n"
		"    float:\n"
		"        a    = {4:.{1}f}\n"
		"        x[0] = {5:.{1}f}\n"
		"        x[1] = {6:.{1}f}\n"
		"    double:\n"
		"        a    = {7:.{2}f}\n"
		"        x[0] = {8:.{2}f}\n"
		"        x[1] = {9:.{2}f}\n"
		"    long double:\n"
		"        a    = {10:.{3}f}\n"
		"        x[0] = {11:.{3}f}\n"
		"        x[1] = {12:.{3}f}\n",
		k,
		FLT_DIG,
		DBL_DIG,
		LDBL_DIG,
		a<float>,
		fwd::get_x<float>(0),
		fwd::get_x<float>(1),
		a<double>,
		fwd::get_x<double>(0),
		fwd::get_x<double>(1),
		a<long double>,
		fwd::get_x<long double>(0),
		fwd::get_x<long double>(1),
		sizeof(float), sizeof(double), sizeof(long double),
		std::numeric_limits<float>::is_iec559,
		std::numeric_limits<double>::is_iec559,
		std::numeric_limits<long double>::is_iec559
	) << '\n';

	std::cout << "Wartości kolejnych xn dla a = 3\n";

	std::cout << "float:\n";
	for (size_t i = 0; i != 47; ++i) {
		std::cout << std::format("\tx{0}\t= {1:.{2}f}\n", i, fwd::get_x<float>(i), FLT_DIG);
	}

	std::cout << "double:\n";
	for (size_t i = 0; i != 47; ++i) {
		std::cout << std::format("\tx{0}\t= {1:.{2}f}\n", i, fwd::get_x<double>(i), DBL_DIG);
	}

	std::cout << "long double:\n";
	for (size_t i = 0; i != 47; ++i) {
		std::cout << std::format("\tx{0}\t= {1:.{2}f}\n", i, fwd::get_x<long double>(i), LDBL_DIG);
	}
	std::cout << '\n';

	std::cout << std::format(
		"Wartości x[k] i x[k+1] liczone rekurencyjnie w przód:\n"
		"    float:\n"
		"        x[k]   = {3:.{0}f}\n"
		"        x[k+1] = {4:.{0}f}\n"
		"    double:\n"
		"        x[k]   = {5:.{1}f}\n"
		"        x[k+1] = {6:.{1}f}\n"
		"    long double:\n"
		"        x[k]   = {7:.{2}f}\n"
		"        x[k+1] = {8:.{2}f}\n",
		FLT_DIG,
		DBL_DIG,
		LDBL_DIG,
		fwd::get_x<float>(k),
		fwd::get_x<float>(k + 1),
		fwd::get_x<double>(k),
		fwd::get_x<double>(k + 1),
		fwd::get_x<long double>(k),
		fwd::get_x<long double>(k + 1)
	) << '\n';

	bwd::reset();
	std::cout << std::format(
		"Wartości x[0] i x[1], liczone rekurencyjnie w tył:\n"
		"    float:\n"
		"        x[0] = {3:.{0}f}\n"
		"        x[1] = {4:.{0}f}\n"
		"    double:\n"
		"        x[0] = {5:.{1}f}\n"
		"        x[1] = {6:.{1}f}\n"
		"    long double:\n"
		"        x[0] = {7:.{2}f}\n"
		"        x[1] = {8:.{2}f}\n",
		FLT_DIG,
		DBL_DIG,
		LDBL_DIG,
		bwd::get_x<float>(0),
		bwd::get_x<float>(1),
		bwd::get_x<double>(0),
		bwd::get_x<double>(1),
		bwd::get_x<long double>(0),
		bwd::get_x<long double>(1)
	) << '\n';

	auto xn_str = std::string("n\tfloat\tdouble\tlong double\n");
	auto xk_str = std::string("a\tfloat\tdouble\tlong double\n");
	auto xkp1_str = std::string("a\tfloat\tdouble\tlong double\n");
	auto x0_str = std::string("a\tfloat\tdouble\tlong double\n");
	auto x1_str = std::string("a\tfloat\tdouble\tlong double\n");
	
	for (auto n = 0; n != 47; ++n) {
		xn_str += std::format(
			"{0}\t{1:.{4}f}\t{2:.{5}f}\t{3:.{6}f}\n",
			n,
			fwd::get_x<float>(n),
			fwd::get_x<double>(n),
			fwd::get_x<long double>(n),
			FLT_DIG,
			DBL_DIG,
			LDBL_DIG
		);
	}

	for (auto _a = 2; _a != 1001; ++_a) {
		set_a(_a);
		fwd::reset();
		bwd::reset();

		xk_str.append(std::format(
			"{6}\t{3:.{0}f}\t\{4:.{1}f}\t{5:.{2}f}\n",
			FLT_DIG,
			DBL_DIG,
			LDBL_DIG,

			fwd::get_x<float>(k),
			fwd::get_x<double>(k),
			fwd::get_x<long double>(k),

			_a
		));
		xkp1_str.append(std::format(
			"{6}\t{3:.{0}f}\t\{4:.{1}f}\t{5:.{2}f}\n",
			FLT_DIG,
			DBL_DIG,
			LDBL_DIG,

			fwd::get_x<float>(k + 1),
			fwd::get_x<double>(k + 1),
			fwd::get_x<long double>(k + 1),

			_a
		));

		x0_str.append(std::format(
			"{6}\t{3:.{0}f}\t\{4:.{1}f}\t{5:.{2}f}\n",
			FLT_DIG,
			DBL_DIG,
			LDBL_DIG,

			bwd::get_x<float>(0),
			bwd::get_x<double>(0),
			bwd::get_x<long double>(0),

			_a
		));
		x1_str.append(std::format(
			"{6}\t{3:.{0}f}\t\{4:.{1}f}\t{5:.{2}f}\n",
			FLT_DIG,
			DBL_DIG,
			LDBL_DIG,

			bwd::get_x<float>(1),
			bwd::get_x<double>(1),
			bwd::get_x<long double>(1),

			_a
		));
	}

	auto file = std::ofstream("xn.txt");
	file << xn_str;

	file = std::ofstream("xk.txt");
	file << xk_str;

	file = std::ofstream("xkp1.txt");
	file << xkp1_str;

	file = std::ofstream("x0.txt");
	file << x0_str;

	file = std::ofstream("x1.txt");
	file << x1_str;
}