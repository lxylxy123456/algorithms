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

#include "Hash.hpp"

#include "utils.h"

using namespace algorithms;

int main(int argc, char *argv[]) {
	size_t k = get_argv(argc, argv, 1, 7);  	// max key < 1<<k
	size_t md = get_argv(argc, argv, 2, 23); 	// prime in DivisionHash
	size_t mm = get_argv(argc, argv, 3, 5); 	// MultiplicationHash: m < 1<<p
	size_t p = get_argv(argc, argv, 4, 131);  	// prime in UniversalHash > 1<<k
	DivisionHash d(md);
	MultiplicationHash m(k, mm, 0.6180339887);
	UniversalHash u(p, md);
	std::cout << "key\tdiv\tmul\tuniv" << std::endl;
	for (size_t i = 0; i < 1u<<k; i++) {
		std::cout << i << '\t' << d(i) << '\t' << m(i)
				 << '\t' << u(i) << std::endl;
	}
	return 0;
}
