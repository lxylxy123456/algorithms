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

#ifndef ALGORITHMS_MATRIXINVERSE
#define ALGORITHMS_MATRIXINVERSE

#include "LUPSolve.hpp"

namespace algorithms {

template <typename T>
Matrix<T> MatrixInverse(Matrix<T>& A) {
	const size_t n = A.rows;
	Matrix<T> LU(A), ans(n, 0, 0), b(n, 1, 0);
	PT pi = LUPDecomposition(LU);
	for (size_t i = 0; i < n; i++) {
		b[i][0] = 1;
		Matrix<T> x = LUPSolve(LU, LU, pi, b);
		ans = ans.concat_h(x);
		b[i][0] = 0;
	}
	return ans;
}

}

#endif
