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

#include "DirectAddress.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "utils.hpp"

using namespace algorithms;

int test(int n) {
	std::cout << n << std::endl;
	DirectAddress<int> D(n);
	for (int i = 0; i < n; i++)
		D.DirectAddressInsert(i, i ^ 0xaa);
	for (int i = 0; i < n; i++) {
		assert(*D.DirectAddressSearch(i) == (i ^ 0xaa));
		if (i % 2 == 0)
			D.DirectAddressDelete(i);
		else if (i % 4 == 3)
			D.DirectAddressInsert(i, i ^ 0x55);
	}
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0)
			assert(!D.DirectAddressSearch(i));
		else if (i % 4 == 3)
			assert(*D.DirectAddressSearch(i) == (i ^ 0x55));
		else
			assert(*D.DirectAddressSearch(i) == (i ^ 0xaa));
	}
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<int> ns{1, 2, 5, 8, 19, 52, 100};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		test(*n);
	return 0;
}
