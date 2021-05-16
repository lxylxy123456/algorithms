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

#include "PSquareMatrixMultiply.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "MatrixChainOrder.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(size_t n) {
	std::vector<int> buf_a, buf_b;
	random_integers(buf_a, 0, n, n * n);
	random_integers(buf_b, 0, n, n * n);
	Matrix<int> A(n, n, buf_a);
	Matrix<int> B(n, n, buf_b);
	std::cout << A << std::endl;
	std::cout << B << std::endl;
	Matrix<int> ans0 = SquareMatrixMultiply(A, B, 0);
	Matrix<int> ans1 = PSquareMatrixMultiply(A, B, 0);
	assert(ans0 == ans1);
	Matrix<int> ans2 = PMatrixMultiplyRecursive(A, B, 0);
	assert(ans1 == ans2);
	Matrix<int> ans3 = PMatrixMultiplyStrassen<int, 0>(A, B);
	assert(ans1 == ans3);
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	int N = 15;
	if (argc >= 2)
		N = 7;
	for (int n = 1; n < N; n++)
		test(n);
	return 0;
}
