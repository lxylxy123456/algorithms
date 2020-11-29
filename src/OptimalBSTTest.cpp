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

#include "OptimalBST.hpp"
#include "utils.hpp"

#include <cassert>
#include <vector>

using namespace algorithms;

int test(size_t n) {
	SIZT_1D p, q;
	random_integers<size_t>(p, 1, n, n);
	random_integers<size_t>(q, 1, n, n + 1);
	output_integers(p);
	output_integers(q);
	SIZT_2D root = OptimalBST(p, q, n);
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j <= i; j++)
			assert(root[i][j] == 0);
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<int> ns = {1, 4, 16, 19, 20, 25, 100};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		test(*n);
	return 0;
}
