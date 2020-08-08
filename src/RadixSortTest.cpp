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

#include "RadixSort.hpp"
#include "utils.hpp"

#include <cassert>

using namespace algorithms;

#include "InsertSort.hpp"

const std::vector<int> ans1 = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
const std::vector<int> ans2 = {14, 8, 10, 4, 7, 9, 3, 2, 1};
const std::vector<int> ans3 = {19, 14, 10, 8, 7, 9, 3, 2, 4};
const std::vector<int> ans4 = {19, 14, 10, 11, 7, 9, 3, 2, 8};

int test(int n, int k) {
	std::vector<int> a;
	random_integers(a, 0, pow(2, k) - 1, n);
	std::vector<int> b(a);
	InsertSort(a);
	RadixSort(b, k);
	output_integers(a);
	output_integers(b);
	assert(a == b);
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<int> ns{0, 1, 2, 5, 8, 19, 52, 100};
	std::vector<int> ks{0, 1, 2, 5, 8};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<int>::iterator k = ks.begin(); k < ks.end(); k++)
			test(*n, *k);
	return 0;
}
