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

#include "FindMaximumSubarray.hpp"

#include <vector>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	std::vector<int> a;
	int n = get_argv(argc, argv, 1, 10);
	random_integers(a, -n, n, n);
	output_integers(a);
	sinfo<int> ans2 = FindMaximumSubarray(a);
	sinfo<int> ans1 = FindMaximumSubarray_On<int, 0>(a);
	std::vector<int> sub_array2(a.begin() + ans2.begin, a.begin() + ans2.end);
	std::vector<int> sub_array1(a.begin() + ans1.begin, a.begin() + ans1.end);
	output_integers(sub_array2);
	output_integers(sub_array1);
	return 0;
}
