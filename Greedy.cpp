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
#define MAIN_Greedy
#endif

#ifndef FUNC_Greedy
#define FUNC_Greedy

#include <algorithm>
#include <unordered_set>
#include <map>
#include "utils.h"

template <typename T>
class Matroid {
	public :
		Matroid(std::unordered_set<T>& s): S(s) {}
		virtual bool I(std::unordered_set<T> A) const { return true; }
		std::unordered_set<T> S; 
}; 

template <typename T, typename W>
void Greedy(const Matroid<T>& M, W(*w)(T), std::unordered_set<T>& A) {
	using MSI = typename std::unordered_set<T>::const_iterator; 
	using SI = typename std::multimap<W, T>::reverse_iterator; 
	A.clear(); 
	std::multimap<W, T> S; 
	for (MSI i = M.S.begin(); i != M.S.end(); i++)
		S.insert(std::pair<W, T>(w(*i), *i)); 
	for (SI i = S.rbegin(); i != S.rend(); i++) {
		T& x = i->second; 
		A.insert(x); 
		if (!M.I(A))
			A.erase(x); 
	}
}
#endif

#ifdef MAIN_Greedy
size_t f(size_t x) { return (x * 10 + 3) % 17 % 7 + 1; }

int main(int argc, char *argv[]) {
	using MSI = std::unordered_set<size_t>::iterator; 
	const size_t n = get_argv(argc, argv, 1, 6); 
	// prepare data
	std::unordered_set<size_t> S, ans; 
	for (size_t i = 0; i < n; i++)
		S.insert(i); 
	Matroid<size_t> M(S); 
	std::vector<size_t> weights; 
	for (MSI i = M.S.begin(); i != M.S.end(); i++)
		weights.push_back(f(*i)); 
	output_integers(M.S, "\t"); 
	output_integers(weights, "\t"); 
	// call function
	Greedy<size_t, size_t>(M, f, ans); 
	output_integers(ans); 
	return 0; 
}
#endif

