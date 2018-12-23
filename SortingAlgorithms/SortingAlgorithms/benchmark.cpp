#include "benchmark.h"
#include "sort.h"
#include <random>


//Selection, Bubble, Shaker, Insertion, Shell, Quick, Heap, Merge, NumOfSorts

void(*benchmark_int::sort_func[gui::NumOfSorts])(std::vector<int>&, bool(*cmp)(const int&, const int&)) =
{
	sorting::selection_sort,
	sorting::bubble_sort,
	sorting::shaker_sort,
	sorting::insertion_sort,
	sorting::shell_sort,
	sorting::quick_sort,
	sorting::heap_sort,
	sorting::merge_sort
};

std::vector<std::vector<int>> benchmark_int::test_vectors;

std::vector<double> benchmark_int::runtime = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

void benchmark_int::init_test_vectors(const int n, const int few_sorted_param, const int nearly_sorted_param) {
	std::vector<int> test_vec_random;
	std::vector<int> test_vec_nearly_sorted;
	std::vector<int> test_vec_sorted;
	std::vector<int> test_vec_reverse_sorted;
	std::vector<int> test_vec_few_distinct;

	test_vec_random.reserve(n);
	test_vec_nearly_sorted.reserve(n);
	test_vec_sorted.reserve(n);
	test_vec_reverse_sorted.reserve(n);
	test_vec_few_distinct.reserve(n);
	for (auto i = 0; i < n; i++) {
		test_vec_random.push_back(i);
		test_vec_nearly_sorted.push_back(i);
		test_vec_sorted.push_back(i);
		test_vec_reverse_sorted.push_back(n - i - 1);
		test_vec_few_distinct.push_back(i / few_sorted_param);
	}

	unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());

	std::shuffle(test_vec_random.begin(), test_vec_random.end(), std::default_random_engine(seed));

	
	std::random_device rd;
	std::mt19937 rng(rd());	// Mersenne-Twister
	std::uniform_int_distribution<int> uni(2, nearly_sorted_param); // guaranteed unbiased
	auto random_integer = uni(rng);

	for (auto i = 0U; i < test_vec_nearly_sorted.size() - nearly_sorted_param; i += random_integer) {
		random_integer = uni(rng);
		std::shuffle(test_vec_nearly_sorted.begin() + i, test_vec_nearly_sorted.begin() + i + random_integer - 1, std::default_random_engine(seed));
	}
	
	std::shuffle(test_vec_few_distinct.begin(), test_vec_few_distinct.end(), std::default_random_engine(seed));

	test_vectors.push_back(test_vec_random);
	test_vectors.push_back(test_vec_nearly_sorted);
	test_vectors.push_back(test_vec_sorted);
	test_vectors.push_back(test_vec_reverse_sorted);
	test_vectors.push_back(test_vec_few_distinct);
}
