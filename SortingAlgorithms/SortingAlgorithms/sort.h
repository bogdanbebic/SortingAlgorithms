#pragma once
#ifndef _SORT_H_
#define _SORT_H_
#include <vector>
#include <algorithm>

namespace  sorting {

	/**
	* \brief compares two integers
	* \param lhs first integer
	* \param rhs second integer
	* \return true if lhs is smaller than rhs, otherwise returns false
	*/
	inline bool less(const int & lhs, const int & rhs) {
		return lhs < rhs;
	}


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
			for (int j = i - 1; j >= 0 && (*cmp)(v[j + 1], v[j]); j--) {
				auto temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
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

	/**
	* \brief Function used for finding the pivot, and sorting his position
	* \param v Vector that is sorted
	* \param start beginning of the current part of the vector
	* \param end ending of the current part of the vector
	* \param cmp Function that compares two elements (cmp should return lhs < rhs for ascending sort)
	*/
	template<typename T>
	int find_pivot(std::vector<T>& v, int start, int end, bool(*cmp) (const T & lhs, const T & rhs)) {
		auto i = start;
		auto j = end;
		T pivot = v[i];
		while (i < j) {
			while (!cmp(pivot, v[i]) && i < j)
				i++;
			while (cmp(pivot, v[j]))
				j--;
			if (i < j) {
				T tmp = v[i];
				v[i] = v[j];
				v[j] = tmp;
			}
		}
		v[start] = v[j];
		v[j] = pivot;
		return j;
	}

	/**
	* \brief Recursive function used for quick sort
	* \param v Vector that is sorted
	* \param start beginning of the current part of the vector
	* \param end ending of the current part of the vector
	* \param cmp Function that compares two elements (cmp should return lhs < rhs for ascending sort)
	*/
	template<typename T>
	void quick_recursive(std::vector<T>& v, int start, int end, bool(*cmp) (const T & lhs, const T & rhs)) {
		if (start < end) {
			int i = find_pivot(v, start, end, cmp);
			quick_recursive(v, start, i - 1, cmp);
			quick_recursive(v, i + 1, end, cmp);
		}
	}

	/**
	* \brief Sorts the given vector of numbers using quick sort
	* \param v Vector that is sorted
	* \param cmp Function that compares two elements (cmp should return lhs < rhs for ascending sort)
	*/
	template<typename T>
	void quick_sort(std::vector<T>& v, bool(*cmp) (const T & lhs, const T & rhs)) {
		quick_recursive<T>(v, 0, static_cast<int>(v.size() - 1), cmp);
	}

	template<typename T>
	void bubble_sort(std::vector<T>& v, bool(*cmp) (const T & lhs, const T & rhs)) {
		for (auto i = 0U; i < v.size(); i++) {
			for (int j = static_cast<int>(v.size()) - 2; j >= 0; j--) {
				if ((*cmp)(v[j + 1], v[j])) {
					auto temp = v[j + 1];
					v[j + 1] = v[j];
					v[j] = temp;
				}
			}
		}
	}

	template<typename T>
	void selection_sort(std::vector<T>& v, bool(*cmp) (const T & lhs, const T & rhs)) {
		for (auto i = 0U; i < v.size() - 1; i++) {
			auto min = v[i];
			auto min_index = i;
			for (auto j = i + 1; j < v.size(); j++) {
				if ((*cmp)(v[j], min)) {
					min = v[j];
					min_index = j;
				}
			}
			v[min_index] = v[i];
			v[i] = min;
		}
	}

	template<typename T>
	void merge_sort(std::vector<T>& v, bool(*cmp) (const T & lhs, const T & rhs)) {
		for (auto current_size = 1U; current_size <= v.size() - 1; current_size *= 2) {
			for (auto left_start = 0U; left_start < v.size() - 1; left_start += 2 * current_size) {
				const auto mid = left_start + current_size - 1 < v.size() - 1 ? left_start + current_size - 1 : static_cast<unsigned>(v.size()) - 1U;
				auto right_end = left_start + 2 * current_size - 1 < v.size() - 1 ? left_start + 2 * current_size - 1 : static_cast<unsigned>(v.size()) - 1U;

				std::vector<T> temp;
				temp.reserve(right_end - left_start + 1);
				auto left_iter = left_start, right_iter = mid + 1;
				while (left_iter <= mid && right_iter <= right_end) {
					if (!(*cmp)(v[left_iter], v[right_iter])) {
						temp.push_back(v[right_iter++]);
					}
					else {
						temp.push_back(v[left_iter++]);
					}
				}

				while (left_iter <= mid) {
					temp.push_back(v[left_iter++]);
				}
				while (right_iter <= right_end) {
					temp.push_back(v[right_iter++]);
				}

				for (auto i = left_start, j = 0U; i <= right_end; i++) {
					v[i] = temp[j++];
				}
			}
		}
	}

}
#endif 
