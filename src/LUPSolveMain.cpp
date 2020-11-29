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

#include "LUPSolve.hpp"

#include <iostream>
#include <vector>

#include "SquareMatrixMultiply.hpp"
#include "utils.hpp"

using namespace algorithms;

template <typename T>
void main_T(const size_t n, const size_t compute) {
	std::vector<int> int_a, int_b;
	random_integers(int_a, -n, n, n * n);
	random_integers(int_b, -n, n, n);
	std::vector<T> buf_a(n * n), buf_b(n);
	for (size_t i = 0; i < int_a.size(); i++)
		buf_a[i] = int_a[i];
	for (size_t i = 0; i < int_b.size(); i++)
		buf_b[i] = int_b[i];
	Matrix<T> A(n, n, buf_a);
	Matrix<T> b(n, 1, buf_b);
	std::cout << A << std::endl;
	Matrix<T> ans1(b), ans2(n, 0, 0);
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
}

int main(int argc, char *argv[]) {
	const size_t type = get_argv(argc, argv, 1, 0);
	const size_t n = get_argv(argc, argv, 2, 5);
	const size_t compute = get_argv(argc, argv, 3, 3);
	if (!type)
		main_T<double>(n, compute);
	else
		main_T<Fraction<int>>(n, compute);
	return 0;
}
