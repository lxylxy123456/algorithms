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

#include "IterativeFFT.hpp"
#include "utils.hpp"

#include "RecursiveFFT.hpp"
#include <cassert>

using namespace algorithms;

bool almost_equal(Complex<double> lhs, Complex<double> rhs) {
	return fabs(lhs.real - rhs.real) + fabs(lhs.imag - rhs.imag) < 1e-5;
}

int test(size_t n) {
	std::vector<int> int_a, int_b;
	random_integers(int_a, -n, n, n);
	random_integers(int_b, -n, n, n);
	using T = Complex<double>;
	std::vector<T> buf_a(n), buf_b(n);
	for (size_t i = 0; i < n; i++)
		buf_a[i] = int_a[i];
	for (size_t i = 0; i < n; i++)
		buf_b[i] = int_b[i];
	output_integers(int_a);
	output_integers(int_b);
	Matrix<T> a(n, 1, buf_a);
	Matrix<T> b(n, 1, buf_b);
	Matrix<T> c = PolynomialMultiply(a, b);
	Matrix<T> d = IterativePolynomialMultiply(a, b);
	Matrix<int> e(2 * n, 1, 0);
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			e[i + j][0] += int_a[i] * int_b[j];
	for (size_t i = 0; i < 2 * n; i++) {
		assert(almost_equal(d[i][0], c[i][0]));
		assert(almost_equal(d[i][0], e[i][0]));
	}
	std::cout << std::endl;
	return 0;
}

int main(int argc, char *argv[]) {
	for (size_t n = 2; n <= 1024; n *= 2)
		test(n);
	return 0;
}
