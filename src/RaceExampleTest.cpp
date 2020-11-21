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
#include "utils.hpp"

#include <cassert>

using namespace algorithms;

int test(size_t n) {
	std::cout << n << std::endl;
	for (size_t i = 0; i < n; i++)
		if (RaceExample<size_t>() != 2)
			return 1;
	return 0;
}

int main(int argc, char *argv[]) {
	for (int n = 0; n < 2147483647; n++)
		if (test(n))
			return 0;
	assert(false);
	return 0;
}