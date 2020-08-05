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
#define MAIN_FiniteAutomatonMatcher
#endif

#ifndef FUNC_FiniteAutomatonMatcher
#define FUNC_FiniteAutomatonMatcher

#include "utils.h"

#include "NaiveStringMatcher.cpp"

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
#endif

#ifdef MAIN_FiniteAutomatonMatcher
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 40);
	const size_t m = get_argv(argc, argv, 2, 3);
	const size_t d = get_argv(argc, argv, 3, 2);
	const size_t compute = get_argv(argc, argv, 4, 1);
	std::vector<char> S, P;
	random_integers<char>(S, 'a', 'a' + d, n);
	random_integers<char>(P, 'a', 'a' + d, m);
	output_integers(S, "");
	output_integers(P, "");
	std::vector<std::vector<size_t>> delta;
	ComputeTransitionFunction(P, d, 'a', delta);
	std::vector<size_t> ans;
	FiniteAutomatonMatcher(S, delta, 'a', ans);
	output_integers(ans);
	if (compute) {
		std::vector<size_t> ans1;
		NaiveStringMatcher(S, P, ans1);
		output_integers(ans1);
		std::cout << std::boolalpha << (ans == ans1) << std::endl;
	}
	return 0;
}
#endif

