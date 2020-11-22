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

#include "NaiveStringMatcher.hpp"
#include "utils.hpp"

#include <cassert>

using namespace algorithms;

template <typename T>
int test(size_t n, size_t m, size_t d) {
	std::vector<T> S, P;
	random_integers<T>(S, 'a', 'a' + d, n);
	random_integers<T>(P, 'a', 'a' + d, m);
	output_integers(S);
	output_integers(P);
	std::vector<size_t> ans;
	NaiveStringMatcher(S, P, ans);
	for (std::vector<size_t>::iterator i = ans.begin(); i < ans.end(); i++)
		assert(std::vector<T>(S.begin() + *i, S.begin() + *i + m) == P);
	output_integers(ans);
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<size_t> ns = {2, 5, 10, 23, 49, 100};
	for (std::vector<size_t>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<size_t>::iterator m = ns.begin(); m < ns.end(); m++) {
			for (int d = 1; d < 20; d += 2)
				test<char>(*m, *n, d);
			for (int d = 2; d < 1000; d += 10)
				test<int>(*m, *n, d);
		}
	return 0;
}
