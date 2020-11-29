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

#include "Quicksort.hpp"

#include <cassert>
#include <vector>

#include "InsertSort.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(int n) {
	std::vector<int> a;
	random_integers(a, 0, n - 1, n);
	std::vector<int> b(a), c(a);
	output_integers(a);
	InsertSort(a);
	Quicksort(b.begin(), b.end());
	RandomizedQuicksort(c.begin(), c.end());
	output_integers(a);
	output_integers(b);
	output_integers(c);
	assert(a == b && a == c);
	return 0;
}

int main(int argc, char *argv[]) {
	test(0);
	test(1);
	test(2);
	test(5);
	test(8);
	test(19);
	test(52);
	test(100);
	return 0;
}
