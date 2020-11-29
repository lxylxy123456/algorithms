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

#ifndef ALGORITHMS_QUICKSORT
#define ALGORITHMS_QUICKSORT

#include "random_integers.hpp"

namespace algorithms {

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
	size_t i = random_integer<int>(0, r - p - 1);
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

}

#endif
