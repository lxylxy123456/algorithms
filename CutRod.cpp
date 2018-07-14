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
#define MAIN_CutRod
#endif

#ifndef FUNC_CutRod
#define FUNC_CutRod

#define CUT_ROD_INFO std::pair<T, std::vector<size_t>>

#include <iomanip>
#include <map>
#include "utils.h"

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
#endif

#ifdef MAIN_CutRod
int main(int argc, char *argv[]) {
	using T = int; 
	const size_t n = get_argv(argc, argv, 1, 16); 
	const size_t compute = get_argv(argc, argv, 2, 15); 
	std::vector<int> l; 
	random_integers(l, 0, n - 1, n); 
	std::vector<int> p = {0}; 
	for (std::vector<int>::iterator i = l.begin(); i != l.end(); i++)
		p.push_back(*i + *(p.end() - 1)); 
	output_integers(p); 
	if (compute >> 0 & 1) {
		std::cout << std::left << std::setw(24) << "CutRod"; 
		std::cout << CutRod(p, n) << std::endl; 
	}
	if (compute >> 1 & 1) {
		std::cout << std::left << std::setw(24) << "MemorizedCutRod"; 
		std::cout << MemorizedCutRod(p, n) << std::endl; 
	}
	if (compute >> 2 & 1) {
		std::cout << std::left << std::setw(24) << "BottomUpCutRod"; 
		std::cout << BottomUpCutRod(p, n) << std::endl; 
	}
	if (compute >> 3 & 1) {
		std::cout << std::left << std::setw(24) << "ExtendedBottomUpCutRod"; 
		CUT_ROD_INFO ans = PrintCutRodSolution(p, n); 
		std::cout << ans.first << std::endl; 
		output_integers(ans.second); 
	}
	return 0; 
}
#endif

