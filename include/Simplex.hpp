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

#ifndef ALGORITHMS_SIMPLEX
#define ALGORITHMS_SIMPLEX

#include <cassert>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

#include "LUPSolve.hpp"
#include "ProtovEB.hpp"

using std::size_t;

namespace algorithms {

#define usetst typename std::unordered_set<std::size_t>
#define vectst typename std::unordered_map<std::size_t, T>
#define matst typename \
	std::unordered_map<std::size_t, std::unordered_map<std::size_t, T>>

template <typename T>
void Pivot(usetst& N, usetst& B, matst& A, vectst& b, vectst& c, T& v,
			std::size_t l, std::size_t e) {
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
						T& v, const T epsilon) {
	const std::size_t n = c.size(), m = b.size();
	for (std::size_t i = 1; i <= n; i++)
		N.insert(i);
	for (std::size_t i = n + 1; i <= n + m; i++)
		B.insert(i);
	v = 0;
	std::size_t k = n + 1;
	for (auto i = B.begin(); i != B.end(); i++)
		if (b[*i] < b[k])
			k = *i;
	if (!(b[k] < epsilon))
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
		std::size_t e = NIL, l = NIL;
		for (auto i = N.begin(); i != N.end(); i++)
			if (epsilon < Lc[*i]) {
				e = *i;
				break;
			}
		if (e == NIL)
			break;
		T delta;
		for (auto i = B.begin(); i != B.end(); i++)
			if (epsilon < A[*i][e]) {
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
			std::size_t e = NIL;
			for (auto i = N.begin(); i != N.end(); i++)
				if (!(-epsilon < A[0][*i] && A[0][*i] < epsilon)) {
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
vectst Simplex(matst A, vectst b, vectst c, const T epsilon) {
	// Numbers in [-epsilon, epsilon] are treated as 0
	usetst N, B;
	T v;
	InitializeSimplex(N, B, A, b, c, v, epsilon);
	while (true) {
		std::size_t e = NIL, l = NIL;
		for (auto i = N.begin(); i != N.end(); i++)
			if (epsilon < c[*i]) {
				e = *i;
				break;
			}
		if (e == NIL)
			break;
		T delta;
		for (auto i = B.begin(); i != B.end(); i++)
			if (epsilon < A[*i][e]) {
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
	for (std::size_t i = 1; i <= c.size(); i++) {
		if (B.find(i) != B.end())
			x[i] = b[i];
		else
			x[i] = 0;
	}
	return x;
}

}

#endif
