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

#include "SquareMatrixMultiply.hpp"

#include <cassert>
#include "utils.hpp"

using namespace algorithms;

int test(int n) {
	std::vector<int> buf_a, buf_b;
	random_integers(buf_a, 0, n, n * n);
	random_integers(buf_b, 0, n, n * n);
	Matrix<int> A(n, n, buf_a);
	Matrix<int> B(n, n, buf_b);
	std::cout << A << std::endl;
	std::cout << B << std::endl;
	Matrix<int> ans1(A);
	{
		std::cout << "SquareMatrixMultiply" << std::endl;
		ans1 = SquareMatrixMultiply(A, B, 0);
		std::cout << ans1 << std::endl;
	}
	{
		std::cout << "SquareMatrixMultiplyRecursive" << std::endl;
		Matrix<int> ans2 = SquareMatrixMultiplyRecursive(A, B, 0);
		std::cout << ans2 << std::endl;
		assert(ans1 == ans2);
	}
	{
		std::cout << "SquareMatrixMultiplyStrassen" << std::endl;
		Matrix<int> ans3 = SquareMatrixMultiplyStrassen<int, 0>(A, B);
		std::cout << ans3 << std::endl;
		assert(ans1 == ans3);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	test(1);
	test(2);
	test(10);
	test(49);
	test(100);
	return 0;
}
