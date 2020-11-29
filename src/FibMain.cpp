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

#include "Fib.hpp"

#include "utils.hpp"
#include <algorithm>
#include <iostream>

using namespace algorithms;

int main(int argc, char *argv[]) {
	std::cout << "n\ta\tb\ta == b" << std::endl;
	for (int i = 1; i < std::max(argc, 2); i++) {
		size_t n = get_argv(argc, argv, i, 10);
		size_t a = Fib(n);
		std::cout << n << '\t' << a << '\t' << std::flush;
		size_t b = PFib(n);
		std::cout << b << '\t';
		std::cout << std::boolalpha << (a == b) << std::endl;
	}
	return 0;
}
