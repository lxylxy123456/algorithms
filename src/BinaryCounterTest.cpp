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

#include "BinaryCounter.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(size_t n, size_t k) {
	BinaryCounter A(k);
	for (size_t i = 0; i < n; i++) {
		A.Increment();
	}
	std::cout << n << '\t' << A.x<size_t>() << std::endl;
	assert(A.x<size_t>() == (n & ((1 << k) - 1)));
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<int> ns = {1, 4, 16, 19, 20, 25, 100};
	std::vector<int> ks = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<int>::iterator k = ks.begin(); k < ks.end(); k++)
			test(*n, *k);
	return 0;
}
