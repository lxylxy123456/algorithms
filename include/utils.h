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

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <string>
#include <sstream>

#include "random_integers.hpp"
#include "output_integers.hpp"
#include "print_ptr.hpp"

namespace algorithms {

template <typename T>
void input_integers(std::vector<T>& a) {
	std::copy(	std::istream_iterator<T>(std::cin),
				std::istream_iterator<T>(),
				std::insert_iterator<std::vector<T>>(a, a.begin()));
}

template <typename T>
T get_argv(int argc, char *argv[], int index, T def) {
	if (index < 0 || index >= argc)
		return def;
	T ans;
	std::istringstream(argv[index]) >> ans;
	return ans;
}

}

#endif
