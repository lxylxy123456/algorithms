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

#include "SubsetSum.hpp"
#include "utils.hpp"

#include <cassert>

using namespace algorithms;

template <typename T, typename FT>
int test(size_t n, size_t m, T t, FT e) {
	std::vector<T> S_int;
	random_integers(S_int, 1, m, n);
	set_T S;
	for (auto i = S_int.begin(); i != S_int.end(); i++)
		S.insert(*i);
	std::cout << t << '\t';
	output_integers(S);
	T exact = ExactSubsetSum(S, t);
	T approx = ApproxSubsetSum(S, t, e);
	assert(exact <= t);
	assert(approx <= exact);
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<size_t> ns = {10, 23, 49, 100};
	std::vector<int> ts = {50, 100, 500, 2000, 9000};
	for (std::vector<size_t>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<size_t>::iterator m = ns.begin(); m < ns.end(); m++)
			for (std::vector<int>::iterator t = ts.begin(); t < ts.end(); t++)
				for (float e = 0.1; e < 1; e += 0.1)
					test(*n, *m, *t, e);
	return 0;
}
