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
#define MAIN_ModularExponentiation
#endif

#ifndef FUNC_ModularExponentiation
#define FUNC_ModularExponentiation

#include "utils.h"

#include "Euclid.cpp"

template <typename T>
T ModularExponentiation(T a, T b, T n) {
	T c = 0; 
	T d = 1; 
	for (T i = log2(b); i >= 0; i--) {
		c *= 2; 
		d = d * d % n; 
		if (b & 1 << i) {
			c++; 
			d = d * a % n; 
		}
	}
	assert(c == b); 
	return d; 
}
#endif

#ifdef MAIN_ModularExponentiation
int main(int argc, char *argv[]) {
	const size_t nn = get_argv(argc, argv, 1, 4); 
	using T = long long int; 
    std::random_device rd; 
    std::uniform_int_distribution<T> dis(0, 1 << nn); 
    std::uniform_int_distribution<T> disn(1, 1 << nn); 
	T a = get_argv(argc, argv, 2, dis(rd)); 
	T b = get_argv(argc, argv, 3, dis(rd)); 
	T n = get_argv(argc, argv, 4, disn(rd)); 
	T ans = ModularExponentiation(a, b, n); 
	std::cout << a << " ** " << b << " % " << n << " = " << ans << std::endl; 
	return 0; 
}
#endif

