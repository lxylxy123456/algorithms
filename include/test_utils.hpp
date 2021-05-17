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

#ifndef ALGORITHMS_TEST_UTILS
#define ALGORITHMS_TEST_UTILS

#include <cassert>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "random_integers.hpp"

namespace algorithms {

bool parse_args(int argc, char *argv[]) {
	bool valgrind = false;
	for (int i = 1; i < argc; i++) {
		std::string opt(argv[i]);
		if (opt == "--seed") {
			std::random_device::result_type s;
			std::istringstream(argv[++i]) >> s;
			random_seed_reset(s);
		} else if (opt == "--valgrind") {
			valgrind = true;
		} else {
			assert(0);
		}
	}
	std::cerr << argv[0] << ' ' << random_seed_get() << std::endl;
	return valgrind;
}

}

#endif
