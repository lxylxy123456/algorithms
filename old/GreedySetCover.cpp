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

#ifndef MAIN
#define MAIN
#define MAIN_GreedySetCover
#endif

#ifndef FUNC_GreedySetCover
#define FUNC_GreedySetCover

#include <cassert>
#include <iomanip>
#include <set>
#include "utils.h"

#define set_T typename std::set<T>

template <typename T>
std::set<size_t> GreedySetCover(set_T& X, std::vector<set_T>& F) {
	size_t U_size = X.size();
	std::set<size_t> e;
	std::vector<set_T> FU = F;
	while (U_size) {
		size_t s, s_size = 0;
		for (size_t i = 0; i < FU.size(); i++) {
			size_t i_size = FU[i].size();
			if (s_size < i_size) {
				s = i;
				s_size = i_size;
			}
		}
		assert(s_size);
		for (auto i = FU[s].begin(); i != FU[s].end(); i++) {
			U_size--;
			for (size_t j = 0; j < FU.size(); j++)
				if (j != s)
					FU[j].erase(*i);
		}
		FU[s].clear();
		e.insert(s);
	}
	return e;
}
#endif

#ifdef MAIN_GreedySetCover
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 10);
	const size_t m = get_argv(argc, argv, 2, 10);
	const size_t l = get_argv(argc, argv, 2, 20);
	using T = size_t;
	set_T X;
	std::vector<set_T> F;
	for (size_t i = 0; i < n; i++)
		X.insert(i);
    std::random_device rd;
    std::uniform_int_distribution<T> d1(0, n * m);
	for (size_t i = 0; i < m; i++) {
		set_T s;
		for (size_t j = 0; j < n; j++)
			if (d1(rd) < l)
				s.insert(j);
		F.push_back(s);
	}
    std::uniform_int_distribution<T> d2(0, m - 1);
    for (size_t i = 0; i < n; i++)
    	F[d2(rd)].insert(i);
    std::uniform_int_distribution<T> d3(0, n - 1);
    for (size_t i = 0; i < m; i++)
    	F[i].insert(d3(rd));
    std::set<size_t> ans = GreedySetCover(X, F);
    for (size_t i = 0; i < m; i++) {
    	if (ans.find(i) != ans.end())
	    	std::cout << "+ ";
	    else
	    	std::cout << "  ";
	    for (size_t j = 0; j < n; j++) {
	    	if (F[i].find(j) != F[i].end())
	    		std::cout << std::setw(4) << j;
	    	else
	    		std::cout << std::string(4, ' ');
	    }
	    std::cout << std::endl;
    }
	return 0;
}
#endif

