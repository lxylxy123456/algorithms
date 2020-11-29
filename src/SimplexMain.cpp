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

#include "Simplex.hpp"

#include "utils.hpp"
#include "LUPSolve.hpp"
#include <iostream>
#include <vector>

using namespace algorithms;

template <typename T>
void main_T(const size_t n, const size_t m) {
	std::vector<int> int_a, int_b, int_c;
	random_integers(int_a, -m, m, m * n);
	random_integers(int_b, -m, m, m);
	random_integers(int_c, -m, m, n);
	matst A;
	vectst b, c;
	for (size_t i = 1; i <= n; i++)
		c[i] = int_c[i - 1];
	for (size_t i = 1; i <= m; i++)
		b[n + i] = int_b[i - 1];
	for (size_t i = 1; i <= m; i++)
		for (size_t j = 1; j <= n; j++)
			A[n + i][j] = int_a[(i - 1) * n + (j - 1)];
	for (size_t i = 1; i <= m; i++) {
		for (size_t j = 1; j <= n; j++)
			std::cout << A[n + i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (size_t i = 1; i <= m; i++)
		std::cout << b[n + i] << " ";
	std::cout << std::endl;
	for (size_t i = 1; i <= n; i++)
		std::cout << c[i] << " ";
	std::cout << std::endl;
	vectst x = Simplex(A, b, c, (T) 0);
	for (size_t i = 1; i <= n; i++)
		std::cout << x[i] << " ";
	std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	const size_t type = get_argv(argc, argv, 1, 0);
	const size_t m = get_argv(argc, argv, 2, 4);
	const size_t n = get_argv(argc, argv, 3, 2);
	if (!type)
		main_T<double>(n, m);
	else
		main_T<Fraction<int>>(n, m);
	return 0;
}
