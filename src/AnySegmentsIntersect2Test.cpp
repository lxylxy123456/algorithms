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

#include "AnySegmentsIntersect.hpp"
#include "utils.hpp"

#include "SegmentsIntersect.hpp"
#include <cassert>

using namespace algorithms;

int test(size_t n, size_t m) {
	std::vector<int> b;
	random_integers(b, -n, n, m * 4);
	output_integers(b);
	using T = double;
	T x;
	std::vector<Segment<T>> S;
	S.reserve(m);
	for (size_t i = 0; i < m; i++) {
		if (b[4 * i + 0] == b[4 * i + 2])
			b[4 * i + 2]++;
		Vector<T> s(b[4 * i + 0], b[4 * i + 1]), e(b[4 * i + 2], b[4 * i + 3]);
		S.push_back(Segment<T>(s, e, x));
	}
	bool actual, expected = AnySegmentsIntersect(S);
	for (size_t i = 0; i < m; i++)
		for (size_t j = i + 1; j < m; j++)
			if (SegmentsIntersect(S[i].a, S[i].b, S[j].a, S[j].b)) {
				actual = true;
				break;
			}
	assert(actual == expected);
	return 0;
}

int main(int argc, char *argv[]) {
	std::cout << random_seed_get() << std::endl;
	std::vector<size_t> ns = {100, 101, 102};
	std::vector<size_t> ms = {2, 5, 10, 23, 49};
	for (std::vector<size_t>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<size_t>::iterator m = ms.begin(); m < ms.end(); m++)
			test(*n, *m);
	return 0;
}
