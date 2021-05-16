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

#include "AnySegmentsIntersect.hpp"

#include <iostream>
#include <vector>

#include "RedBlackTree.hpp"
#include "SegmentsIntersect.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 200);
	const size_t m = get_argv(argc, argv, 2, 5);
	std::vector<int> b;
	random_integers(b, -n, n, m * 4);
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
	std::cout << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?>"
				 << std::endl;
	std::cout << "<svg height=\"" << 2 * n << "\" width=\"" << 2 * n << "\">"
				 << std::endl;
	std::cout << "\t<rect fill=\"#ffffff\" x=\"0\" y=\"0\" width=\"" << 2 * n
				 << "\" height=\"" << 2 * n << "\"/>" << std::endl;
	for (auto i = S.begin(); i != S.end(); i++)
		print_seg(i->a, i->b, (T) n, "#000000");
	std::cout << "\t<text x=\"" << n << "\" y=\"" << n << "\">"
				 << std::boolalpha << AnySegmentsIntersect(S)
				 << "</text>" << std::endl;
	std::cout << "</svg>" << std::endl;
	return 0;
}
