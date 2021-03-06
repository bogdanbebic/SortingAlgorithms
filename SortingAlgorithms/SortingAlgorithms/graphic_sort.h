#pragma once
#ifndef _GRAPHIC_SORT_H_
#define _GRAPHIC_SORT_H_
#include <vector>
#include <algorithm>
#include "graphics.h"

namespace  gui_sorting {
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
	void shell_sort(std::vector<T>& v, bool(*cmp)(const T& lhs, const T& rhs)) {
		gui::update_simulation();
		for (int i = 0; i < ciura_gap_sequence.size(); i++) {
			int gap = ciura_gap_sequence[i];
			for (int j = gap; j < v.size(); j++) {
				gui::rect_v[j].setFillColor(sf::Color::Red);
				T key = v[j];
				sf::RectangleShape rect = gui::rect_v[j];
				int k = j - gap;
				while (k >= 0 && (*cmp)(key, v[k])) {
					gui::rect_v[k].setFillColor(sf::Color::Red);
					v[k + gap] = v[k];
					gui::changePos(gui::rect_v[k + gap], gui::rect_v[k]);
					gui::update_simulation();
					gui::rect_v[k].setFillColor(sf::Color::White);
					k = k - gap;
				}
				v[k + gap] = key;
				gui::changePos(gui::rect_v[k + gap], rect);
				gui::update_simulation();
				gui::rect_v[j].setFillColor(sf::Color::White);
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
		gui::update_simulation();
		for (auto i = 1U; i < v.size(); i++) {
			for (int j = i - 1; j >= 0 && (*cmp)(v[j + 1], v[j]); j--) {
				gui::rect_v[j].setFillColor(sf::Color::Red);
				auto temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
				auto rect = gui::rect_v[j];
				gui::changePos(gui::rect_v[j], gui::rect_v[j + 1]);
				gui::changePos(gui::rect_v[j + 1], rect);
				gui::update_simulation();
				gui::rect_v[j].setFillColor(sf::Color::White);
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
		gui::update_simulation();
		for (int i = 1; i < v.size(); i++) {
			T current_elem = v[i];
			sf::RectangleShape rect = gui::rect_v[i];
			gui::rect_v[i].setFillColor(sf::Color::Red);
			int son_ind = i;
			int father_ind = (i - 1) / 2;
			while (son_ind > 0 && cmp(v[father_ind], current_elem)) {
				v[son_ind] = v[father_ind];
				gui::changePos(gui::rect_v[son_ind], gui::rect_v[father_ind]);
				son_ind = father_ind;
				father_ind = (son_ind - 1) / 2;
				gui::update_simulation();
			}
			v[son_ind] = current_elem;
			gui::changePos(gui::rect_v[son_ind], rect);
			gui::update_simulation();
			gui::rect_v[i].setFillColor(sf::Color::White);
		}
		for (auto i = v.size() - 1; i >= 1; i--) {
			// largest element gets pushed to the end
			// largest element is always at the beginning of the vector due to the heap
			gui::rect_v[i].setFillColor(sf::Color::Red);
			T last_elem = v[i];
			sf::RectangleShape rect = gui::rect_v[i];
			v[i] = v[0];
			gui::changePos(gui::rect_v[i], gui::rect_v[0]);
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
				gui::changePos(gui::rect_v[father_ind], gui::rect_v[son_ind]);
				father_ind = son_ind;
				son_ind = 2 * father_ind + 1;
				if (son_ind + 1 < i && cmp(v[son_ind], v[son_ind + 1]))
					son_ind++;
				gui::update_simulation();
			}
			v[father_ind] = last_elem;
			gui::changePos(gui::rect_v[father_ind], rect);
			gui::rect_v[i].setFillColor(sf::Color::White);
		}
		gui::update_simulation();
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
		gui::update_simulation();
		while (end > start) {
			int new_start = end;
			int new_end = start;
			for (int i = start; i < end; i++) {
				gui::rect_v[i + 1].setFillColor(sf::Color::Red);
				if (v[i] > v[i + 1]) {
					T tmp = v[i];
					v[i] = v[i + 1];
					v[i + 1] = tmp;
					sf::RectangleShape rect = gui::rect_v[i];
					gui::changePos(gui::rect_v[i], gui::rect_v[i + 1]);
					gui::changePos(gui::rect_v[i + 1], rect);
					new_end = i;
				}
				gui::update_simulation();
				gui::rect_v[i + 1].setFillColor(sf::Color::White);
			}
			end = new_end;
			for (int i = end; i >= start + 1; i--) {
				gui::rect_v[i - 1].setFillColor(sf::Color::Red);
				if (v[i] < v[i - 1]) {
					T tmp = v[i];
					v[i] = v[i - 1];
					v[i - 1] = tmp;
					sf::RectangleShape rect = gui::rect_v[i];
					gui::changePos(gui::rect_v[i], gui::rect_v[i - 1]);
					gui::changePos(gui::rect_v[i - 1], rect);
					new_start = i;
				}
				gui::update_simulation();
				gui::rect_v[i - 1].setFillColor(sf::Color::White);
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
	int find_pivot(std::vector<T>& v, int start, int end, bool(*cmp) (const T & lhs, const T & rhs)){
		auto i = start;
		auto j = end;
		T pivot = v[i];
		sf::RectangleShape rect = gui::rect_v[i];
		gui::rect_v[i].setFillColor(sf::Color::Red);
		gui::update_simulation();
		gui::rect_v[i].setFillColor(sf::Color::White);
		while (i < j) {
			while (!cmp(pivot, v[i]) && i < j)
				i++;
			while (cmp(pivot, v[j]))
				j--;
			if (i < j) {
				T tmp = v[i];
				v[i] = v[j];
				v[j] = tmp;
				sf::RectangleShape tmp_rect = gui::rect_v[i];
				gui::changePos(gui::rect_v[i], gui::rect_v[j]);
				gui::changePos(gui::rect_v[j], tmp_rect);
			}
			gui::rect_v[i].setFillColor(sf::Color::Red);
			gui::rect_v[j].setFillColor(sf::Color::Red);
			gui::update_simulation();
			gui::rect_v[i].setFillColor(sf::Color::White);
			gui::rect_v[j].setFillColor(sf::Color::White);
		}
		v[start] = v[j];
		v[j] = pivot;
		gui::changePos(gui::rect_v[start], gui::rect_v[j]);
		gui::changePos(gui::rect_v[j], rect);
		gui::update_simulation();
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
		gui::update_simulation();
		for (auto i = 0U; i < v.size(); i++) {
			for (int j = static_cast<int>(v.size()) - 2; j >= 0; j--) {
				gui::rect_v[j].setFillColor(sf::Color::Red);
				if ((*cmp)(v[j + 1], v[j])) {
					auto temp = v[j + 1];
					v[j + 1] = v[j];
					v[j] = temp;
					sf::RectangleShape rect = gui::rect_v[j + 1];
					gui::changePos(gui::rect_v[j + 1], gui::rect_v[j]);
					gui::changePos(gui::rect_v[j], rect);
				}
				gui::update_simulation();
				gui::rect_v[j].setFillColor(sf::Color::White);
			}
		}
	}

	template<typename T>
	void selection_sort(std::vector<T>& v, bool(*cmp) (const T & lhs, const T & rhs)) {
		gui::update_simulation();
		for (auto i = 0U; i < v.size() - 1; i++) {
			sf::RectangleShape min_rect = gui::rect_v[i];
			gui::rect_v[i].setFillColor(sf::Color::Red);
			auto min = v[i];
			auto min_index = i;
			for (auto j = i + 1; j < v.size(); j++) {
				gui::rect_v[j].setFillColor(sf::Color::Red);
				if ((*cmp)(v[j], min)) {
					gui::rect_v[min_index].setFillColor(sf::Color::White);
					min_rect = gui::rect_v[j];
					min = v[j];
					min_index = j;
				}
				gui::update_simulation();

				if (min_index != j) {
					gui::rect_v[j].setFillColor(sf::Color::White);
				}
			}
			gui::changePos(gui::rect_v[min_index], gui::rect_v[i]);
			gui::changePos(gui::rect_v[i], min_rect);
			gui::rect_v[min_index].setFillColor(sf::Color::White);
			gui::update_simulation();
			gui::rect_v[i].setFillColor(sf::Color::White);
			v[min_index] = v[i];
			v[i] = min;
		}
	}

	template<typename T>
	void merge_sort(std::vector<T>& v, bool(*cmp) (const T & lhs, const T & rhs)) {
		gui::update_simulation();
		for (auto current_size = 1U; current_size <= v.size() - 1; current_size *= 2) {
			for (auto left_start = 0U; left_start < v.size() - 1; left_start += 2 * current_size) {
				const auto mid = left_start + current_size - 1 < v.size() - 1 ? left_start + current_size - 1 : static_cast<unsigned>(v.size()) - 1U;
				auto right_end = left_start + 2 * current_size - 1 < v.size() - 1 ? left_start + 2 * current_size - 1 : static_cast<unsigned>(v.size()) - 1U;

				std::vector<sf::RectangleShape> tmp_rect;
				tmp_rect.reserve(right_end - left_start + 1);
				std::vector<T> temp;
				tmp_rect.reserve(right_end - left_start + 1);
				temp.reserve(right_end - left_start + 1);
				auto left_iter = left_start, right_iter = mid + 1;
				while (left_iter <= mid && right_iter <= right_end) {
					gui::rect_v[left_iter].setFillColor(sf::Color::Red);
					gui::rect_v[right_iter].setFillColor(sf::Color::Red);
					gui::update_simulation();
					if (!(*cmp)(v[left_iter], v[right_iter])) {
						gui::rect_v[right_iter].setFillColor(sf::Color::White);
						tmp_rect.push_back(gui::rect_v[right_iter]);
						temp.push_back(v[right_iter++]);
					}
					else {
						gui::rect_v[left_iter].setFillColor(sf::Color::White);
						tmp_rect.push_back(gui::rect_v[left_iter]);
						temp.push_back(v[left_iter++]);
					}
					//gui::update_simulation();
				}

				while (left_iter <= mid) {
					gui::rect_v[left_iter].setFillColor(sf::Color::White);
					tmp_rect.push_back(gui::rect_v[left_iter]);
					temp.push_back(v[left_iter++]);
				}
				while (right_iter <= right_end) {
					gui::rect_v[right_iter].setFillColor(sf::Color::White);
					tmp_rect.push_back(gui::rect_v[right_iter]);
					temp.push_back(v[right_iter++]);
				}

				for (auto i = left_start, j = 0U; i <= right_end; i++) {
					gui::changePos(gui::rect_v[i], tmp_rect[j]);
					gui::rect_v[i].setFillColor(sf::Color::Red);
					gui::update_simulation();
					gui::rect_v[i].setFillColor(sf::Color::White);
					v[i] = temp[j++];
				}
			}
		}
	}
}
#endif 
