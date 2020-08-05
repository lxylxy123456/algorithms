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

#ifndef ALGORITHMS_RANDOMPERMUTE
#define ALGORITHMS_RANDOMPERMUTE

#include <map>
#include "utils.h"

namespace algorithms {


template <typename T>
void PermuteBySorting(std::vector<T>& a) {
	size_t n = a.size();
	std::vector<int> r;
	random_integers(r, 1, n*n*n, n);
	std::map<int, T> b;
	for (auto i = r.begin(), j = a.begin(); j != a.end(); i++, j++)
		b[*i] = *j;
	for (auto i = b.begin(), j = a.begin(); j != a.end(); i++, j++)
		*j = i->second;
}

template <typename T>
void RandomizeInPlace(std::vector<T>& a) {
	size_t n = a.size();
	std::random_device rd;
	for (size_t i = 0; i < n - 1; i++)
		std::swap(a[i], a[std::uniform_int_distribution<size_t>(i, n-1)(rd)]);
}

}

#endif
