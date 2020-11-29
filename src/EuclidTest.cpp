//
//  algorithm - some algorithms in "Introduction to Algorithms", third edition
//  Copyright (C) 2020  lxylxy123456
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

#include "Euclid.hpp"
#include "utils.hpp"

#include <cassert>
#include <iostream>

using namespace algorithms;

template <typename T>
int test(T a, T b) {
	T x, y;
	T d = ExtendedEuclid(a, b, x, y);
	std::cout << d << " = gcd(" << a << ", " << b << ") = "
			 << a << " * " << x << " + " << b << " * " << y << std::endl;
	assert(d == Euclid(a, b));
	assert(d == a * x + b * y);
	assert(a % d == 0);
	assert(b % d == 0);
	assert(a * x + b * y == d);
	return 0;
}

int main(int argc, char *argv[]) {
	for (int n = 2; n > 0; n += 1000000)
		test(random_integer<int>(1, n), random_integer<int>(1, n));
	for (long int n = 2; n > 0; n += 1000000000000000)
		test(random_integer<long int>(1, n), random_integer<long int>(1, n));
	for (long int n = 2; n > 0; n += 1000000000000000)
		test(random_integer<long long int>(1, n),
			random_integer<long long int>(1, n));
	return 0;
}
