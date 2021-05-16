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

#include "BucketSort.hpp"

#include <cassert>
#include <vector>

#include "InsertSort.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(int n) {
	std::vector<int> a;
	random_integers(a, 0, n - 1, n);
	std::vector<int> b(a);
	InsertSort(a);
	output_integers(a);
	BucketSort<int>(b, 0, n);
	output_integers(b);
	assert(a == b);
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<int> ns{0, 1, 2, 5, 8, 19, 52, 100};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		test(*n);
	return 0;
}
