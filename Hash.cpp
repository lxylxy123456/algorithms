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
#define MAIN_Hash
#endif

#ifndef FUNC_Hash
#define FUNC_Hash

#include <vector>
#include "utils.h"

class DivisionHash {
	public:
		DivisionHash(size_t mm): m(mm) {}
		size_t operator()(size_t k) { return k % m; }
		size_t m; 
}; 

class MultiplicationHash {
	public:
		MultiplicationHash(size_t ww, size_t pp, float A): 
			w(ww), K(1 << w), p(pp), s(A * K), m(1 << p) {}
		size_t operator()(size_t k) {
			return ((k * s) & (K - 1)) >> (w - p); 
		}
		size_t w, K, p, s, m; 
}; 

class UniversalHash {
	public:
		UniversalHash(size_t pp, size_t mm): p(pp), m(mm) {
			std::random_device rd; 
			a = std::uniform_int_distribution<int>(1, p - 1)(rd); 
			b = std::uniform_int_distribution<int>(0, p - 1)(rd); 
		}
		size_t operator()(size_t k) {
			return ((a * k + b) % p) % m; 
		}
		size_t p, m, a, b; 
}; 
#endif

#ifdef MAIN_Hash
int main(int argc, char *argv[]) {
	size_t k = get_argv(argc, argv, 1, 7);  	// max key < 1<<k
	size_t md = get_argv(argc, argv, 2, 23); 	// prime in DivisionHash
	size_t mm = get_argv(argc, argv, 3, 5); 	// MultiplicationHash: m < 1<<p
	size_t p = get_argv(argc, argv, 4, 131);  	// prime in UniversalHash > 1<<k
	DivisionHash d(md); 
	MultiplicationHash m(k, mm, 0.6180339887); 
	UniversalHash u(p, md); 
	std::cout << "key\tdiv\tmul\tuniv" << std::endl; 
	for (size_t i = 0; i < 1u<<k; i++) {
		std::cout << i << '\t' << d(i) << '\t' << m(i)
				 << '\t' << u(i) << std::endl; 
	}
	return 0; 
}
#endif

