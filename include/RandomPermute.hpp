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

#include <algorithm>
#include <map>
#include <vector>

#include "random_integers.hpp"

using std::size_t;

namespace algorithms {

template <typename T>
void PermuteBySorting(std::vector<T>& a) {
	size_t n = a.size();
	std::vector<int> r;
	random_integers(r, 1, n*n*n, n);
	std::map<int, T> b;
	typename std::vector<T>::iterator j = a.begin();
	for (std::vector<int>::iterator i = r.begin(); j != a.end(); i++, j++)
		b[*i] = *j;
	j = a.begin();
	for (typename std::map<int, T>::iterator i = b.begin(); j != a.end();
		i++, j++)
		*j = i->second;
}

template <typename T>
void RandomizeInPlace(std::vector<T>& a) {
	size_t n = a.size();
	for (size_t i = 0; i + 1 < n; i++)
		std::swap(a[i], a[random_integer<size_t>(i, n - 1)]);
}

}

#endif
