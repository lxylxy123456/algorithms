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

#ifndef ALGORITHMS_INSERTSORT
#define ALGORITHMS_INSERTSORT

#include <vector>

using std::size_t;

namespace algorithms {

template <typename T>
void InsertSort(std::vector<T>& list) {
	for (size_t i = 1; i < list.size(); i++) {
		T tmp = list[i];
		size_t j;
		for (j = i; j > 0 && tmp < list[j - 1]; j--)
			list[j] = list[j - 1];
		list[j] = tmp;
	}
}

template <typename T>
void InsertSort(T p, T r) {
	for (T i = p + 1; i < r; i++) {
		typename T::value_type tmp = *i;
		T j;
		for (j = i - 1; j >= p && tmp < *j; j--)
			*(j + 1) = *j;
		*(j + 1) = tmp;
	}
}

}

#endif
