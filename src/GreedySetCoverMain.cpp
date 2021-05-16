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

#include "GreedySetCover.hpp"

#include <iomanip>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t n = get_argv(argc, argv, 1, 10);
	const std::size_t m = get_argv(argc, argv, 2, 10);
	const std::size_t l = get_argv(argc, argv, 3, 20);
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
	for (std::size_t i = 0; i < m; i++) {
		if (ans.find(i) != ans.end())
			std::cout << "+ ";
		else
			std::cout << "  ";
		for (std::size_t j = 0; j < n; j++) {
			if (F[i].find(j) != F[i].end())
				std::cout << std::setw(4) << j;
			else
				std::cout << std::string(4, ' ');
		}
		std::cout << std::endl;
	}
	return 0;
}
