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

#include "CountingSort.hpp"

#include <iostream>
#include <vector>

#include "InsertSort.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	std::vector<int> a;
	const std::size_t n = get_argv(argc, argv, 1, 10);
	const int k = get_argv(argc, argv, 2, n);
	const std::size_t compute = get_argv(argc, argv, 3, 3);
	random_integers(a, 0, k - 1, n);
	std::vector<int> b(a), c(n, 0);
	if (compute >> 0 & 1) {
		InsertSort(a);
		output_integers(a);
	}
	if (compute >> 1 & 1) {
		CountingSort(b, c, k, Self<int>);
		output_integers(c);
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (a == c) << std::endl;
	}
	return 0;
}
