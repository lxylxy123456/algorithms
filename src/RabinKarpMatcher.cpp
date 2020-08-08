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

#include "RabinKarpMatcher.hpp"

#include "utils.hpp"
#include "ModularExponentiation.hpp"
#include "NaiveStringMatcher.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 40);
	const size_t m = get_argv(argc, argv, 2, 3);
	const size_t d = get_argv(argc, argv, 3, 2);
	const size_t compute = get_argv(argc, argv, 4, 1);
	std::vector<char> S, P;
	random_integers<char>(S, 'a', 'a' + d, n);
	random_integers<char>(P, 'a', 'a' + d, m);
	output_integers(S, "");
	output_integers(P, "");
	std::vector<size_t> ans;
	RabinKarpMatcher(S, P, d, 1000000007, 'a', ans);
	output_integers(ans);
	if (compute) {
		std::vector<size_t> ans1;
		NaiveStringMatcher(S, P, ans1);
		output_integers(ans1);
		std::cout << std::boolalpha << (ans == ans1) << std::endl;
	}
	return 0;
}
