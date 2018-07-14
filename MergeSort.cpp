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
#define MAIN_MergeSort
#endif

#ifndef FUNC_MergeSort
#define FUNC_MergeSort

#include <list>
#include <cassert>
#include "utils.h"

template <typename T>
void Merge(std::vector<T>& A, size_t p, size_t q, size_t r) {
	// A[p:q] and A[q:r] are sorted
	std::list<T> L(A.begin() + p, A.begin() + q); 
	std::list<T> R(A.begin() + q, A.begin() + r); 
	for (size_t k = p; k < r; k++) {
		if (!R.size() || (L.size() && L.front() <= R.front())) {
			A[k] = L.front(); 
			L.pop_front(); 
		} else {
			A[k] = R.front(); 
			R.pop_front(); 
		}
	}
	assert(!R.size() && !L.size()); 
}

template <typename T>
void MergeSort(std::vector<T>& A, size_t p, size_t r) {
	if (p < r - 1) {
		size_t q = (p + r) / 2; 
		MergeSort(A, p, q); 
		MergeSort(A, q, r); 
		Merge(A, p, q, r); 
	}
}

template <typename T>
void MergeSort(std::vector<T>& A) {
	MergeSort(A, 0, A.size()); 
}
#endif

#ifdef MAIN_MergeSort
int main(int argc, char *argv[]) {
	std::vector<int> a; 
	int n = get_argv(argc, argv, 1, 10); 
	random_integers(a, 0, n - 1, n); 
	MergeSort(a); 
	output_integers(a); 
	return 0; 
}
#endif

