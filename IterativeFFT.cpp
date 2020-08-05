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

#ifndef MAIN
#define MAIN
#define MAIN_IterativeFFT
#endif

#ifndef FUNC_IterativeFFT
#define FUNC_IterativeFFT

#include "utils.h"

#include "RecursiveFFT.cpp"

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
#endif

#ifdef MAIN_IterativeFFT
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
#endif

