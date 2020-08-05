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

#ifndef ALGORITHMS_FLOYDWARSHALL
#define ALGORITHMS_FLOYDWARSHALL

#include "utils.h"

#include "Graph.hpp"

namespace algorithms {

void PrintAllPairsShortestPath(Matrix<T_ptr<size_t>>& PI, size_t i, size_t j,
	std::vector<size_t>& ans) {
	if (i == j)
		ans.push_back(i);
	else if (!PI[i][j].nil) {
		PrintAllPairsShortestPath(PI, i, PI[i][j].val, ans);
		ans.push_back(j);
	}
}

template <typename T>
std::pair<Matrix<T>, Matrix<T_ptr<size_t>>> FloydWarshall(Matrix<T>& W) {
	const size_t n = W.rows;
	Matrix<T> D = W;
	Matrix<T_ptr<size_t>> PI(n, n, T_ptr<size_t>());
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			if (i != j && !W[i][j].inf)
				PI[i][j] = i;
	for (size_t k = 0; k < n; k++) {
		Matrix<T> D_new = D;
		Matrix<T_ptr<size_t>> PI_new = PI;
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++) {
				T n = D[i][k] + D[k][j];
				if (n < D_new[i][j]) {
					D_new[i][j] = n;
					PI_new[i][j] = PI[k][j];
				}
			}
		D = D_new;
		PI = PI_new;
	}
	return std::pair<Matrix<T>, Matrix<T_ptr<size_t>>>(D, PI);
}

}

#endif