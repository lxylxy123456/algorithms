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

#include "FindMaximumSubarray.hpp"

#include <cassert>
#include <numeric>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test_vector(int n) {
	std::vector<int> a;
	random_integers(a, -n, n, n);
	output_integers(a);
	sinfo<int> ans2 = FindMaximumSubarray(a);
	sinfo<int> ans1 = FindMaximumSubarray_On<int, 0>(a);
	int sum2 = std::accumulate(a.begin() + ans2.begin, a.begin() + ans2.end, 0);
	assert(sum2 == ans2.sum);
	int sum1 = std::accumulate(a.begin() + ans1.begin, a.begin() + ans1.end, 0);
	assert(sum1 == ans1.sum);
	assert(ans2.sum == ans1.sum);
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	test_vector(1);
	test_vector(2);
	test_vector(10);
	test_vector(49);
	test_vector(100);
	return 0;
}
