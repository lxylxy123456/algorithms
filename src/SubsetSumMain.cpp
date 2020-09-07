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

#include "SubsetSum.hpp"

#include <cassert>
#include <iomanip>
#include <set>
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 100);
	const size_t m = get_argv(argc, argv, 2, 100);
	using T = int;
	using FT = float;
	const T t = get_argv(argc, argv, 3, 500);
	const FT e = get_argv(argc, argv, 4, 0.9);
	std::vector<T> S_int;
	random_integers(S_int, 1, m, n);
	set_T S;
	for (auto i = S_int.begin(); i != S_int.end(); i++)
		S.insert(*i);
	output_integers(S);
	std::cout << "t = " << t << std::endl;
	std::cout << "exact  = " << ExactSubsetSum(S, t) << std::endl;
	std::cout << "approx = " << ApproxSubsetSum(S, t, e) << std::endl;
	return 0;
}
