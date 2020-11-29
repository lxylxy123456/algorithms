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

#include "LCSLength.hpp"

#include "utils.hpp"
#include <iostream>
#include <vector>

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t x = get_argv(argc, argv, 1, 8);
	const size_t y = get_argv(argc, argv, 2, 9);
	const size_t n = get_argv(argc, argv, 3, 25);
	std::vector<char> X, Y;
	random_integers<char>(X, 'a', 'a' + n, x);
	random_integers<char>(Y, 'a', 'a' + n, y);
	output_integers(X, "");
	output_integers(Y, "");
	std::vector<VECT_SIZT> c = LCSLength(X, Y);
	PrintLCS(c, X, x, y);
	std::cout << std::endl;
	return 0;
}
