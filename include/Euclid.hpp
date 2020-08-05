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

#ifndef ALGORITHMS_EUCLID
#define ALGORITHMS_EUCLID

#include <cassert>
#include "utils.h"

namespace algorithms {


template <typename T>
T Euclid(T a, T b) {
	if (b == 0)
		return a;
	else
		return Euclid(b, a % b);
}

template <typename T>
T ExtendedEuclid(T a, T b, T& x, T& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	} else {
		T xx, yy;
		T dd = ExtendedEuclid(b, a % b, xx, yy);
		x = yy;
		y = xx - (a / b) * yy;
		return dd;
	}
}

}

#endif
