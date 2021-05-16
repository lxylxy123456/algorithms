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

#ifndef ALGORITHMS_NAIVESTRINGMATCHER
#define ALGORITHMS_NAIVESTRINGMATCHER

#include <vector>

using std::size_t;

namespace algorithms {

template <typename T>
bool equal(const std::vector<T>& S, size_t Ss,
			const std::vector<T>& P, size_t Ps, size_t n) {
	for (size_t i = 0; i < n; i++)
		if (S[Ss + i] != P[Ps + i])
			return false;
	return true;
}

template <typename T>
bool equal(const std::vector<T>& S, size_t Ss, size_t Se,
			const std::vector<T>& P, size_t Ps, size_t Pe) {
	size_t n = Se - Ss;
	if (n != Pe - Ps)
		return false;
	return equal(S, P, Ss, Ps, n);
}

template <typename T>
void NaiveStringMatcher(const std::vector<T>& S, const std::vector<T>& P,
						std::vector<size_t>& ans) {
	size_t n = S.size(), m = P.size();
	for (size_t s = 0; s + m <= n; s++)
		if (equal(P, 0, S, s, m))
			ans.push_back(s);
}

}

#endif
