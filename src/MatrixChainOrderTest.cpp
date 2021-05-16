//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#include "MatrixChainOrder.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test_chain(int n, int a) {
	VECT_SIZT p;
	std::vector<VECT_SIZT> s(n, VECT_SIZT(n + 1, 0));
	random_integers<size_t>(p, 1, a, n + 1);
	output_integers(p);
	size_t mco = MatrixChainOrder(p, s);
	size_t mmc = MemorizedMatrixChain(p);
	assert(mco == mmc);
	if (n <= 16) {
		size_t rmc = RecursiveMatrixChain(p);
		assert(mco == rmc);
	}
	PrintOptimalParens(s, 0, n);
	std::cout << std::endl;
	return 0;
}

int test_multiply(int n) {
	int a = n, b = n, c = n;
	std::vector<int> buf_a, buf_b;
	random_integers(buf_a, 0, b, a * b);
	random_integers(buf_b, 0, b, b * c);
	Matrix<int> A(a, b, buf_a);
	Matrix<int> B(b, c, buf_b);
	std::cout << A << std::endl;
	std::cout << B << std::endl;
	assert(MatrixMultiply(A, B) == SquareMatrixMultiply(A, B, 0));
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<int> ns = {1, 4, 16, 19, 20, 47, 100};
	std::vector<int> as = {1, 2, 4, 7, 9};
	for (std::vector<int>::iterator n = ns.begin(); n != ns.end(); n++)
		for (std::vector<int>::iterator a = as.begin(); a != as.end(); a++)
			test_chain(*n, *a);
	for (std::vector<int>::iterator n = ns.begin(); n != ns.end(); n++)
		test_multiply(*n);
	return 0;
}
