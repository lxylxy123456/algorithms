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
#define MAIN_RandomizedSelect
#endif

#ifndef FUNC_RandomizedSelect
#define FUNC_RandomizedSelect

#include "utils.h"
#include "Quicksort.cpp"

template <typename T>
T RandomizedSelect(T p, T r, size_t i) {
	if (p == r - 1)
		return p; 
	T q = RandomizedPartition(p, r); 
	size_t k = q - p; 
	if (i == k)
		return q; 
	else if (i < k)
		return RandomizedSelect(p, q, i); 
	else
		return RandomizedSelect(q + 1, r, i - k - 1); 
}

template <typename T>
T RandomizedSelect(std::vector<T> A, size_t i) {
	return *RandomizedSelect(A.begin(), A.end(), i); 
}

template <typename T>
T RandomizedSelectIter(std::vector<T> A, size_t i) {
	typename std::vector<T>::iterator p = A.begin(), q, r = A.end(); 
	while (true) {
		if (p == r - 1)
			return *p; 
		q = RandomizedPartition(p, r); 
		size_t k = q - p; 
		if (i == k)
			return *q; 
		else if (i < k)
			r = q; 
		else {
			p = q + 1; 
			i -= k + 1; 
		}
	}
}
#endif

#ifdef MAIN_RandomizedSelect
int main(int argc, char *argv[]) {
	std::vector<int> a; 
	const size_t n = get_argv(argc, argv, 1, 10); 
	const size_t compute = get_argv(argc, argv, 2, 7); 
	random_integers(a, 0, n - 1, n); 

	std::random_device rd; 
    std::uniform_int_distribution<int> d(0, n - 1); 
	size_t i = d(rd); 

	std::vector<int> b(a); 
	int ans1, ans2, ans3; 

	output_integers(a); 
	if (compute >> 0 & 1) {
		Quicksort(b.begin(), b.end()); 
		ans1 = b[i]; 
		std::cout << ans1 << std::endl; 
	}
	if (compute >> 1 & 1) {
		ans2 = RandomizedSelect(a, i); 
		std::cout << ans2 << std::endl; 
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (ans1 == ans2) << std::endl; 
	}
	if (compute >> 2 & 1) {
		ans3 = RandomizedSelectIter(a, i); 
		std::cout << ans3 << std::endl; 
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (ans1 == ans3) << std::endl; 
	}
	return 0; 
}
#endif

