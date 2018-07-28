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
#define MAIN_LeastSquareApprox
#endif

#ifndef FUNC_LeastSquareApprox
#define FUNC_LeastSquareApprox

#include "utils.h"

#include "LUPSolve.cpp"

template <typename T>
Matrix<T> LeastSquareApprox(Matrix<T>& A, Matrix<T>& y) {
	Matrix<T> AT = A.transpose(); 
	Matrix<T> b = SquareMatrixMultiply(AT, y, (T) 0); 
	Matrix<T> ATA = SquareMatrixMultiply(AT, A, (T) 0); 
	PT pi = LUPDecomposition(ATA); 
	Matrix<T> c = LUPSolve(ATA, ATA, pi, b); 
	return c; 
}
#endif

#ifdef MAIN_LeastSquareApprox
template <typename T>
void main_T(const size_t n, const size_t m) {
	std::vector<int> int_a, int_b; 
	random_integers(int_a, 0, m, m * n); 
	random_integers(int_b, 0, m, m); 
	std::vector<T> buf_a(m * n), buf_b(m); 
	for (size_t i = 0; i < int_a.size(); i++)
		buf_a[i] = int_a[i]; 
	for (size_t i = 0; i < int_b.size(); i++)
		buf_b[i] = int_b[i]; 
	Matrix<T> A(m, n, buf_a); 
	Matrix<T> b(m, 1, buf_b); 
	std::cout << A << std::endl; 
	Matrix<T> ans1(b), ans2(n, 0); 
	Matrix<T> x = LeastSquareApprox(A, b); 
	ans2 = ans2.concat_h(x); 
	Matrix<T> bb = SquareMatrixMultiply(A, x, (T) 0); 
	ans1 = ans1.concat_h(bb); 
	for (size_t i = 0; i < m; i++) {
		output_integers(ans1[i], "\t"); 
	}
	std::cout << std::endl; 
	for (size_t i = 0; i < n; i++) {
		std::cout << "\t"; 
		output_integers(ans2[i], "\t"); 
	}
	std::cout << std::endl; 
}

int main(int argc, char *argv[]) {
	const size_t type = get_argv(argc, argv, 1, 0); 
	const size_t m = get_argv(argc, argv, 2, 10); 
	const size_t n = get_argv(argc, argv, 3, 5); 
	if (!type)
		main_T<double>(n, m); 
	else
		main_T<Fraction<int>>(n, m); 
	return 0; 
}
#endif

