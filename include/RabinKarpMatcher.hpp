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

#ifndef ALGORITHMS_RABINKARPMATCHER
#define ALGORITHMS_RABINKARPMATCHER

#include "ModularExponentiation.hpp"
#include "NaiveStringMatcher.hpp"

namespace algorithms {

template <typename T>
void RabinKarpMatcher(const std::vector<T>& S, const std::vector<T>& P,
						size_t d, size_t q, T o, std::vector<size_t>& ans) {
	size_t n = S.size(), m = P.size();
	size_t h = ModularExponentiation(d, m - 1, q);
	size_t p = 0, t = 0;
	for (size_t i = 0; i < m; i++) {
		p = (d * p + P[i] - o) % q;
		t = (d * t + S[i] - o) % q;
	}
	for (size_t s = 0; s + m <= n; s++) {
		if (p == t && equal(P, 0, S, s, m))
			ans.push_back(s);
		if (s < n - m)
			t = (d * (t - (S[s] - o) * h) + S[s + m] - o) % q;
	}
}

}

#endif
