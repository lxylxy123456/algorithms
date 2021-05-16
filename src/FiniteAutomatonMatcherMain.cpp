//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#include "FiniteAutomatonMatcher.hpp"

#include <iostream>
#include <vector>

#include "NaiveStringMatcher.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t n = get_argv(argc, argv, 1, 40);
	const std::size_t m = get_argv(argc, argv, 2, 3);
	const std::size_t d = get_argv(argc, argv, 3, 2);
	const std::size_t compute = get_argv(argc, argv, 4, 1);
	std::vector<char> S, P;
	random_integers<char>(S, 'a', 'a' + d, n);
	random_integers<char>(P, 'a', 'a' + d, m);
	output_integers(S, "");
	output_integers(P, "");
	std::vector<std::vector<std::size_t>> delta;
	ComputeTransitionFunction(P, d, 'a', delta);
	std::vector<std::size_t> ans;
	FiniteAutomatonMatcher(S, delta, 'a', ans);
	output_integers(ans);
	if (compute) {
		std::vector<std::size_t> ans1;
		NaiveStringMatcher(S, P, ans1);
		output_integers(ans1);
		std::cout << std::boolalpha << (ans == ans1) << std::endl;
	}
	return 0;
}
