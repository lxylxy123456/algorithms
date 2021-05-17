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

#include "CutRod.hpp"

#include <iomanip>
#include <iostream>
#include <vector>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	using T = int;
	const std::size_t n = get_argv(argc, argv, 1, 16);
	const std::size_t compute = get_argv(argc, argv, 2, 15);
	std::vector<int> l;
	random_integers(l, 0, n - 1, n);
	std::vector<int> p = {0};
	for (std::vector<int>::iterator i = l.begin(); i != l.end(); i++)
		p.push_back(*i + *(p.end() - 1));
	output_integers(p);
	if (compute >> 0 & 1) {
		std::cout << std::left << std::setw(24) << "CutRod";
		std::cout << CutRod(p, n) << std::endl;
	}
	if (compute >> 1 & 1) {
		std::cout << std::left << std::setw(24) << "MemorizedCutRod";
		std::cout << MemorizedCutRod(p, n) << std::endl;
	}
	if (compute >> 2 & 1) {
		std::cout << std::left << std::setw(24) << "BottomUpCutRod";
		std::cout << BottomUpCutRod(p, n) << std::endl;
	}
	if (compute >> 3 & 1) {
		std::cout << std::left << std::setw(24) << "ExtendedBottomUpCutRod";
		CUT_ROD_INFO ans = PrintCutRodSolution(p, n);
		std::cout << ans.first << std::endl;
		output_integers(ans.second);
	}
	return 0;
}
