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

#ifndef ALGORITHMS_MODLINEQUATIONSOLVER
#define ALGORITHMS_MODLINEQUATIONSOLVER

#include "utils.h"

#include "Euclid.hpp"

namespace algorithms {

template <typename T>
void ModularLinearEquationSolver(T a, T b, T n, std::vector<T>& ans) {
	T x, y;
	T d = ExtendedEuclid(a, n, x, y);
	if (b % d == 0) {
		T x0 = x * (b / d) % n;
		ans.reserve(d);
		for (T i = 0; i < d; i++)
			ans.push_back(((x0 + i * (n / d)) % n + n) % n);
	}
}

}

#endif
