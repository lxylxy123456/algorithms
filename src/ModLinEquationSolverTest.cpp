//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#include "ModLinEquationSolver.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "Euclid.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

template <typename T>
int test(T a, T b, T n) {
	std::vector<T> ans;
	ModularLinearEquationSolver(a, b, n, ans);
	std::cout << a << " * x === " << b << " (mod " << n << ")" << std::endl;
	if (ans.size()) {
		std::cout << "x = ";
		output_integers(ans);
		for (typename std::vector<T>::iterator i = ans.begin(); i != ans.end();
			i++)
			assert((a * *i - b) % n == 0);
	} else {
		std::cout << "no solutions" << std::endl;
		assert(b % Euclid(a, n) != 0);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	for (int n = 2; n <= 46340; n += 10)
		test(random_integer<int>(1, n),
			random_integer<int>(1, n),
			random_integer<int>(1, n));
	for (long int n = 2; n <= 3037000499; n += 1000000)
		test(random_integer<long int>(1, n),
			random_integer<long int>(1, n),
			random_integer<long int>(1, n));
	for (long int n = 2; n <= 3037000499; n += 1000000)
		test(random_integer<long long int>(1, n),
			random_integer<long long int>(1, n),
			random_integer<long long int>(1, n));
	return 0;
}
