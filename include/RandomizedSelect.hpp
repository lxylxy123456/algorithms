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

#ifndef ALGORITHMS_RANDOMIZEDSELECT
#define ALGORITHMS_RANDOMIZEDSELECT

#include "utils.h"
#include "Quicksort.hpp"

namespace algorithms {


template <typename T>
T RandomizedSelect(T p, T r, size_t i) {
	if (p == r - 1)
		return p;
	T q = RandomizedPartition(p, r);
	size_t k = q - p;
	if (i == k)
		return q;
	else if (i < k)
		return RandomizedSelect(p, q, i);
	else
		return RandomizedSelect(q + 1, r, i - k - 1);
}

template <typename T>
T RandomizedSelect(std::vector<T> A, size_t i) {
	return *RandomizedSelect(A.begin(), A.end(), i);
}

template <typename T>
T RandomizedSelectIter(std::vector<T> A, size_t i) {
	typename std::vector<T>::iterator p = A.begin(), q, r = A.end();
	while (true) {
		if (p == r - 1)
			return *p;
		q = RandomizedPartition(p, r);
		size_t k = q - p;
		if (i == k)
			return *q;
		else if (i < k)
			r = q;
		else {
			p = q + 1;
			i -= k + 1;
		}
	}
}

}

#endif
