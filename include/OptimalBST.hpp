//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#ifndef ALGORITHMS_OPTIMALBST
#define ALGORITHMS_OPTIMALBST

#define SIZT_1D std::vector<std::size_t>
#define SIZT_2D std::vector<std::vector<std::size_t>>

#include <vector>

namespace algorithms {

SIZT_2D OptimalBST(SIZT_1D& p, SIZT_1D& q, std::size_t n) {
	SIZT_2D e(n + 1, SIZT_1D(n + 1, 0));
	SIZT_2D w(n + 1, SIZT_1D(n + 1, 0));
	SIZT_2D root(n, SIZT_1D(n + 1, 0));
	for (std::size_t i = 0; i < n; i++)
		w[i][i] = e[i][i] = q[i];
	for (std::size_t l = 1; l <= n; l++)
		for (std::size_t i = 0; i <= n - l; i++) {
			std::size_t j = i + l;
			e[i][j] = -1;
			w[i][j] = w[i][j - 1] + p[j - 1] + q[j];
			for (std::size_t r = i; r < j; r++) {
				std::size_t t = e[i][r] + e[r + 1][j] + w[i][j];
				if (t < e[i][j]) {
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	return root;
}

}

#endif
