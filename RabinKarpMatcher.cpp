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
#define MAIN_RabinKarpMatcher
#endif

#ifndef FUNC_RabinKarpMatcher
#define FUNC_RabinKarpMatcher

#include "utils.h"

#include "ModularExponentiation.cpp"
#include "NaiveStringMatcher.cpp"

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
	for (size_t s = 0; s <= n - m; s++) {
		if (p == t && equal(P, 0, S, s, m))
			ans.push_back(s); 
		if (s < n - m)
			t = (d * (t - (S[s] - o) * h) + S[s + m] - o) % q; 
	}
}
#endif

#ifdef MAIN_RabinKarpMatcher
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
	std::vector<size_t> ans; 
	RabinKarpMatcher(S, P, d, 1000000007, 'a', ans); 
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

