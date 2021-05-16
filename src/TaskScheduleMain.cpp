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

#include "TaskSchedule.hpp"

#include <set>
#include <vector>

#include "Greedy.hpp"
#include "utils.hpp"

using namespace algorithms;

template <typename T>
T f(Task<T> x) { return x.p; }

int main(int argc, char *argv[]) {
	const std::size_t n = get_argv(argc, argv, 1, 7);
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
