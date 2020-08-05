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

#include "IterativeFFT.hpp"

#include "utils.h"
#include "RecursiveFFT.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	for (size_t i = 0; i < 8; i++) {
		std::cout << rev(i, 8) << std::endl;
	}
	const size_t n = get_argv(argc, argv, 1, 16);
	std::vector<int> int_a, int_b;
	random_integers(int_a, -n, n, n);
	random_integers(int_b, -n, n, n);
	using T = Complex<double>;
	std::vector<T> buf_a(n), buf_b(n);
	for (size_t i = 0; i < int_a.size(); i++)
		buf_a[i] = int_a[i];
	for (size_t i = 0; i < int_a.size(); i++)
		buf_b[i] = int_b[i];
	Matrix<T> a(n, 1, buf_a);
	std::cout << a << std::endl;
	Matrix<T> b(n, 1, buf_b);
	std::cout << b << std::endl;
	Matrix<T> ans(2 * n, 0);
	ans = ans.concat_h(PolynomialMultiply(a, b));
	ans = ans.concat_h(IterativePolynomialMultiply(a, b));
	std::cout << ans << std::endl;
	return 0;
}
