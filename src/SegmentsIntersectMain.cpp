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

#include "SegmentsIntersect.hpp"

#include <iostream>
#include <vector>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t n = get_argv(argc, argv, 1, 200);
	std::vector<int> b;
	random_integers(b, -n, n, 8);
	using T = double;
	Vector<T> p1(b[0], b[1]), p2(b[2], b[3]), p3(b[4], b[5]), p4(b[6], b[7]);
	std::cout << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?>"
				 << std::endl;
	std::cout << "<svg height=\"" << 2 * n << "\" width=\"" << 2 * n << "\">"
				 << std::endl;
	std::cout << "\t<rect fill=\"#ffffff\" x=\"0\" y=\"0\" width=\"" << 2 * n
				 << "\" height=\"" << 2 * n << "\"/>" << std::endl;
	print_seg(p1, p2, (T) n, "#ff0000");
	print_seg(p3, p4, (T) n, "#00ff00");
	std::cout << "\t<text x=\"" << n << "\" y=\"" << n << "\">"
				 << std::boolalpha << SegmentsIntersect(p1, p2, p3, p4)
				 << "</text>" << std::endl;
	std::cout << "</svg>" << std::endl;
	return 0;
}
