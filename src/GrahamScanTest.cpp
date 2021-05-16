//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#include "GrahamScan.hpp"

#include <cassert>
#include <vector>

#include "SegmentsIntersect.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(size_t n, size_t m) {
	std::vector<int> b;
	random_integers(b, -n, n, m * 2);
	output_integers(b);
	using T = double;
	std::vector<Vector<T>> Q, S;
	Q.reserve(m);
	for (size_t i = 0; i < m; i++)
		Q.push_back(Vector<T>(b[2 * i + 0], b[2 * i + 1]));
	GrahamScan(Q, S);
	assert(S.size() >= 3);
	T cross1 = (S[0] - S[1]).Cross(S[2] - S[1]);
	for (size_t i = 0; i < S.size(); i++) {
		Vector<T> a = S[i], b, c;
		if (i == S.size() - 2) {
			b = S[i + 1];
			c = S[0];
		} else if (i == S.size() - 1) {
			b = S[0];
			c = S[1];
		} else {
			b = S[i + 1];
			c = S[i + 2];
		}
		assert((a - b).Cross(c - b) * cross1 > 0);
		bool found = false;
		for (size_t i = 0; i < m; i++) {
			assert((a - b).Cross(Q[i] - b) * cross1 >= 0);
			assert((Q[i] - b).Cross(c - b) * cross1 >= 0);
			found = found || a == Q[i];
		}
		assert(found);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<size_t> ns = {100, 1024, 10000};
	std::vector<size_t> ms = {3, 5, 10, 23, 49, 100};
	for (std::vector<size_t>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<size_t>::iterator m = ms.begin(); m < ms.end(); m++)
			test(*n, *m);
	return 0;
}
