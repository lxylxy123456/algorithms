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

#include "MatrixChainOrder.hpp"

#include <exception>
#include "utils.h"
#include "SquareMatrixMultiply.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 10);
	const size_t a = get_argv(argc, argv, 2, 6);
	const size_t b = get_argv(argc, argv, 3, 7);
	const size_t c = get_argv(argc, argv, 4, 8);
	if (n) {	// Matrix-Chain Multiplication problem
		VECT_SIZT p;
		std::vector<VECT_SIZT> s(n, VECT_SIZT(n + 1, 0));
		random_integers<size_t>(p, 1, a, n + 1);
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
