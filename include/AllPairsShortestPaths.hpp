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

#ifndef ALGORITHMS_ALLPAIRSSHORTESTPATHS
#define ALGORITHMS_ALLPAIRSSHORTESTPATHS

#include "Graph.hpp"

#include <algorithm>

namespace algorithms {

template <typename T>
Matrix<T> ExtendShortestPaths(Matrix<T>& L, Matrix<T>& W) {
	const size_t n = L.rows;
	Matrix<T> ans(n, n, T());
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			for (size_t k = 0; k < n; k++)
				ans[i][j] = std::min(ans[i][j], L[i][k] + W[k][j]);
	return ans;
}

template <typename T>
Matrix<T> SlowAllPairsShortestPaths(Matrix<T>& W) {
	const size_t n = W.rows;
	Matrix<T> L = W;
	for (size_t m = 2; m < n; m++)
		L = ExtendShortestPaths(L, W);
	return L;
}

template <typename T>
Matrix<T> FasterAllPairsShortestPaths(Matrix<T>& W) {
	const size_t n = W.rows;
	Matrix<T> L = W;
	for (size_t m = 1; m < n - 1; m *= 2)
		L = ExtendShortestPaths(L, L);
	return L;
}

}

#endif
