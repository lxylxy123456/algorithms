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

#ifndef ALGORITHMS_SUBSETSUM
#define ALGORITHMS_SUBSETSUM

#include <set>

using std::size_t;

namespace algorithms {

#define set_T typename std::set<T>

template <typename T>
T ExactSubsetSum(set_T& S, T t) {
	set_T L;
	L.insert(0);
	for (set_T::iterator i = S.begin(); i != S.end(); i++) {
		set_T L1(L);
		for (set_T::iterator j = L.begin(); j != L.end(); j++)
			if (*j + *i <= t)
				L1.insert(*j + *i);
		L = L1;
	}
	return *L.rbegin();
}

template <typename T, typename FT>
set_T Trim(set_T& L, T t, FT delta) {
	set_T M;
	set_T::iterator i = L.begin();
	T last = *i;
	M.insert(last);
	for (i++; i != L.end(); i++)
		if (*i > last * (1 + delta) && *i <= t) {
			M.insert(*i);
			last = *i;
		}
	return M;
}

template <typename T, typename FT>
T ApproxSubsetSum(set_T& S, T t, FT e) {
	std::size_t n = S.size();
	set_T L;
	L.insert(0);
	for (set_T::iterator i = S.begin(); i != S.end(); i++) {
		set_T L1(L);
		for (set_T::iterator j = L.begin(); j != L.end(); j++)
			if (*j + *i <= t)
				L1.insert(*j + *i);
		L = Trim(L1, t, e / (2 * n));
	}
	return *L.rbegin();
}

}

#endif
