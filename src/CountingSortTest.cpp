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

#include "CountingSort.hpp"
#include "utils.hpp"

#include <cassert>

#include "InsertSort.hpp"

using namespace algorithms;

int test(int n, int k) {
	std::vector<int> a;
	random_integers(a, 0, k - 1, n);
	std::vector<int> b(a), c(n, 0);
	InsertSort(a);
	output_integers(a);
	CountingSort(b, c, k, Self<int>);
	output_integers(c);
	assert(a == c);
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<int> ns{0, 1, 2, 5, 8, 19, 52, 100};
	std::vector<int> ks{1, 2, 5, 8, 19, 52, 100};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<int>::iterator k = ks.begin(); k < ks.end(); k++)
			test(*n, *k);
	return 0;
}
