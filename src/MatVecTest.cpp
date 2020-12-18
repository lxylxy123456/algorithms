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

#include "MatVec.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "MatrixChainOrder.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(size_t n) {
	std::vector<int> buf_A, buf_x;
	random_integers(buf_A, 0, n, n * n);
	random_integers(buf_x, 0, n, n);
	Matrix<int> A(n, n, buf_A);
	Matrix<int> x(n, 1, buf_x);
	std::cout << A << std::endl;
	std::cout << x << std::endl;
	Matrix<int> y0 = MatrixMultiply(A, x);
	Matrix<int> y1(n, 1, 0), y2(n, 1, 0), y3(n, 1, 0);
	MatVec(A, x, y1);
	assert(y0 == y1);
	MatVecRecursive(A, x, y2);
	assert(y1 == y2);
	MatVecWrong(A, x, y3);
	if (y1 == y3)
		return 0;
	else
		return 1;
}

int main(int argc, char *argv[]) {
	int failed = 0;
	int I = 100, N = 40;
	bool test_failed = true;
	if (argc >= 2) {
		I = 2;
		N = 10;
		test_failed = false;
	}
	for (int i = 0; i < I && !failed; i++)
		for (int n = 1; n < N; n++)
			failed |= test(n);
	if (test_failed)
		assert(failed);
	return 0;
}
