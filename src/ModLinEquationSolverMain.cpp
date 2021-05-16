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

#include "ModLinEquationSolver.hpp"

#include <iostream>
#include <vector>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t nn = get_argv(argc, argv, 1, 4);
	using T = long long int;
	T a = get_argv(argc, argv, 2, random_integer<T>(0, 1 << nn));
	T b = get_argv(argc, argv, 3, random_integer<T>(0, 1 << nn));
	T n = get_argv(argc, argv, 4, random_integer<T>(0, 1 << nn));
	std::vector<T> ans;
	ModularLinearEquationSolver(a, b, n, ans);
	std::cout << a << " * x === " << b << " (mod " << n << ")" << std::endl;
	if (ans.size()) {
		std::cout << "x = ";
		output_integers(ans);
	} else
		std::cout << "no solutions" << std::endl;
	return 0;
}
