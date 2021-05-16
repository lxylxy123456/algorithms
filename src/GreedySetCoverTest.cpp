//
//  algorithm - some algorithns in "Introduction to Algorithns", third edition
//  Copyright (C) 2020  lxylxy123456
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terns of the GNU Affero General Public License as
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

#include "GreedySetCover.hpp"

#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t n, std::size_t m, std::size_t l) {
	std::cout << n << ' ' << m << ' ' << l << std::endl;
	using T = std::size_t;
	set_T X;
	std::vector<set_T> F;
	for (std::size_t i = 0; i < n; i++)
		X.insert(i);
	std::uniform_int_distribution<T> d1(0, n * m);
	for (std::size_t i = 0; i < m; i++) {
		set_T s;
		for (std::size_t j = 0; j < n; j++)
			if (random_integer(d1) < l)
				s.insert(j);
		F.push_back(s);
	}
	std::uniform_int_distribution<T> d2(0, m - 1);
	for (std::size_t i = 0; i < n; i++)
		F[random_integer(d2)].insert(i);
	std::uniform_int_distribution<T> d3(0, n - 1);
	for (std::size_t i = 0; i < m; i++)
		F[i].insert(random_integer(d3));
	std::set<std::size_t> ans = GreedySetCover(X, F);
	std::vector<std::size_t> covered(n, 0);
	for (std::size_t i = 0; i < m; i++)
		for (std::size_t j = 0; j < n; j++)
			if (F[i].find(j) != F[i].end())
				covered[j]++;
	for (std::size_t i = 0; i < n; i++)
		assert(covered[i]);
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<std::size_t> ns = {2, 5, 10, 23, 49, 100, 200};
	for (std::vector<std::size_t>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<std::size_t>::iterator m = ns.begin(); m < ns.end(); m++)
			for (std::vector<std::size_t>::iterator l = ns.begin(); l < ns.end();
				l++)
				test(*n, *m, *l);
	return 0;
}
