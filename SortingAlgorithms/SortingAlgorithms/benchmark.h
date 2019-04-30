#pragma once
#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include <vector>
#include <chrono>
#include "graphics.h"


namespace benchmark_int {
	extern std::vector<std::vector<int>> test_vectors;

	extern void(*sort_func[gui::NumOfSorts])(std::vector<int>&, bool(*cmp)(const int&, const int&));
	extern std::vector<double> runtime;

	void init_test_vectors(const int n, const int few_sorted_param = 10, const int nearly_sorted_param = 5);

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
