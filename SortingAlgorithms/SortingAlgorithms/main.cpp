#include <iostream>
#include <vector>

#include "sort.h"

bool less(const int & lhs, const int & rhs) {
	return lhs < rhs;
}

std::vector<int> test_vec = { 8, 1, 3, 5, 2, 6, 4, 7, 0, 9 };

int main(int argc, char* argv[]) {
	for (auto elem : test_vec) {
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	// Test of sort function on test_vec
	sorting::insertion_sort<int>(test_vec, less);

	for (auto elem : test_vec) {
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	system("pause");
}
