//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#ifndef ALGORITHMS_FINDMAXIMUMSUBARRAY
#define ALGORITHMS_FINDMAXIMUMSUBARRAY

#include <algorithm>
#include <vector>

using std::size_t;

namespace algorithms {

template <typename T>
class sinfo {
	public:
		sinfo(std::size_t a, std::size_t b, T c): begin(a), end(b), sum(c) {}
		bool operator<(const sinfo& rhs) const { return sum < rhs.sum; }
		std::size_t begin;
		std::size_t end;
		T sum;
};

template <typename T>
sinfo<T> FindMaxCrossingSubarray(std::vector<T>& A, std::size_t l,
									std::size_t m, std::size_t h) {
	T lsum, rsum, sum = 0;
	std::size_t lmax, rmax;
	for (std::size_t i = m; (i--) > l; ) {
		sum += A[i];
		if (i == m - 1 || sum > lsum) {
			lsum = sum;
			lmax = i;
		}
	}
	sum = 0;
	for (std::size_t j = m; j < h; j++) {
		sum += A[j];
		if (j == m || sum > rsum) {
			rsum = sum;
			rmax = j + 1;
		}
	}
	return sinfo<T>(lmax, rmax, lsum + rsum);
}

template <typename T>
sinfo<T> FindMaximumSubarray(std::vector<T>& A, std::size_t l, std::size_t h) {
	if (l == h - 1) {
		return sinfo<T>(l, h, A[l]);
	} else {
		std::size_t m = (l + h) / 2;
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
	std::size_t bci = 0; 	// best continuing index
	T bcv = T0; 		// best continuing value
	for (std::size_t i = 0; i < A.size(); i++) {
		// sum([bci:i]) = bcv
		if (bcv < 0) {
			bci = i;
			bcv = T0;
		}
		bcv += A[i];
		best = std::max(best, sinfo<T>(bci, i + 1, bcv));
	}
	if (best.begin == best.end) {
		best.begin = std::max_element(A.begin(), A.end()) - A.begin();
		best.end = best.begin + 1;
		best.sum = A[best.begin];
	}
	return best;
}

}

#endif
