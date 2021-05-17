//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#ifndef ALGORITHMS_MATRIXCHAINORDER
#define ALGORITHMS_MATRIXCHAINORDER

#define VECT_SIZT std::vector<std::size_t>

#include <iostream>
#include <stdexcept>
#include <vector>

#include "SquareMatrixMultiply.hpp"

namespace algorithms {

template <typename T>
Matrix<T> MatrixMultiply(Matrix<T>&A, Matrix<T>&B) {
	if (A.cols != B.rows)
		throw std::invalid_argument("incompatible dimensions");
	Matrix<T> C(A.rows, B.cols, A[0][0]);
	for (std::size_t i = 0; i < C.rows; i++) {
		for(std::size_t j = 0; j < C.cols; j++) {
			T& loc = C.data[i][j];
			loc = A[i][0] * B[0][j];
			for(std::size_t k = 1; k < A.cols; k++)
				loc += A[i][k] * B[k][j];
		}
	}
	return C;
}

std::size_t MatrixChainOrder(VECT_SIZT& p, std::vector<VECT_SIZT>& s) {
	std::size_t n = p.size() - 1;
	std::vector<VECT_SIZT> m(n, VECT_SIZT(n + 1, 0));
	for (std::size_t l = 2; l <= n; l++) {
		for (std::size_t i = 0; i <= n - l; i++) {
			std::size_t j = l + i;
			m[i][j] = -1;
			for (std::size_t k = i + 1; k < j; k++) {
				std::size_t q = m[i][k] + m[k][j] + p[i] * p[k] * p[j];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	return m[0][n];
}

void PrintOptimalParens(std::vector<VECT_SIZT>& s, std::size_t i,
						std::size_t j) {
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

std::size_t RecursiveMatrixChain(VECT_SIZT& p, std::size_t i, std::size_t j) {
	if (i == j - 1)
		return 0;
	std::size_t m = -1;
	for (std::size_t k = i + 1; k < j; k++) {
		std::size_t q = RecursiveMatrixChain(p, i, k)
				 + RecursiveMatrixChain(p, k, j)
				 + p[i] * p[k] * p[j];
		if (q < m)
			m = q;
	}
	return m;
}

std::size_t RecursiveMatrixChain(VECT_SIZT& p) {
	return RecursiveMatrixChain(p, 0, p.size() - 1);
}

std::size_t LookupChain(std::vector<VECT_SIZT>& m, VECT_SIZT& p, std::size_t i,
						std::size_t j){
	if (m[i][j] != (std::size_t)-1)
		return m[i][j];
	if (i + 1 == j)
		m[i][j] = 0;
	else {
		for (std::size_t k = i + 1; k < j; k++) {
			std::size_t q = LookupChain(m, p, i, k) + LookupChain(m, p, k, j)
					 + p[i] * p[k] * p[j];
			if (q < m[i][j])
				m[i][j] = q;
		}
	}
	return m[i][j];
}

std::size_t MemorizedMatrixChain(VECT_SIZT& p) {
	std::size_t n = p.size() - 1;
	std::vector<VECT_SIZT> m(n, VECT_SIZT(n + 1, -1));
	return LookupChain(m, p, 0, n);
}

}

#endif
