//  
//  algorithm - some algorithms in "Introduction to Algorithms", third edition
//  Copyright (C) 2020  lxylxy123456
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as
//  published by the Free Software Foundation, either version 3 of the
//  License, or (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//  
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//  

#include <InsertSort.hpp>
#include "utils.h"

#include <cassert>

using namespace algorithms;

template <typename T>
bool is_increasing_order(T p, T r) {
	if (p == r)
		return true;
	for (T i = p, j = p + 1; j < p; j++)
		if (*i > *j)
			return false;
	return true;
}

int test_vector(int n) {
	std::vector<int> a;
	random_integers(a, 0, n - 1, n);
	InsertSort(a);
	assert(is_increasing_order(a.begin(), a.end()));
	return 0;
}

int test_iterator(int n) {
	std::vector<int> a;
	random_integers(a, 0, n - 1, n);
	InsertSort(a.begin(), a.end());
	assert(is_increasing_order(a.begin(), a.end()));
	return 0;
}

int main(int argc, char *argv[]) {
	test_vector(0);
	test_vector(1);
	test_vector(2);
	test_vector(10);
	test_vector(100);
	test_iterator(0);
	test_iterator(1);
	test_iterator(2);
	test_iterator(10);
	test_iterator(100);
	return 0;
}
