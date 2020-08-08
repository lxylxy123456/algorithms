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

#ifndef ALGORITHMS_OUTPUT_INTEGERS
#define ALGORITHMS_OUTPUT_INTEGERS

#include <algorithm>
#include <iostream>
#include <iterator>

namespace algorithms {

template <typename T>
void output_integers(const T& a, const char* sep) {
	std::copy(a.begin(), a.end(),
				std::ostream_iterator<typename T::value_type>(std::cout, sep));
	std::cout << std::endl;
}

template <typename T>
void output_integers(const T& a) {
	output_integers(a, " ");
}

}

#endif
