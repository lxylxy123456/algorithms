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

#ifndef MAIN
#define MAIN
#define MAIN_MatVec
#endif

#ifndef FUNC_MatVec
#define FUNC_MatVec

#include <thread>
#include "utils.h"

#include "SquareMatrixMultiply.cpp"

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
void MatVec(Matrix<T>& A, Matrix<T>& x, Matrix<T>& y) {
	size_t n = A.rows; 
	MatVecMainLoop(&A, &x, &y, n, 0, n); 
}

template <typename T>
void MatVecWrongLoop2(Matrix<T>* A, Matrix<T>* x, Matrix<T>* y, size_t n, 
					size_t i, size_t j1, size_t j2) {
	if (j1 == j2 - 1)
		(*y)[i][0] += (*A)[i][j1] * (*x)[j1][0]; 
	else {
		size_t mid = (j1 + j2) / 2; 
		std::thread t1(MatVecWrongLoop2<T>, A, x, y, n, i, j1, mid); 
		MatVecWrongLoop2(A, x, y, n, i, mid, j2); 
		t1.join(); 
	}
}

template <typename T>
void MatVecWrongLoop1(Matrix<T>* A, Matrix<T>* x, Matrix<T>* y, size_t n, 
					size_t i1, size_t i2) {
	if (i1 == i2 - 1)
		MatVecWrongLoop2(A, x, y, n, i1, 0, n); 
	else {
		size_t mid = (i1 + i2) / 2; 
		std::thread t1(MatVecWrongLoop1<T>, A, x, y, n, i1, mid); 
		MatVecWrongLoop1(A, x, y, n, mid, i2); 
		t1.join(); 
	}
}

template <typename T>
void MatVecWrong(Matrix<T>& A, Matrix<T>& x, Matrix<T>& y) {
	size_t n = A.rows; 
	MatVecWrongLoop1(&A, &x, &y, n, 0, n); 
}
#endif

#ifdef MAIN_MatVec
int main(int argc, char *argv[]) {
	size_t n = get_argv(argc, argv, 1, 10); 
	size_t compute = get_argv(argc, argv, 2, 1); 
	std::vector<int> buf_A, buf_x; 
	random_integers(buf_A, 0, n, n * n); 
	random_integers(buf_x, 0, n, n); 
	Matrix<int> A(n, n, buf_A); 
	Matrix<int> x(n, 1, buf_x); 
	Matrix<int> y(n, 1, 0); 
	MatVec(A, x, y); 
	std::cout << A << std::endl; 
	std::cout << x << std::endl; 
	std::cout << y << std::endl; 
	if (compute) {
		Matrix<int> yw(n, 1, 0); 
		MatVecWrong(A, x, yw); 
		std::cout << yw << std::endl; 
		std::cout << std::boolalpha << (y == yw) << std::endl; 
	}
	return 0; 
}
#endif

