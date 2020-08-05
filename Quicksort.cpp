//
//  algorithm - some algorithms in "Introduction to Algorithms", third edition
//  Copyright (C) 2018  lxylxy123456
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

#ifndef MAIN
#define MAIN
#define MAIN_Quicksort
#endif

#ifndef FUNC_Quicksort
#define FUNC_Quicksort

#include "utils.h"

template <typename T>
T Partition(T p, T r) {
	T l = r - 1;
	typename T::value_type &x = *l;
	T i = p;
	for (T j = p; j != l; j++) {
		if (*j <= x) {
			std::swap(*i, *j);
			i++;
		}
	}
	std::swap(*i, *l);
	return i;
}

template <typename T>
void Quicksort(T p, T r) {
	if (p + 1 < r) {
		T q = Partition(p, r);
		Quicksort(p, q);
		Quicksort(q + 1, r);
	}
}

template <typename T>
T RandomizedPartition(T p, T r) {
	std::random_device rd;
    std::uniform_int_distribution<int> d(0, r - p - 1);
	size_t i = d(rd);
	std::swap(*(p + i), *(r - 1));
	return Partition(p, r);
}

template <typename T>
void RandomizedQuicksort(T p, T r) {
	if (p + 1 < r) {
		T q = RandomizedPartition(p, r);
		RandomizedQuicksort(p, q);
		RandomizedQuicksort(q + 1, r);
	}
}
#endif

#ifdef MAIN_Quicksort

#include "InsertSort.cpp"

int main(int argc, char *argv[]) {
	std::vector<int> a;
	const size_t n = get_argv(argc, argv, 1, 10);
	const size_t compute = get_argv(argc, argv, 2, 7);
	random_integers(a, 0, n - 1, n);
	std::vector<int> b(a), c(a);
	if (compute >> 0 & 1) {
		InsertSort(a);
		output_integers(a);
	}
	if (compute >> 1 & 1) {
		Quicksort(b.begin(), b.end());
		output_integers(b);
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (a == b) << std::endl;
	}
	if (compute >> 2 & 1) {
		RandomizedQuicksort(c.begin(), c.end());
		output_integers(c);
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (a == c) << std::endl;
	}
	return 0;
}
#endif

