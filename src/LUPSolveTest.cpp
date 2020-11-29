//
//  algorithm - some algorithms in "Introduction to Algorithms", third edition
//  Copyright (C) 2020  lxylxy123456
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
#include "utils.hpp"

#include "SquareMatrixMultiply.hpp"
#include "MatrixChainOrder.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace algorithms;

bool almost_equal(double lhs, double rhs) {
	return fabs(lhs - rhs) < 1e-7;
}

template <typename T>
bool almost_equal(Fraction<T> lhs, Fraction<T> rhs) {
	return lhs == rhs;
}

template <typename T>
int test(size_t n, size_t tries) {
	for (size_t index = 0; index < tries; index++) {
		try {
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
			std::cout << A << std::endl << b << std::endl;
			Matrix<T> ans1(b), ans2(n, 0, 0);
			{
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
			{
				Matrix<T> A2(A);
				PT pi = LUPDecomposition(A2);
				Matrix<T> x = LUPSolve(A2, A2, pi, b);
				ans2 = ans2.concat_h(x);
				Matrix<T> bb = SquareMatrixMultiply(A, x, (T) 0);
				ans1 = ans1.concat_h(bb);
			}
			ans1 = ans1.concat_h(MatrixMultiply(A, ans2));
			bool test_flag = true;
			for (size_t i = 0; i < n; i++) {
				test_flag = test_flag && almost_equal(ans1[i][0], ans1[i][1]);
				test_flag = test_flag && almost_equal(ans1[i][0], ans1[i][2]);
				test_flag = test_flag && almost_equal(ans1[i][0], ans1[i][3]);
				test_flag = test_flag && almost_equal(ans1[i][0], ans1[i][4]);
			}
			if (!test_flag)
				continue;
			return 0;
		} catch (std::invalid_argument& e) {
			assert(std::string(e.what()) == "singular matrix" ||
					std::string(e.what()) == "zero denominator");
			continue;
		}
	}
	assert(0 && "test failed");
}

int main(int argc, char *argv[]) {
	test<double>(2, 50);
	test<double>(5, 50);
	test<double>(8, 50);
	test<double>(19, 50);
	test<double>(52, 50);
	test<double>(100, 50);
	test<Fraction<long long int>>(2, 50);
	test<Fraction<long long int>>(5, 50);
	test<Fraction<long long int>>(6, 100);
	return 0;
}
