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
#define MAIN_LUPSolve
#endif

#ifndef FUNC_LUPSolve
#define FUNC_LUPSolve

#include "utils.h"

#include "SquareMatrixMultiply.cpp"

using PT = std::vector<size_t>; 

template <typename T>
Matrix<T> LUPSolve(Matrix<T>& L, Matrix<T>& U, PT& pi, Matrix<T>& b) {
	size_t n = L.rows; 
	Matrix<T> x(n, 1, 0), y(n, 1, 0); 
	for (size_t i = 0; i < n; i++) {
		T& yy = y[i][0]; 
		yy = b[pi[i]][0]; 
		for (size_t j = 0; j < i; j++)
			yy -= L[i][j] * y[j][0]; 
	}
	for (size_t i = n; i-- > 0; ) {
		T& xx = x[i][0]; 
		xx = y[i][0]; 
		for (size_t j = i + 1; j < n; j++)
			xx -= U[i][j] * x[j][0]; 
		xx /= U[i][i]; 
	}
	return x; 
}

template <typename T>
void LUDecomposition(Matrix<T>& A, Matrix<T>& L, Matrix<T>& U) {
	const size_t n = A.rows; 
	U = L = Matrix<T>(n, n, 0); 
	for (size_t i = 0; i < n; i++)
		L[i][i] = 1; 
	for (size_t k = 0; k < n; k++) {
		U[k][k] = A[k][k]; 
		for (size_t i = k + 1; i < n; i++) {
			L[i][k] = A[i][k] / U[k][k]; 
			U[k][i] = A[k][i]; 
		}
		for (size_t i = k + 1; i < n; i++)
			for (size_t j = k + 1; j < n; j++)
				A[i][j] -= L[i][k] * U[k][j]; 
	}
}

template <typename T>
PT LUPDecomposition(Matrix<T>& A) {
	const size_t n = A.rows; 
	PT pi(n); 
	for (size_t i = 0; i < n; i++)
		pi[i] = i; 
	for (size_t k = 0; k < n; k++) {
		T p = 0; 
		size_t kk; 
		for (size_t i = k; i < n; i++) {
			T abs = A[i][k] < 0 ? -A[i][k] : A[i][k]; 
			if (abs > p) {
				p = abs; 
				kk = i; 
			}
		}
		if (p == 0)
			throw std::invalid_argument("singular matrix"); 
		std::swap(pi[k], pi[kk]); 
		for (size_t i = 0; i < n; i++)
			std::swap(A[k][i], A[kk][i]); 
		for (size_t i = k + 1; i < n; i++) {
			A[i][k] /= A[k][k]; 
			for (size_t j = k + 1; j < n; j++)
				A[i][j] -= A[i][k] * A[k][j]; 
		}
	}
	return pi; 
}
#endif

#ifdef MAIN_LUPSolve
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 16); 
	const size_t compute = get_argv(argc, argv, 2, 3); 
	std::vector<int> int_a, int_b; 
	random_integers(int_a, -n, n, n * n); 
	random_integers(int_b, -n, n, n); 
	using T = double; 
	std::vector<T> buf_a(n * n), buf_b(n); 
	for (size_t i = 0; i < int_a.size(); i++)
		buf_a[i] = int_a[i]; 
	for (size_t i = 0; i < int_b.size(); i++)
		buf_b[i] = int_b[i]; 
	Matrix<T> A(n, n, buf_a); 
	Matrix<T> b(n, 1, buf_b); 
	std::cout << A << std::endl; 
	Matrix<T> ans1(b), ans2(n, 0); 
	if (compute >> 0 & 1) {
		Matrix<T> A1(A), L(0, 0), U(0, 0); 
		PT pi(n); 
		for (size_t i = 0; i < n; i++)
			pi[i] = i; 
		LUDecomposition(A1, L, U); 
		Matrix<T> x = LUPSolve(L, U, pi, b); 
		ans2 = ans2.concat_h(x); 
		Matrix<T> bb = SquareMatrixMultiply(A, x, (T) 0); 
		ans1 = ans1.concat_h(bb); 
	}
	if (compute >> 1 & 1) {
		Matrix<T> A2(A); 
		PT pi = LUPDecomposition(A2); 
		Matrix<T> x = LUPSolve(A2, A2, pi, b); 
		ans2 = ans2.concat_h(x); 
		Matrix<T> bb = SquareMatrixMultiply(A, x, (T) 0); 
		ans1 = ans1.concat_h(bb); 
	}
	for (size_t i = 0; i < n; i++) {
		output_integers(ans1[i], "\t"); 
	}
	std::cout << std::endl; 
	for (size_t i = 0; i < n; i++) {
		std::cout << "\t"; 
		output_integers(ans2[i], "\t"); 
	}
	std::cout << std::endl; 
	return 0; 
}
#endif

