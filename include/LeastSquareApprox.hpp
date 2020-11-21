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

#ifndef ALGORITHMS_LEASTSQUAREAPPROX
#define ALGORITHMS_LEASTSQUAREAPPROX

#include "LUPSolve.hpp"

namespace algorithms {

template <typename T>
Matrix<T> LeastSquareApprox(Matrix<T>& A, Matrix<T>& y) {
	Matrix<T> AT = A.transpose();
	Matrix<T> b = SquareMatrixMultiply(AT, y, (T) 0);
	Matrix<T> ATA = SquareMatrixMultiply(AT, A, (T) 0);
	PT pi = LUPDecomposition(ATA);
	Matrix<T> c = LUPSolve(ATA, ATA, pi, b);
	return c;
}

}

#endif
