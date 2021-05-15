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

#ifndef ALGORITHMS_ITERATIVEFFT
#define ALGORITHMS_ITERATIVEFFT

#include <cassert>

#include "RecursiveFFT.hpp"

using std::size_t;

namespace algorithms {

size_t rev(size_t k, size_t n) {
	size_t ans = 0;
	for (size_t i = 1; i != n; i <<= 1) {
		ans <<= 1;
		if (k & i)
			ans |= 1;
	}
	return ans;
}

template <typename T>
Matrix<T> BitReverseCopy(Matrix<T>& a) {
	const size_t n = a.rows;
	Matrix<T> A(n, 1, 0);
	for (size_t k = 0; k < n; k++)
		A[rev(k, n)] = a[k];
	return A;
}

template <typename T>
Matrix<T> IterativeFFT(Matrix<T>& a, bool neg = false) {
	const size_t n = a.rows;
	Matrix<T> A = BitReverseCopy(a);
	for (size_t s = 1; size_t (1 << s) <= n; s++) {
		size_t m = 1 << s;
		T wm = expi((neg ? -1 : 1) * 2 * M_PI / m);
		for (size_t k = 0; k < n; k += m) {
			T w = 1;
			for (size_t j = 0; j < m / 2; j++) {
				T t = w * A[k + j + m / 2][0];
				T u = A[k + j][0];
				A[k + j][0] = u + t;
				A[k + j + m / 2][0] = u - t;
				w *= wm;
			}
		}
	}
	return A;
}

template <typename T>
Matrix<T> IterativeInverseFFT(Matrix<T>& a) {
	const size_t n = a.rows;
	Matrix<T> ans = IterativeFFT(a, true);
	for (size_t i = 0; i < n; i++)
		ans[i][0] /= n;
	return ans;
}

template <typename T>
Matrix<T> IterativePolynomialMultiply(Matrix<T>& a, Matrix<T>& b) {
	const size_t n = a.rows;
	assert(n == b.rows);
	Matrix<T> n0(n, 1, 0);
	Matrix<T> aa = a.concat_v(n0);
	Matrix<T> bb = b.concat_v(n0);
	Matrix<T> fa = IterativeFFT(aa);
	Matrix<T> fb = IterativeFFT(bb);
	Matrix<T> fc(2 * n, 1, 0);
	for (size_t i = 0; i < 2 * n; i++)
		fc[i][0] = fa[i][0] * fb[i][0];
	return IterativeInverseFFT(fc);
}

}

#endif
