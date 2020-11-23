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

#include <cassert>
#include "utils.hpp"
#include "LUPSolve.hpp"

using namespace algorithms;

template <typename T>
void main_T(const size_t n, const size_t m) {
	std::vector<int> int_a = {-3, 3, 2, -3}, int_b = {-3, -3}, int_c = {-1, 1};
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
	vectst x = Simplex(A, b, c, (T) 0.0000001);
	for (size_t i = 1; i <= n; i++)
		std::cout << x[i] << " ";
	std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	const size_t type = 0;
	const size_t m = 2;
	const size_t n = 2;
	if (!type)
		main_T<double>(n, m);
	else
		main_T<Fraction<int>>(n, m);
	return 0;
}
