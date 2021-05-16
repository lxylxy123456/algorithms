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

#ifndef ALGORITHMS_MERGESORT
#define ALGORITHMS_MERGESORT

#include <cassert>
#include <list>
#include <vector>

using std::size_t;

namespace algorithms {

template <typename T>
void Merge(std::vector<T>& A, std::size_t p, size_t q, size_t r) {
	// A[p:q] and A[q:r] are sorted
	std::list<T> L(A.begin() + p, A.begin() + q);
	std::list<T> R(A.begin() + q, A.begin() + r);
	for (std::size_t k = p; k < r; k++) {
		if (!R.size() || (L.size() && L.front() <= R.front())) {
			A[k] = L.front();
			L.pop_front();
		} else {
			A[k] = R.front();
			R.pop_front();
		}
	}
	assert(!R.size() && !L.size());
}

template <typename T>
void MergeSort(std::vector<T>& A, std::size_t p, size_t r) {
	if (p + 1 < r) {
		std::size_t q = (p + r) / 2;
		MergeSort(A, p, q);
		MergeSort(A, q, r);
		Merge(A, p, q, r);
	}
}

template <typename T>
void MergeSort(std::vector<T>& A) {
	MergeSort(A, 0, A.size());
}

}

#endif
