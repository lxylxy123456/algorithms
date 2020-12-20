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

#include "RandomizedSelect.hpp"

#include <cassert>
#include <vector>

#include "Quicksort.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(size_t n, size_t i) {
	std::vector<int> a;
	random_integers(a, 0, n - 1, n);
	std::vector<int> b(a);
	int ans1, ans2, ans3;
	output_integers(a);
	Quicksort(b.begin(), b.end());
	ans1 = b[i];
	ans2 = RandomizedSelect(a, i);
	assert(ans1 == ans2);
	ans3 = RandomizedSelectIter(a, i);
	assert(ans1 == ans3);
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<size_t> ns{1, 2, 5, 8, 19, 52, 100};
	for (std::vector<size_t>::iterator n = ns.begin(); n < ns.end(); n++)
		for (size_t i = 0; i < *n; i++)
			test(*n, i);
	return 0;
}
