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

#include "Simplex.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "LUPSolve.hpp"
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
int test(size_t m, size_t n, T epsilon) {
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
	try {
		vectst x = Simplex(A, b, c, epsilon);
		for (size_t i = 1; i <= n; i++)
			std::cout << x[i] << " ";
		std::cout << std::endl;
		for (size_t i = 1; i <= m; i++) {
			T s(0);
			for (size_t j = 1; j <= n; j++)
				s += A[n + i][j] * x[j];
			assert(s - b[n + i] < (T) 1 / (T) 100000);
		}
	} catch (std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
		assert(std::string(e.what()) == "infeasible" ||
				std::string(e.what()) == "unbounded");
	}
	std::cout << std::endl;
	return 0;
}

int main(int argc, char *argv[]) {
	std::cout << random_seed_get() << std::endl;
	std::vector<size_t> ns = {2, 5, 8, 19, 39, 52, 73};
	for (std::vector<size_t>::iterator m = ns.begin(); m < ns.end(); m++)
		for (std::vector<size_t>::iterator n = ns.begin(); n < ns.end(); n++)
			if (*m > *n)
				test<double>(*m, *n, 1e-5);
	test<Fraction<long long int>>(3, 2, (Fraction<long long int>) 0);
	test<Fraction<long long int>>(4, 2, (Fraction<long long int>) 0);
	test<Fraction<long long int>>(4, 3, (Fraction<long long int>) 0);
	return 0;
}
