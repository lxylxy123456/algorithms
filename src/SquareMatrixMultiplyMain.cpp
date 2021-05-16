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

#include "SquareMatrixMultiply.hpp"

#include <iostream>
#include <vector>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t n = get_argv(argc, argv, 1, 16);
	const std::size_t compute = get_argv(argc, argv, 2, 7);
	std::vector<int> buf_a, buf_b;
	random_integers(buf_a, 0, n, n * n);
	random_integers(buf_b, 0, n, n * n);
	Matrix<int> A(n, n, buf_a);
	Matrix<int> B(n, n, buf_b);
	std::cout << A << std::endl;
	std::cout << B << std::endl;
	Matrix<int> ans1(A);
	if (compute >> 0 & 1) {
		std::cout << "SquareMatrixMultiply" << std::endl;
		ans1 = SquareMatrixMultiply(A, B, 0);
		std::cout << ans1 << std::endl;
	}
	if (compute >> 1 & 1) {
		std::cout << "SquareMatrixMultiplyRecursive" << std::endl;
		Matrix<int> ans2 = SquareMatrixMultiplyRecursive(A, B, 0);
		std::cout << ans2 << std::endl;
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (ans1 == ans2) << std::endl;
	}
	if (compute >> 2 & 1) {
		std::cout << "SquareMatrixMultiplyStrassen" << std::endl;
		Matrix<int> ans3 = SquareMatrixMultiplyStrassen<int, 0>(A, B);
		std::cout << ans3 << std::endl;
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (ans1 == ans3) << std::endl;
	}
	return 0;
}
