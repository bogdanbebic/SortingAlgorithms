#pragma once
#ifndef _SORT_H_
#define _SORT_H_
#include <vector>

namespace  sorting {

	/**
	 * \brief gap sequences used for shell sort
	 */
	extern std::vector<int> hibbard_gap_sequence;
	extern std::vector<int> pratt_gap_sequence;
	extern std::vector<int> ciura_gap_sequence;

	/**
	* \brief Sorts the given vector of numbers using shell sort
	* \param v Vector that is sorted
	* \param cmp Function that compares two elements (cmp should return lhs < rhs for ascending sort)
	*/
	template<typename T> void shell_sort(std::vector<T>& v, bool (*cmp) (T lhs, T rhs));

	template<typename T> void insertion_sort(std::vector<T>& v, bool(*cmp) (T lhs, T rhs));

}

#endif 