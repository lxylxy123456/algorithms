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

#include "MatVec.hpp"

#include <iostream>
#include <vector>

#include "SquareMatrixMultiply.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	size_t n = get_argv(argc, argv, 1, 10);
	size_t compute = get_argv(argc, argv, 2, 7);
	std::vector<int> buf_A, buf_x;
	random_integers(buf_A, 0, n, n * n);
	random_integers(buf_x, 0, n, n);
	Matrix<int> A(n, n, buf_A);
	Matrix<int> x(n, 1, buf_x);
	std::cout << A << std::endl;
	std::cout << x << std::endl;
	Matrix<int> y1(n, 1, 0), y2(n, 1, 0), y3(n, 1, 0);
	if (compute >> 0 & 1) {
		MatVec(A, x, y1);
		std::cout << y1 << std::endl;
	}
	if (compute >> 1 & 1) {
		MatVecRecursive(A, x, y2);
		std::cout << y2;
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (y1 == y2) << std::endl;
		std::cout << std::endl;
	}
	if (compute >> 2 & 1) {
		MatVecWrong(A, x, y3);
		std::cout << y3;
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (y1 == y3) << std::endl;
		std::cout << std::endl;
	}
	return 0;
}
