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

#include "SegmentsIntersect.hpp"

#include <cassert>

#include "utils.hpp"

using namespace algorithms;

int test(double p1x, double p1y, double p2x, double p2y, double p3x, double p3y,
		double p4x, double p4y, bool expected) {
	using T = double;
	Vector<T> p1(p1x, p1y), p2(p2x, p2y), p3(p3x, p3y), p4(p4x, p4y);
	assert(expected == SegmentsIntersect(p1, p2, p3, p4));
	return 0;
}

int main(int argc, char *argv[]) {
	test(1, 0, 0, 1, 0, 0, 1, 1, true);
	test(1, 1, 0, 1, 0, 0, 1, 0, false);
	test(10, 10, 50, 50, 29, 29, 70, 0, true);
	test(10, 10, 50, 50, 11, 10, 51, 50, false);
	test(10, 10, 50, 50, 11, 10, 50, 51, true);
	test(10, 10, 50, 50, 10, 10, 50, 50, true);
	return 0;
}
