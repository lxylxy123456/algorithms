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

#ifndef ALGORITHMS_FINITEAUTOMATONMATCHER
#define ALGORITHMS_FINITEAUTOMATONMATCHER

#include <algorithm>
#include <vector>

#include "NaiveStringMatcher.hpp"

using std::size_t;

namespace algorithms {

template <typename T>
void FiniteAutomatonMatcher(const std::vector<T>& S,
							const std::vector<std::vector<size_t>>& delta,
							T o, std::vector<size_t>& ans) {
	size_t n = S.size(), m = delta.size() - 1;
	size_t q = 0;
	for (size_t i = 0; i < n; i++) {
		q = delta[q][S[i] - o];
		if (q == m)
			ans.push_back(i - m + 1);
	}
}

template <typename T>
void ComputeTransitionFunction(const std::vector<T>& P, size_t d, T o,
								std::vector<std::vector<size_t>>& delta) {
	size_t m = P.size();
	for (size_t q = 0; q <= m; q++) {
		delta.push_back(std::vector<size_t>());
		for (size_t a = 0; a <= d; a++) {
			size_t k = std::min(m, q + 1);
			while (k && (P[k-1] - o != (T) a || !equal(P, 0, P, q - k+1, k-1)))
				k--;
			delta[q].push_back(k);
		}
	}
}

}

#endif
