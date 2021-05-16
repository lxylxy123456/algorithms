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

#ifndef ALGORITHMS_ONLINEMAXIMUM
#define ALGORITHMS_ONLINEMAXIMUM

#include <vector>

using std::size_t;

namespace algorithms {

template <typename T>
std::size_t OnLineMaximum(std::vector<T> candidates, size_t k) {
	std::size_t n = candidates.size();
	T best_score = candidates[0];
	for (std::size_t i = 0; i < k; i++)
		if (candidates[i] > best_score)
			best_score = candidates[i];
	for (std::size_t i = k; i < n; i++)
		if (candidates[i] > best_score)
			return i;
	return n - 1;
}

}

#endif
