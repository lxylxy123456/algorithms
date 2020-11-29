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

#include "CutRod.hpp"
#include "utils.hpp"

#include <cassert>
#include <numeric>

using namespace algorithms;

int test(int n) {
	using T = int;
	std::vector<int> l;
	random_integers(l, 0, n - 1, n);
	std::vector<int> p = {0};
	for (std::vector<int>::iterator i = l.begin(); i != l.end(); i++)
		p.push_back(*i + *(p.end() - 1));
	output_integers(p);
	int mcr = MemorizedCutRod(p, n);
	int bucr = BottomUpCutRod(p, n);
	assert(mcr == bucr);
	CUT_ROD_INFO ebucr = PrintCutRodSolution(p, n);
	assert(bucr == ebucr.first);
	assert(std::accumulate(ebucr.second.begin(), ebucr.second.end(), 0) == n);
	int tot = 0;
	for (std::vector<size_t>::iterator i = ebucr.second.begin();
		i != ebucr.second.end(); i++)
		tot += p[*i];
	assert(tot == ebucr.first);
	output_integers(ebucr.second);
	if (n <= 20) {
		int cr = CutRod(p, n);
		assert(ebucr.first == cr);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	test(0);
	test(1);
	test(4);
	test(16);
	test(19);
	test(20);
	test(47);
	test(100);
	return 0;
}
