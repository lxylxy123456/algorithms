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
#define MAIN_Simplex
#endif

#ifndef FUNC_Simplex
#define FUNC_Simplex

#include <cassert>
#include <exception>
#include <unordered_set>
#include <unordered_map>
#include "utils.h"

#include "LUPSolve.cpp"

#define usetst typename std::unordered_set<size_t>
#define vectst typename std::unordered_map<size_t, T>
#define matst typename std::unordered_map<size_t, std::unordered_map<size_t, T>>

const size_t NIL = -1;

template <typename T>
void Pivot(usetst& N, usetst& B, matst& A, vectst& b, vectst& c, T& v,
			size_t l, size_t e) {
	matst A_hat;
	vectst b_hat, c_hat;
	b_hat[e] = b[l] / A[l][e];
	N.erase(e);
	B.erase(l);
	for (auto j = N.begin(); j != N.end(); j++)
		A_hat[e][*j] = A[l][*j] / A[l][e];
	A_hat[e][l] = (T) 1 / A[l][e];
	for (auto i = B.begin(); i != B.end(); i++) {
		b_hat[*i] = b[*i] - A[*i][e] * b_hat[e];
		for (auto j = N.begin(); j != N.end(); j++)
			A_hat[*i][*j] = A[*i][*j] - A[*i][e] * A_hat[e][*j];
		A_hat[*i][l] = - A[*i][e] * A_hat[e][l];
	}
	v += c[e] * b_hat[e];
	for (auto j = N.begin(); j != N.end(); j++)
		c_hat[*j] = c[*j] - c[e] * A_hat[e][*j];
	c_hat[l] = - c[e] * A_hat[e][l];
	N.insert(l);
	B.insert(e);
	A = A_hat;
	b = b_hat;
	c = c_hat;
}

template <typename T>
void InitializeSimplex(usetst& N, usetst& B, matst& A, vectst& b, vectst& c,
						T& v) {
	const size_t n = c.size(), m = b.size();
	for (size_t i = 1; i <= n; i++)
		N.insert(i);
	for (size_t i = n + 1; i <= n + m; i++)
		B.insert(i);
	v = 0;
	size_t k = n + 1;
	for (auto i = B.begin(); i != B.end(); i++)
		if (b[*i] < b[k])
			k = *i;
	if (!(b[k] < (T) 0))
		return;
	vectst Lc;
	T Lv = 0;
	for (auto i = B.begin(); i != B.end(); i++)
		A[*i][0] = -1;
	Lc[0] = -1;
	for (auto j = N.begin(); j != N.end(); j++)
		Lc[*j] = 0;
	N.insert(0);
	Pivot(N, B, A, b, Lc, Lv, k, 0);
	while (true) {
		size_t e = NIL, l = NIL;
		for (auto i = N.begin(); i != N.end(); i++)
			if ((T) 0 < Lc[*i]) {
				e = *i;
				break;
			}
		if (e == NIL)
			break;
		T delta;
		for (auto i = B.begin(); i != B.end(); i++)
			if ((T) 0 < A[*i][e]) {
				T cur = b[*i] / A[*i][e];
				if (l == NIL || cur < delta) {
					l = *i;
					delta = cur;
				}
			}
		assert(l != NIL);
		Pivot(N, B, A, b, Lc, Lv, l, e);
	}
	if (Lv == 0) {
		if (B.find(0) != B.end()) {
			size_t e = NIL;
			for (auto i = N.begin(); i != N.end(); i++)
				if (!(A[0][*i] == 0)) {
					e = *i;
					break;
				}
			assert(e != NIL);
			Pivot(N, B, A, b, Lc, Lv, 0, e);
		}
		N.erase(0);
		for (auto i = B.begin(); i != B.end(); i++)
			A[*i].erase(0);
		for (auto j = N.begin(); j != N.end(); j++)
			if (c.find(*j) == c.end())
				c[*j] = 0;
		for (auto i = B.begin(); i != B.end(); i++) {
			if (c.find(*i) != c.end()) {
				v += b[*i] * c[*i];
				for (auto j = N.begin(); j != N.end(); j++)
					c[*j] -= A[*i][*j] * c[*i];
				c.erase(*i);
			}
		}
	} else
		throw std::invalid_argument("infeasible");
}

template <typename T>
vectst Simplex(matst A, vectst b, vectst c) {
	usetst N, B;
	T v;
	InitializeSimplex(N, B, A, b, c, v);
	while (true) {
		size_t e = NIL, l = NIL;
		for (auto i = N.begin(); i != N.end(); i++)
			if ((T) 0 < c[*i]) {
				e = *i;
				break;
			}
		if (e == NIL)
			break;
		T delta;
		for (auto i = B.begin(); i != B.end(); i++)
			if ((T) 0 < A[*i][e]) {
				T cur = b[*i] / A[*i][e];
				if (l == NIL || cur < delta) {
					l = *i;
					delta = cur;
				}
			}
		if (l == NIL)
			throw std::invalid_argument("unbounded");
		Pivot(N, B, A, b, c, v, l, e);
	}
	vectst x;
	for (size_t i = 1; i <= c.size(); i++) {
		if (B.find(i) != B.end())
			x[i] = b[i];
		else
			x[i] = 0;
	}
	return x;
}
#endif

#ifdef MAIN_Simplex
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
	vectst x = Simplex(A, b, c);
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
#endif

