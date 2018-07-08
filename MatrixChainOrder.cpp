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
#define MAIN_MatrixChainOrder
#endif

#ifndef FUNC_MatrixChainOrder
#define FUNC_MatrixChainOrder

#define VECT_SIZT std::vector<size_t>

#include <algorithm>
#include <exception>
#include <cassert>
#include "utils.h"
#include "SquareMatrixMultiply.cpp"

template <typename T>
Matrix<T> MatrixMultiply(Matrix<T>&A, Matrix<T>&B) {
	if (A.cols != B.rows)
		throw std::invalid_argument("incompatible dimensions"); 
	Matrix<T> C(A.rows, B.cols, A[0][0]); 
	for (size_t i = 0; i < C.rows; i++) {
		for(size_t j = 0; j < C.cols; j++) {
			int& loc = C.data[i][j]; 
			loc = A[i][0] * B[0][j]; 
			for(size_t k = 1; k < A.cols; k++)
				loc += A[i][k] * B[k][j]; 
		}
	}
	return C; 
}

size_t MatrixChainOrder(VECT_SIZT& p, std::vector<VECT_SIZT>& s) {
	size_t n = p.size() - 1; 
	std::vector<VECT_SIZT> m(n, VECT_SIZT(n + 1, 0)); 
	for (size_t l = 2; l <= n; l++) {
		for (size_t i = 0; i <= n - l; i++) {
			size_t j = l + i; 
			m[i][j] = -1; 
			for (size_t k = i + 1; k < j; k++) {
				size_t q = m[i][k] + m[k][j] + p[i] * p[k] * p[j]; 
				if (q < m[i][j]) {
					m[i][j] = q; 
					s[i][j] = k; 
				}
			}
		}
	}
	return m[0][n]; 
}

void PrintOptimalParens(std::vector<VECT_SIZT>& s, size_t i, size_t j) {
	if (i == j - 1)
		std::cout << "A" << i; 
	else {
		std::cout << "("; 
		PrintOptimalParens(s, i, s[i][j]); 
		std::cout << " "; 
		PrintOptimalParens(s, s[i][j], j); 
		std::cout << ")"; 
	}
}

size_t RecursiveMatrixChain(VECT_SIZT& p, size_t i, size_t j) {
	if (i == j - 1)
		return 0; 
	size_t m = -1; 
	for (size_t k = i + 1; k < j; k++) {
		size_t q = RecursiveMatrixChain(p, i, k)
				 + RecursiveMatrixChain(p, k, j)
				 + p[i] * p[k] * p[j]; 
		if (q < m)
			m = q; 
	}
	return m; 
}

size_t RecursiveMatrixChain(VECT_SIZT& p) {
	return RecursiveMatrixChain(p, 0, p.size() - 1); 
}

size_t LookupChain(std::vector<VECT_SIZT>& m, VECT_SIZT& p, size_t i, size_t j){
	if (m[i][j] != (size_t)-1)
		return m[i][j]; 
	if (i + 1 == j) 
		m[i][j] = 0; 
	else {
		for (size_t k = i + 1; k < j; k++) {
			size_t q = LookupChain(m, p, i, k) + LookupChain(m, p, k, j)
					 + p[i] * p[k] * p[j]; 
			if (q < m[i][j])
				m[i][j] = q; 
		}
	}
	return m[i][j]; 
}

size_t MemorizedMatrixChain(VECT_SIZT& p) {
	size_t n = p.size() - 1; 
	std::vector<VECT_SIZT> m(n, VECT_SIZT(n + 1, -1)); 
	return LookupChain(m, p, 0, n); 
}
#endif

#ifdef MAIN_MatrixChainOrder
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 10); 
	const size_t a = get_argv(argc, argv, 2, 6); 
	const size_t b = get_argv(argc, argv, 3, 7); 
	const size_t c = get_argv(argc, argv, 4, 8); 
	if (n) {	// Matrix-Chain Multiplication problem
		VECT_SIZT p; 
		std::vector<VECT_SIZT> s(n, VECT_SIZT(n + 1, 0)); 
		random_integers(p, 1, a, n + 1); 
		output_integers(p); 
		if (b >> 0 & 1) {
			std::cout << MatrixChainOrder(p, s) << std::endl; 
			PrintOptimalParens(s, 0, n); 
			std::cout << std::endl; 
		}
		if (b >> 1 & 1) {
			std::cout << RecursiveMatrixChain(p) << std::endl; 
		}
		if (b >> 2 & 1) {
			std::cout << MemorizedMatrixChain(p) << std::endl; 
		}
	} else {	// test MatrixMultiply
		std::vector<int> buf_a, buf_b; 
		random_integers(buf_a, 0, b, a * b); 
		random_integers(buf_b, 0, b, b * c); 
		Matrix<int> A(a, b, buf_a); 
		Matrix<int> B(b, c, buf_b); 
		std::cout << A << std::endl; 
		std::cout << B << std::endl; 
		std::cout << MatrixMultiply(A, B) << std::endl; 
	}
	return 0; 
}
#endif

