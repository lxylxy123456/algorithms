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

#include "RaceExample.hpp"

#include <cassert>
#include <iostream>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t n) {
	std::cout << n << std::endl;
	for (std::size_t i = 0; i < n; i++)
		if (RaceExample<std::size_t>() != 2)
			return 1;
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	if (argc >= 2)
		// Valgrind: do not test at all
		return 0;
	for (int n = 0; n < 2147483647; n++)
		if (test(n))
			return 0;
	assert(false);
	return 0;
}
