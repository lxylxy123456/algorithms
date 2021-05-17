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

#include "Greedy.hpp"

#include <cassert>
#include <set>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t n) {
	// prepare data
	std::set<std::size_t> S, ans;
	for (std::size_t i = 0; i < n; i++)
		S.insert(i);
	Matroid<std::size_t> M(S);
	std::vector<std::size_t> weights;
	std::size_t (*f)(std::size_t) = [](std::size_t a) { return a; };
	for (std::set<std::size_t>::iterator i = M.S.begin(); i != M.S.end(); i++)
		weights.push_back(f(*i));
	output_integers(M.S, "\t");
	output_integers(weights, "\t");
	// call function
	Greedy<std::size_t, std::size_t>(M, f, ans);
	output_integers(ans);
	assert(ans.size() == n);
	for (std::size_t i = 0; i < n; i++)
		assert(ans.find(i) != ans.end());
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<int> ns = {1, 4, 16, 19, 20, 25, 100};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		test(*n);
	return 0;
}
