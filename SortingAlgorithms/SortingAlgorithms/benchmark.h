#pragma once
#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include <vector>
#include <chrono>


namespace benchmark_int {
	extern std::vector<int> test_vec_random;
	extern std::vector<int> test_vec_nearly_sorted;
	extern std::vector<int> test_vec_sorted;
	extern std::vector<int> test_vec_reverse_sorted;
	extern std::vector<int> test_vec_few_distinct;

	void init_test_vectors(const int n, const int few_sorted_param);

}


namespace benchmark {
	
	template <typename T>
	std::chrono::duration<double> measure_time(void(*f)(std::vector<T>&, bool(*)(const T&, const T&)), std::vector<T> vec, bool(*cmp)(const T&, const T&)) {
		const auto start = std::chrono::system_clock::now();

		f(vec, cmp);

		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> elapsed = end - start;
		return elapsed;
	}

}

#endif
