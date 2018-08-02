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
#define MAIN_Pseudoprime
#endif

#ifndef FUNC_Pseudoprime
#define FUNC_Pseudoprime

#include "utils.h"

#include "ModularExponentiation.cpp"

template <typename T>
bool Pseudoprime(T n) {
	if (ModularExponentiation((T) 2, n - 1, n) != 1)
		return false; 
	else
		return true; 
}
#endif

#ifdef MAIN_Pseudoprime
int main(int argc, char *argv[]) {
	const size_t nn = get_argv(argc, argv, 1, 30); 
	const size_t tries = get_argv(argc, argv, 2, 1); 
	using T = long long int; 
    std::random_device rd; 
    std::uniform_int_distribution<T> dis(1 << (nn - 1), 1 << nn); 
    for (size_t i = 0; i < tries; i++) {
		T n = get_argv(argc, argv, 3 + i, dis(rd) << 1 | 1); 
		std::cout << n << "\t" << std::boolalpha << Pseudoprime(n) << std::endl;
	}
	return 0; 
}
#endif

