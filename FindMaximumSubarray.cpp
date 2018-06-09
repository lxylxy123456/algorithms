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
#define MAIN_FindMaximumSubarray
#endif

#ifndef FUNC_FindMaximumSubarray
#define FUNC_FindMaximumSubarray

#include <algorithm>
#include "utils.h"

template <typename T>
class sinfo {
	public:
		sinfo(size_t a, size_t b, T c): begin(a), end(b), sum(c) {}
		bool operator<(const sinfo& rhs) const { return sum < rhs.sum; }
		size_t begin; 
		size_t end; 
		T sum; 
}; 

template <typename T>
sinfo<T> FindMaxCrossingSubarray(std::vector<T>& A,size_t l,size_t m,size_t h) {
	auto left  = std::min_element(A.begin() + l, A.begin() + m); 
	auto right = std::max_element(A.begin() + m, A.begin() + h); 
	return sinfo<T>(left - A.begin(), right + 1 - A.begin(), *right - *left); 
}

template <typename T>
sinfo<T> FindMaximumSubarray(std::vector<T>& A, size_t l, size_t h) {
	if (l == h - 1) {
		return sinfo<T>(l, h, A[l]); 
	} else {
		size_t m = (l + h) / 2; 
		sinfo<T> si1 = FindMaximumSubarray(A, l, m); 
		sinfo<T> si2 = FindMaximumSubarray(A, m, h); 
		sinfo<T> si3 = FindMaxCrossingSubarray(A, l, m, h); 
		return std::max(std::max(si1, si2), si3); 
	}
}

template <typename T>
sinfo<T> FindMaximumSubarray(std::vector<T>& A) {
	return FindMaximumSubarray(A, 0, A.size()); 
}

template <typename T, T T0>
sinfo<T> FindMaximumSubarray_On(std::vector<T>& A) {
	sinfo<T> best(0, 0, T0); 
	size_t bci = 0; 	// best continuing index
	T bcv = T0; 		// best continuing value
	for (size_t i = 0; i < A.size(); i++) {
		// sum([bci:i]) = bcv
		if (bcv < 0) {
			bci = i; 
			bcv = T0; 
		}
		bcv += A[i]; 
		best = std::max(best, sinfo<T>(bci, i + 1, bcv)); 
	}
	return best; 
}

#endif

#ifdef MAIN_FindMaximumSubarray
int main(int argc, char *argv[]) {
	std::vector<int> a; 
	int n = get_argv(argc, argv, 1, 10); 
	random_integers(a, -n, n, n); 
	output_integers(a); 
	// sinfo<int> ans = FindMaximumSubarray(a); 
	sinfo<int> ans = FindMaximumSubarray_On<int, 0>(a); 
	std::vector<int> sub_array(a.begin() + ans.begin, a.begin() + ans.end); 
	output_integers(sub_array); 
	return 0; 
}
#endif

