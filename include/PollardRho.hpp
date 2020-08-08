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

#ifndef ALGORITHMS_POLLARDRHO
#define ALGORITHMS_POLLARDRHO

#include <cstddef>
#include <random>

#include "Euclid.hpp"

namespace algorithms {

template <typename T>
T abs(T x) {
	if (x < 0)
		return -x;
	else
		return x;
}

template <typename T>
T PollardRho(T n) {
	size_t i = 1, k = 2;
    std::random_device rd;
    std::uniform_int_distribution<T> dis(0, n - 1);
	T x = dis(rd), y = x;
	while (i < 1048576) {
		i++;
		x = (x * x - 1) % n;
		T d = Euclid(abs<T>(y - x), n);
		if (d != 1 && d != n)
			return d;
		if (i == k) {
			y = x;
			k *= 2;
		}
	}
	return 0;
}

}

#endif
