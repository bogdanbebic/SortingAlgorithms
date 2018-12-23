#pragma once
#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include <vector>
#include <chrono>

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
