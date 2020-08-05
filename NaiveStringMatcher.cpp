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
#define MAIN_NaiveStringMatcher
#endif

#ifndef FUNC_NaiveStringMatcher
#define FUNC_NaiveStringMatcher

#include "utils.h"

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
	for (size_t s = 0; s <= n - m; s++)
		if (equal(P, 0, S, s, m))
			ans.push_back(s);
}
#endif

#ifdef MAIN_NaiveStringMatcher
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 40);
	const size_t m = get_argv(argc, argv, 2, 3);
	const size_t d = get_argv(argc, argv, 3, 2);
	std::vector<char> S, P;
	random_integers<char>(S, 'a', 'a' + d, n);
	random_integers<char>(P, 'a', 'a' + d, m);
	output_integers(S, "");
	output_integers(P, "");
	std::vector<size_t> ans;
	NaiveStringMatcher(S, P, ans);
	output_integers(ans);
	return 0;
}
#endif

