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

#ifndef ALGORITHMS_MODULAREXPONENTIATION
#define ALGORITHMS_MODULAREXPONENTIATION

#include <cassert>
#include <cmath>

#include "Euclid.hpp"

using std::size_t;

namespace algorithms {

template <typename T>
T ModularExponentiation(T a, T b, T n) {
	T c = 0;
	T d = 1;
	assert(b >= 0);
	if (b == 0)
		return 1;
	for (T i = log2(b) + 1; i-- > 0;) {
		c *= 2;
		d = d * d % n;
		if (b & 1 << i) {
			c++;
			d = d * a % n;
		}
	}
	assert(c == b);
	return d;
}

}

#endif
