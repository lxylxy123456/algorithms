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

#include "ChainedHash.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(int n, int m) {
	std::cout << n << ' ' << m << std::endl;
	ChainedHash<int> D(n);
	for (int i = 0; i < m; i++)
		D.ChainedHashInsert(i, i ^ 0xaa);
	for (int i = 0; i < m; i++) {
		Element<Pair<int>>* searched = D.ChainedHashSearch(i);
		assert(searched->key.key == (std::size_t) i);
		assert(searched->key.value == (i ^ 0xaa));
		if (i % 2 == 0)
			D.ChainedHashDelete(searched);
		else if (i % 4 == 3)
			D.ChainedHashInsert(i, i ^ 0x55);
	}
	for (int i = 0; i < m; i++) {
		Element<Pair<int>>* searched = D.ChainedHashSearch(i);
		if (i % 2 == 0)
			assert(!searched);
		else if (i % 4 == 3)
			assert(searched->key.value == (i ^ 0x55));
		else
			assert(searched->key.value == (i ^ 0xaa));
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<int> ns{1, 2, 5, 8, 19, 52, 100};
	std::vector<int> ms{1, 2, 5};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<int>::iterator m = ms.begin(); m < ms.end(); m++)
			test(*n, *n * *m);
	return 0;
}
