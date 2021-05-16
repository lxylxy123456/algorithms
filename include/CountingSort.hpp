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

#ifndef ALGORITHMS_COUNTINGSORT
#define ALGORITHMS_COUNTINGSORT

#include <vector>

using std::size_t;

namespace algorithms {

template <typename T>
inline size_t Self(T x) {
	return x;
}

template <typename T, typename Predicate>
void CountingSort(std::vector<T>& A, std::vector<T>& B, size_t k, Predicate f) {
	// for i in A: i in range(k); T must be int-like
	std::vector<size_t> C(k, 0);
	for (typename std::vector<T>::iterator i = A.begin(); i != A.end(); i++)
		C[f(*i)]++;
	for (typename std::vector<size_t>::iterator i = C.begin() + 1;
		i != C.end(); i++)
		*i += *(i - 1);
	for (typename std::vector<T>::reverse_iterator i = A.rbegin();
		i < A.rend(); i++)
		B[--C[f(*i)]] = *i;
}

}

#endif
