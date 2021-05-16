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

#ifndef ALGORITHMS_LCSLENGTH
#define ALGORITHMS_LCSLENGTH

#define VECT_SIZT std::vector<size_t>

#include <algorithm>
#include <iostream>
#include <vector>

using std::size_t;

namespace algorithms {

template <typename T>
std::vector<VECT_SIZT> LCSLength(std::vector<T> X, std::vector<T> Y) {
	size_t m = X.size(), n = Y.size();
	std::vector<VECT_SIZT> c(m + 1, VECT_SIZT(n + 1, 0));
	for (size_t i = 1; i <= m; i++)
		for (size_t j = 1; j <= n; j++) {
			if (X[i - 1] == Y[j - 1])
				c[i][j] = c[i-1][j-1] + 1;
			else
				c[i][j] = std::max(c[i-1][j], c[i][j-1]);
		}
	return c;
}

template <typename T>
void PrintLCS(std::vector<VECT_SIZT>& c, std::vector<T> X, size_t i, size_t j) {
	if (!i || !j)
		return;
	if (c[i][j] == c[i-1][j])
		PrintLCS(c, X, i - 1, j);
	else if (c[i][j] == c[i][j-1])
		PrintLCS(c, X, i, j - 1);
	else {
		PrintLCS(c, X, i - 1, j - 1);
		std::cout << X[i - 1];
	}
}

template <typename T>
void PrintLCS(std::vector<VECT_SIZT>& c, std::vector<T> X, size_t i, size_t j,
				std::ostream& os) {
	if (!i || !j)
		return;
	if (c[i][j] == c[i-1][j])
		PrintLCS(c, X, i - 1, j, os);
	else if (c[i][j] == c[i][j-1])
		PrintLCS(c, X, i, j - 1, os);
	else {
		PrintLCS(c, X, i - 1, j - 1, os);
		os << X[i - 1];
	}
}

}

#endif
