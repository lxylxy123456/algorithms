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

#include "Hash.hpp"

#include <cassert>
#include <iostream>
#include <map>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

template <typename H>
int test_h(std::size_t k, size_t u, H h) {
	std::map<std::size_t, size_t> count;
	for (std::size_t i = 0; i < 1u<<k; i++) {
		std::size_t v = h(i);
		assert(v < u);
		count[v]++;
	}
	assert(!k || count.size() > 1);
	return 0;
}

int test_d() {
	std::vector<int> ks{0, 1, 2, 3, 4, 5, 6, 7};
	std::vector<int> ps{19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73};
	for (std::vector<int>::iterator k = ks.begin(); k < ks.end(); k++)
		for (std::vector<int>::iterator p = ps.begin(); p < ps.end(); p++) {
			std::cout << *k << " DivisionHash " << *p << std::endl;
			test_h(*k, *p, DivisionHash(*p));
		}
	return 0;
}

int test_m() {
	std::vector<int> ks{7, 8, 9};
	std::vector<int> ms{1, 2, 3, 4, 5};
	for (std::vector<int>::iterator k = ks.begin(); k < ks.end(); k++)
		for (std::vector<int>::iterator m = ms.begin(); m < ms.end(); m++) {
			std::cout << *k << " MultiplicationHash " << *m << std::endl;
			test_h(*k, 1 << *m, MultiplicationHash(*k, *m, 0.6180339887));
		}
	return 0;
}

int test_u() {
	std::vector<int> ks{0, 1, 2, 3, 4, 5, 6, 7};
	std::vector<int> ps{19, 23, 29, 31, 37, 41, 43, 47, 53};
	std::vector<int> ms{131, 137, 139, 149, 151};
	for (std::vector<int>::iterator k = ks.begin(); k < ks.end(); k++)
		for (std::vector<int>::iterator p = ps.begin(); p < ps.end(); p++)
			for (std::vector<int>::iterator m = ms.begin(); m < ms.end(); m++) {
				std::cout << *k << " UniversalHash " << *p << ' ' << *m;
				std::cout << std::endl;
				test_h(*k, *m, UniversalHash(*p, *m));
			}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	test_d();
	test_m();
	test_u();
	return 0;
}
