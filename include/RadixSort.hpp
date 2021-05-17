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

#ifndef ALGORITHMS_RADIXSORT
#define ALGORITHMS_RADIXSORT

#include <algorithm>
#include <vector>

#include "CountingSort.hpp"

namespace algorithms {

template <typename T>
class GetBit {
	public:
		GetBit(std::size_t b): bit(b) {}
		std::size_t operator()(T x) { return (x >> bit) & 1; }
		std::size_t bit;
};

template <typename T>
void RadixSort(std::vector<T>& A, std::size_t b) {
	std::vector<T> B(A.size(), 0);
	for (std::size_t i = 0; i < b; i++) {
		CountingSort(A, B, 2, GetBit<T>(i));
		std::copy(B.begin(), B.end(), A.begin());
	}
}

}

#endif
