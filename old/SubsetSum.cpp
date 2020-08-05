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

#ifndef MAIN
#define MAIN
#define MAIN_SubsetSum
#endif

#ifndef FUNC_SubsetSum
#define FUNC_SubsetSum

#include <cassert>
#include <iomanip>
#include <set>
#include "utils.h"

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
	size_t n = S.size();
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
#endif

#ifdef MAIN_SubsetSum
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 100);
	const size_t m = get_argv(argc, argv, 2, 100);
	using T = int;
	using FT = float;
	const T t = get_argv(argc, argv, 3, 500);
	const FT e = get_argv(argc, argv, 4, 0.9);
	std::vector<T> S_int;
	random_integers(S_int, 1, m, n);
	set_T S;
	for (auto i = S_int.begin(); i != S_int.end(); i++)
		S.insert(*i);
	output_integers(S);
    std::random_device rd;
	std::cout << "t = " << t << std::endl;
	std::cout << "exact  = " << ExactSubsetSum(S, t) << std::endl;
	std::cout << "approx = " << ApproxSubsetSum(S, t, e) << std::endl;
	return 0;
}
#endif

