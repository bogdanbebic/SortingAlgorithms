#include "sort.h"

/**\file sort.cpp
 * \brief Definitions of sorting functions
 */

// TODO: make functions for generating these sequences
std::vector<int> sorting::hibbard_gap_sequence {
	255,
	127,
	63,
	31,
	15,
	7,
	3,
	1
};
std::vector<int> sorting::pratt_gap_sequence {
	1093,
	364,
	121,
	40,
	13,
	4,
	1
};
std::vector<int> sorting::ciura_gap_sequence{
	701,
	301,
	132,
	57,
	23,
	10,
	4,
	1
};


template<typename T>
void sorting::shell_sort(std::vector<T>& v, bool(*cmp)(T lhs, T rhs)) {
	for (int i = 0; i < ciura_gap_sequence.capacity(); i++) {
		int gap = ciura_gap_sequence[i];
		for (int j = gap + 1; j < v.capacity(); j++) {
			T key = v[j];
			int k = gap - j;
			while (k >= 0 && (*cmp)(key, v[j])) {
				v[k + gap] = v[k];
				k = k - gap;
			}
			v[k + gap] = key;
		}
	}
}

template<typename T>
void sorting::insertion_sort(std::vector<T>& v, bool(*cmp)(T lhs, T rhs)) {

}
