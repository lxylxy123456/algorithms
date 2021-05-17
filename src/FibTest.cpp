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

#include "Fib.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t n, std::size_t expected) {
	std::size_t a = Fib(n);
	std::cout << n << '\t' << expected << '\t' << a << '\t' << std::flush;
	std::size_t b = PFib(n);
	assert(a == expected);
	std::cout << b << std::endl;
	assert(a == b);
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	int N = 21;
	if (argc >= 2)
		// Valgrind: reduce test size
		N = 13;
	std::size_t prev = 0, cur = 1;
	for (int n = 0; n < N; n++) {
		test(n, prev);
		prev += cur;
		std::swap(cur, prev);
	}
	return 0;
}
