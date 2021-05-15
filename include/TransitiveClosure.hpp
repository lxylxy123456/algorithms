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

#ifndef ALGORITHMS_TRANSITIVECLOSURE
#define ALGORITHMS_TRANSITIVECLOSURE

#include "Graph.hpp"

using std::size_t;

namespace algorithms {

template <typename GT>
Matrix<bool> TransitiveClosure(GT& G) {
	const size_t n = G.V.size();
	Matrix<bool> T(n, n, false);
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			if (i == j || G.is_edge(i, j))
				T[i][j] = true;
	for (size_t k = 0; k < n; k++) {
		Matrix<bool> T_new = T;
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++)
				T_new[i][j] = T[i][j] || (T[i][k] && T[k][j]);
		T = T_new;
	}
	return T;
}

}

#endif
