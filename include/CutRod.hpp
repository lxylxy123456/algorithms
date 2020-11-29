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

#ifndef ALGORITHMS_CUTROD
#define ALGORITHMS_CUTROD

#define CUT_ROD_INFO std::pair<T, std::vector<size_t>>

#include <vector>
#include <map>

namespace algorithms {

template <typename T>
T CutRod(const std::vector<T>& p, size_t n) {
	if (!n)
		return 0;
	T q = p[n];
	for (size_t i = 1; i < n; i++)
		q = std::max(q, p[i] + CutRod(p, n - i));
	return q;
}

template <typename T>
T MemorizedCutRodAux(const std::vector<T>& p, size_t n, std::vector<T>& r) {
	if (r[n] >= 0)
		return r[n];
	if (n == 0)
		return r[n] = 0;
	T q = p[n] + MemorizedCutRodAux(p, 0, r);
	for (size_t i = 1; i < n; i++)
		q = std::max(q, p[i] + MemorizedCutRodAux(p, n - i, r));
	r[n] = q;
	return q;
}

template <typename T>
T MemorizedCutRod(const std::vector<T>& p, size_t n) {
	std::vector<T> r(n + 1, -1);
	return MemorizedCutRodAux(p, n, r);
}

template <typename T>
T BottomUpCutRod(const std::vector<T>& p, size_t n) {
	std::vector<T> r(n + 1, 0);
	for (size_t i = 1; i <= n; i++)
		for (size_t j = 1; j <= i; j++)
			r[i] = std::max(r[i], p[j] + r[i - j]);
	return r[n];
}

template <typename T>
CUT_ROD_INFO ExtendedBottomUpCutRod(const std::vector<T>& p, size_t n) {
	std::vector<T> r(n + 1, 0);
	std::vector<size_t> s(n + 1, 0);
	for (size_t j = 1; j <= n; j++)
		for (size_t i = 1; i <= j; i++)
			if (r[j] < p[i] + r[j - i]) {
				r[j] = p[i] + r[j - i];
				s[j] = i;
			}
	return CUT_ROD_INFO(r[n], s);
}

template <typename T>
CUT_ROD_INFO PrintCutRodSolution(const std::vector<T>& p, size_t n) {
	CUT_ROD_INFO ans = ExtendedBottomUpCutRod(p, n);
	std::vector<size_t>& s = ans.second;
	std::vector<size_t> c;
	for (size_t i = n; i; i -= s[i]) {
		if (s[i])
			c.push_back(s[i]);
		else {
			c.push_back(i);
			break;
		}
	}
	return CUT_ROD_INFO(ans.first, c);
}

}

#endif
