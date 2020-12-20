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

#include "ActivitySelector.hpp"

#include <cassert>
#include <vector>

#include "Quicksort.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(size_t n) {
	std::vector<Event<int>> e, ans1, ans2;
	// prepare event list
	std::vector<int> time_list;
	random_integers(time_list, 0, n - 1, 2 * n);
	for (size_t i = 0; i < n; i++)
		e.push_back(Event<int>(time_list[2 * i], time_list[2 * i + 1]));
	Quicksort(e.begin(), e.end());
	output_integers(e);
	// compute
	RecursiveActivitySelector(e, 0, ans1);
	GreedyActivitySelector(e, ans2);
	assert(ans1 == ans2);
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<int> ns = {1, 4, 16, 19, 20, 25, 100, 1000, 10240};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		test(*n);
	return 0;
}
