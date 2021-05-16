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

#include "MatrixInverse.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "LUPSolve.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

bool almost_equal(double lhs, double rhs) {
	return fabs(lhs - rhs) < 1e-7;
}

template <typename T>
bool almost_equal(Fraction<T> lhs, Fraction<T> rhs) {
	return lhs == rhs;
}

template <typename T>
int test(std::size_t n, std::size_t tries) {
	for (std::size_t index = 0; index < tries; index++) {
		try {
			std::vector<int> int_a, int_b;
			random_integers(int_a, -n, n, n * n);
			std::vector<T> buf_a(n * n), buf_b(n);
			for (std::size_t i = 0; i < int_a.size(); i++)
				buf_a[i] = int_a[i];
			Matrix<T> A(n, n, buf_a);
			std::cout << A << std::endl;
			Matrix<T> B = MatrixInverse(A);
			Matrix<T> C = SquareMatrixMultiply(A, B, (T) 0);
			bool test_flag = true;
			for (std::size_t i = 0; i < n; i++)
				for (std::size_t j = 0; j < n; j++) {
					if (i == j)
						test_flag = test_flag && almost_equal(C[i][j], (T) 1);
					else
						test_flag = test_flag && almost_equal(C[i][j], (T) 0);
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
