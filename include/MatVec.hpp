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

#ifndef ALGORITHMS_MATVEC
#define ALGORITHMS_MATVEC

#include <thread>
#include "utils.h"

#include "SquareMatrixMultiply.hpp"

namespace algorithms {

template <typename T, typename F>
void parallel_for(T i1, T i2, F func) {
	if (i1 == i2 - 1)
		func(i1);
	else {
		T mid = (i1 + i2) / 2;
		std::thread t1(parallel_for<T, F>, i1, mid, func);
		parallel_for<T, F>(mid, i2, func);
		t1.join();
	}
}

template <typename T>
void MatVecMainLoop(Matrix<T>* A, Matrix<T>* x, Matrix<T>* y, size_t n,
					size_t i1, size_t i2) {
	if (i1 == i2 - 1)
		for (size_t j = 0; j < n; j++)
			(*y)[i1][0] += (*A)[i1][j] * (*x)[j][0];
	else {
		size_t mid = (i1 + i2) / 2;
		std::thread t1(MatVecMainLoop<T>, A, x, y, n, i1, mid);
		MatVecMainLoop(A, x, y, n, mid, i2);
		t1.join();
	}
}

template <typename T>
void MatVecRecursive(Matrix<T>& A, Matrix<T>& x, Matrix<T>& y) {
	size_t n = A.rows;
	MatVecMainLoop(&A, &x, &y, n, 0, n);
}

template <typename T>
void MatVec(Matrix<T>& A, Matrix<T>& x, Matrix<T>& y) {
	size_t n = A.rows;
	parallel_for<size_t>(0, n, [&](size_t i){
		for (size_t j = 0; j < n; j++)
			y[i][0] += A[i][j] * x[j][0];
	});
}

template <typename T>
void MatVecWrong(Matrix<T>& A, Matrix<T>& x, Matrix<T>& y) {
	size_t n = A.rows;
	parallel_for<size_t>(0, n, [&](size_t i){
		parallel_for<size_t>(0, n, [&](size_t j){
			y[i][0] += A[i][j] * x[j][0];
		});
	});
}

}

#endif
