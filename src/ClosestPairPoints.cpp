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

#include "ClosestPairPoints.hpp"

#include <algorithm>
#include <cassert>
#include <unordered_set>
#include "utils.hpp"
#include "SegmentsIntersect.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 200);
	const size_t m = get_argv(argc, argv, 2, 10);
	std::vector<int> b;
	random_integers(b, -n, n, m * 2);
	using T = double;
	std::vector<Vector<T>> Q, S;
	Q.reserve(m);
	for (size_t i = 0; i < m; i++)
		Q.push_back(Vector<T>(b[2 * i + 0], b[2 * i + 1]));
	VecPair<T> ans = ClosestPairPoints(Q);
	std::cout << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?>"
				 << std::endl;
	std::cout << "<svg height=\"" << 2 * n << "\" width=\"" << 2 * n << "\">"
				 << std::endl;
	std::cout << "\t<rect fill=\"#ffffff\" x=\"0\" y=\"0\" width=\"" << 2 * n
				 << "\" height=\"" << 2 * n << "\"/>" << std::endl;
	for (auto i = Q.begin(); i != Q.end(); i++)
		std::cout << "\t<circle cx=\"" << n + i->x + 1 << "\" cy=\""
				 << n + i->y + 1 << "\" r=\"2\"/>" << std::endl;
	print_seg(ans.a, ans.b, (T) n, "#00ff00");
	std::cout << "</svg>" << std::endl;
	return 0;
}
