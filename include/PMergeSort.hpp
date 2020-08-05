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

#ifndef ALGORITHMS_PMERGESORT
#define ALGORITHMS_PMERGESORT

#include <thread>
#include "utils.h"

#include "MergeSort.hpp"

namespace algorithms {


template <typename T>
void MergeSort_prime(std::vector<T>* A, size_t p, size_t r) {
	if (p < r - 1) {
		size_t q = (p + r) / 2;
		std::thread t1(MergeSort_prime<T>, A, p, q);
		MergeSort_prime(A, q, r);
		t1.join();
		Merge(*A, p, q, r);
	}
}

template <typename T>
void MergeSort_prime(std::vector<T>& A) {
	MergeSort_prime(&A, 0, A.size());
}

template <typename T>
size_t BinarySearch(T x, std::vector<T>& S, size_t p, size_t r) {
	size_t low = p;
	size_t high = std::max(p, r);
	while (low < high) {
		size_t mid = (low + high + 1) / 2;
		if (x <= S[mid - 1])
			high = mid - 1;
		else
			low = mid;
	}
	return low;
}

template <typename T>
void PMerge(std::vector<T>* S, size_t p1, size_t r1, size_t p2, size_t r2,
			std::vector<T>* A, size_t p3) {
	size_t n1 = r1 - p1;
	size_t n2 = r2 - p2;
	if (n1 < n2) {
		std::swap(p1, p2);
		std::swap(r1, r2);
		std::swap(n1, n2);
	}
	if (!n1)
		return;
	size_t q1 = (p1 + r1) / 2;
	size_t q2 = BinarySearch((*S)[q1], *S, p2, r2);
	size_t q3 = p3 + (q1 - p1) + (q2 - p2);
	(*A)[q3] = (*S)[q1];
	std::thread t1(PMerge<T>, S, p1, q1, p2, q2, A, p3);
	PMerge(S, q1 + 1, r1, q2, r2, A, q3 + 1);
	t1.join();
}

template <typename T>
void PMergeSort(std::vector<T>* A, size_t p, size_t r, std::vector<T>* B,
				size_t s) {
	size_t n = r - p;
	if (n == 1)
		(*B)[s] = (*A)[p];
	else {
		std::vector<T> S(n);
		size_t q = (p + r) / 2;
		size_t qq = q - p;
		std::thread t1(PMergeSort<T>, A, p, q, &S, 0);
		PMergeSort(A, q, r, &S, qq);
		t1.join();
		PMerge(&S, 0, qq, qq, n, B, s);
	}
}

template <typename T>
void PMergeSort(std::vector<T>& A, std::vector<T>& B) {
	PMergeSort(&A, 0, A.size(), &B, 0);
}

}

#endif
