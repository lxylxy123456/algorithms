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

#include "LeastSquareApprox.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "LUPSolve.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

template <typename T>
T norm(Matrix<T> lhs, Matrix<T> rhs) {
	T ans = 0;
	assert(lhs.rows == rhs.rows && lhs.cols == 1 && rhs.cols == 1);
	for (std::size_t i = 0; i < lhs.rows; i++) {
		T tmp = lhs[i][0] - rhs[i][0];
		ans += tmp * tmp;
	}
	return ans;
}

template <typename T>
int test(std::size_t m, size_t n, size_t tries) {
	for (std::size_t index = 0; index < tries; index++) {
		try {
			std::vector<int> int_a, int_b;
			random_integers(int_a, 0, m, m * n);
			random_integers(int_b, 0, m, m);
			std::vector<T> buf_a(m * n), buf_b(m);
			for (std::size_t i = 0; i < int_a.size(); i++)
				buf_a[i] = int_a[i];
			for (std::size_t i = 0; i < int_b.size(); i++)
				buf_b[i] = int_b[i];
			Matrix<T> A(m, n, buf_a);
			Matrix<T> b(m, 1, buf_b);
			std::cout << A << std::endl;
			std::cout << b << std::endl;
			Matrix<T> x = LeastSquareApprox(A, b);
			Matrix<T> bb = SquareMatrixMultiply(A, x, (T) 0);
			bool test_flag = true;
			for (std::size_t i = 0; i < n; i++)
				for (T j = -1; j < (T) 11 / (T) 10; j += (T) 1 / (T) 10) {
					Matrix<T> y(x);
					y[i][0] += j;
					Matrix<T> by = SquareMatrixMultiply(A, y, (T) 0);
					T nx = norm(b, bb), ny = norm(b, by);
					test_flag = test_flag && !(ny - nx < (T) -1 / (T) 100000);
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
	parse_args(argc, argv);
	std::vector<std::size_t> ns = {2, 5, 8, 19, 52, 100};
	for (std::vector<std::size_t>::iterator m = ns.begin(); m < ns.end(); m++)
		for (std::vector<std::size_t>::iterator n = ns.begin(); n < ns.end(); n++)
			if (*m > *n)
				test<double>(*m, *n, 1);
	test<Fraction<long long int>>(3, 1, 100);
	test<Fraction<long long int>>(3, 2, 100);
	test<Fraction<long long int>>(4, 2, 100);
	test<Fraction<long long int>>(4, 3, 100);
	return 0;
}
