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

#include "ClosestPairPoints.hpp"

#include <cassert>
#include <vector>

#include "SegmentsIntersect.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t n, size_t m) {
	while (true) {
		std::vector<int> b;
		random_integers(b, -n, n, m * 2);
		output_integers(b);
		using T = double;
		std::vector<Vector<T>> Q;
		Q.reserve(m);
		for (std::size_t i = 0; i < m; i++)
			Q.push_back(Vector<T>(b[2 * i + 0], b[2 * i + 1]));
		bool retry = false;
		for (std::size_t i = 0; i < m; i++)
			for (std::size_t j = i + 1; j < m; j++)
				if (Q[i] == Q[j])
					retry = true;
		if (retry)
			continue;
		VecPair<T> ans = ClosestPairPoints(Q);
		bool found_a = false, found_b = false;
		for (std::size_t i = 0; i < m; i++) {
			found_a = found_a || Q[i] == ans.a;
			found_b = found_b || Q[i] == ans.b;
			for (std::size_t j = i + 1; j < m; j++) {
				assert(ans.Dist() <= (Q[i] - Q[j]).Length());
			}
		}
		assert(found_a && found_b);
		return 0;
	}
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<std::size_t> ns = {100, 1024, 10000};
	std::vector<std::size_t> ms = {2, 5, 10, 23, 49, 100};
	for (std::vector<std::size_t>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<std::size_t>::iterator m = ms.begin(); m < ms.end(); m++)
			test(*n, *m);
	return 0;
}
