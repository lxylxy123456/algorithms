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

#include "Pseudoprime.hpp"

#include <cassert>
#include <iostream>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

template <typename T>
int test(T n) {
	std::cout << n << std::endl;
	bool ans = Pseudoprime(n);
	bool ans2 = (n % 2 != 0);
	for (T i = 3; i * i <= n; i += 2)
		if (n % i == 0) {
			ans2 = false;
			break;
		}
	if (ans != ans2)
		assert(ans && !ans2);
	return ans != ans2;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	int total = 0, count = 0;
	for (int n = 2; n <= 46340; n += 10) {
		count += test(random_integer<int>(1, n));
		total++;
	}
	for (long int n = 2; n <= 3037000499; n += 300000) {
		count += test(random_integer<long int>(1, n));
		total++;
	}
	for (long int n = 2; n <= 3037000499; n += 300000) {
		count += test(random_integer<long long int>(1, n));
		total++;
	}
	assert((double) count / total < 0.0055);
	return 0;
}
