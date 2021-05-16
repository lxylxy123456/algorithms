//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#ifndef ALGORITHMS_BUCKETSORT
#define ALGORITHMS_BUCKETSORT

#include <algorithm>
#include <cassert>
#include <vector>

#include "InsertSort.hpp"

using std::size_t;

namespace algorithms {

template <typename T>
void BucketSort(std::vector<T>& A, T a_min, T a_max) {
	const std::size_t n = A.size();
	const T a_diff = a_max - a_min;
	// for all i, a_min <= A[i] < a_max
	std::vector<std::vector<T>> B;
	B.resize(n);
	for (typename std::vector<T>::iterator i = A.begin(); i != A.end(); i++)
		B[(*i - a_min) * n / a_diff].push_back(*i);
	typename std::vector<T>::iterator b = A.begin();
	for (typename std::vector<std::vector<T>>::iterator i = B.begin();
		i != B.end(); i++) {
		InsertSort(*i);
		b = std::copy(i->begin(), i->end(), b);
	}
	assert(b == A.end());
}

}

#endif
