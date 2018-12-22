#pragma once
#ifndef _SORT_H_
#define _SORT_H_
#include <vector>

namespace  sorting {

	/**
	 * \brief gap sequence used for shell sort
	 */
	extern std::vector<int> ciura_gap_sequence;

	/**
	* \brief Sorts the given vector of numbers using shell sort
	* \param v Vector that is sorted
	* \param cmp Function that compares two elements (cmp should return lhs < rhs for ascending sort)
	*/
	template<typename T>
	void shell_sort(std::vector<T>& v, bool(*cmp)(const T& lhs,const T& rhs)) {
		for (int i = 0; i < ciura_gap_sequence.size(); i++) {
			int gap = ciura_gap_sequence[i];
			for (int j = gap; j < v.size(); j++) {
				T key = v[j];
				int k = j - gap;
				while (k >= 0 && (*cmp)(key, v[k])) {
					v[k + gap] = v[k];
					k = k - gap;
				}
				v[k + gap] = key;
			}
		}
	}

	/**
	* \brief Sorts the given vector of numbers using insertion sort
	* \param v Vector that is sorted
	* \param cmp Function that compares two elements (cmp should return lhs < rhs for ascending sort)
	*/
	template<typename T>
	void insertion_sort(std::vector<T>& v, bool(*cmp) (const T & lhs, const T & rhs)) {
		for (auto i = 1U; i < v.size(); i++) {
			for (int j = i - 1; j >= 0; j--) {
				if ((*cmp)(v[j + 1], v[j])) {
					auto temp = v[j];
					v[j] = v[j + 1];
					v[j + 1] = temp;
				}
			}
		}
	}

	/**
	* \brief Sorts the given vector of numbers using heap sort
	* \param v Vector that is sorted
	* \param cmp Function that compares two elements (cmp should return lhs < rhs for ascending sort)
	*/
	template<typename T>
	void heap_sort(std::vector<T>& v, bool(*cmp) (const T & lhs, const T & rhs)) {
		// heap creation
		for(int i = 1; i < v.size(); i++) {
			T current_elem = v[i];
			int son_ind = i;
			int father_ind = (i - 1) / 2;
			while (son_ind > 0 && cmp(v[father_ind], current_elem)) {
				v[son_ind] = v[father_ind];
				son_ind = father_ind;
				father_ind = (son_ind - 1) / 2;
			}
			v[son_ind] = current_elem;
		}
		for(auto i = v.size() - 1; i >= 1; i--) {
			// largest element gets pushed to the end
			// largest element is always at the beginning of the vector due to the heap
			T last_elem = v[i];
			v[i] = v[0];
			int father_ind = 0;
			// heap update
			int son_ind;
			if (i >= 3 && cmp(v[1], v[2]))
				son_ind = 2;
			else
				son_ind = 1;
			// reposition the last element 
			while (son_ind < i && cmp(last_elem, v[son_ind])) {
				v[father_ind] = v[son_ind];
				father_ind = son_ind;
				son_ind = 2 * father_ind + 1;
				if (son_ind + 1 < i && cmp(v[son_ind], v[son_ind + 1]))
					son_ind++;
			}
			v[father_ind] = last_elem;
		}
	}

	/**
	* \brief Sorts the given vector of numbers using shaker sort (modified bubble sort)
	* \param v Vector that is sorted
	* \param cmp Function that compares two elements (cmp should return lhs < rhs for ascending sort)
	*/
	template<typename T>
	void shaker_sort(std::vector<T>& v, bool(*cmp) (const T & lhs, const T & rhs)) {
		int start = 0;
		int end = static_cast<int>(v.size()) - 1;
		while (end > start) {
			int new_start = end;
			int new_end = start;
			for (int i = start; i < end - 1; i++) {
				if (v[i] > v[i + 1]) {
					T tmp = v[i];
					v[i] = v[i + 1];
					v[i + 1] = tmp;
					new_end = i;
				}
			}
			end = new_end;
			for (int i = end; i >= start + 1; i--) {
				if (v[i] < v[i - 1]) {
					T tmp = v[i];
					v[i] = v[i - 1];
					v[i - 1] = tmp;
					new_start = i;
				}
			}
			start = new_start;
		}
	}
}
#endif 
