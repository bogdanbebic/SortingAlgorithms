#include "benchmark.h"

std::vector<int> benchmark_int::test_vec_random;
std::vector<int> benchmark_int::test_vec_nearly_sorted;
std::vector<int> benchmark_int::test_vec_sorted;
std::vector<int> benchmark_int::test_vec_reverse_sorted;
std::vector<int> benchmark_int::test_vec_few_distinct;

void benchmark_int::init_test_vectors(const int n, const int few_sorted_param) {
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

	// TODO: random
	// TODO: nearly sorted
	// TODO: few distinct

}
