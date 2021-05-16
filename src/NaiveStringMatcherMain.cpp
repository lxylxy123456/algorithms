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

#include "NaiveStringMatcher.hpp"

#include <vector>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t n = get_argv(argc, argv, 1, 40);
	const std::size_t m = get_argv(argc, argv, 2, 3);
	const std::size_t d = get_argv(argc, argv, 3, 2);
	std::vector<char> S, P;
	random_integers<char>(S, 'a', 'a' + d, n);
	random_integers<char>(P, 'a', 'a' + d, m);
	output_integers(S, "");
	output_integers(P, "");
	std::vector<std::size_t> ans;
	NaiveStringMatcher(S, P, ans);
	output_integers(ans);
	return 0;
}
