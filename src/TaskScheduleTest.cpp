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

#include "TaskSchedule.hpp"

#include <set>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t n) {
	// prepare data
	std::set<Task<std::size_t>> S;
	std::vector<std::size_t> d, w;
	random_integers<std::size_t>(d, 1, n, n);
	random_integers<std::size_t>(w, 1, n, n);
	for (std::size_t i = 0; i < n; i++)
		S.insert(Task<std::size_t>(i, d[i], w[i]));
	TaskMatroid<std::size_t> M(S);
	output_integers(M.S, "\t");
	// call function
	std::vector<Task<std::size_t>> ans;
	TaskSchedule(M, ans);
	output_integers(ans, "\t");
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<int> ns = {1, 4, 16, 19, 20, 25, 100};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		test(*n);
	return 0;
}
