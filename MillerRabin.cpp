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
#define MAIN_MillerRabin
#endif

#ifndef FUNC_MillerRabin
#define FUNC_MillerRabin

#include "utils.h"

#include "ModularExponentiation.cpp"

template <typename T>
bool Witness(T a, T n) {
	T t = 0, u = n - 1; 
	while (!(u & 1)) {
		t++; 
		u >>= 1; 
	}
	T x0 = ModularExponentiation(a, u, n); 
	for (T i = 0; i < t; i++) {
		T x1 = x0 * x0 % n; 
		if (x1 == 1 && x0 != 1 && x0 != n - 1)
			return true; 
		x0 = x1; 
	}
	if (x0 != 1)
		return true; 
	return false; 
}

template <typename T>
bool MillerRabin(T n, size_t s) {
	std::vector<T> a; 
	random_integers<T>(a, 1, n - 1, s); 
	for (auto i = a.begin(); i != a.end(); i++) {
		if (Witness(*i, n))
			return false; 
	}
	return true; 
}
#endif

#ifdef MAIN_MillerRabin
int main(int argc, char *argv[]) {
	const size_t nn = get_argv(argc, argv, 1, 30); 
	const size_t s = get_argv(argc, argv, 2, 5); 
	const size_t tries = get_argv(argc, argv, 3, 1); 
	using T = long long int; 
    std::random_device rd; 
    std::uniform_int_distribution<T> dis(1 << (nn - 1), 1 << nn); 
    for (size_t i = 0; i < tries; i++) {
		T n = get_argv(argc, argv, 4 + i, dis(rd) << 1 | 1); 
		bool ans = MillerRabin(n, s); 
		std::cout << n << "\t" << std::boolalpha << ans << std::endl;
	}
	return 0; 
}
#endif

