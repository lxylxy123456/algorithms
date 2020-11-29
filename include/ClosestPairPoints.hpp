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

#ifndef ALGORITHMS_CLOSESTPAIRPOINTS
#define ALGORITHMS_CLOSESTPAIRPOINTS

#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <vector>

#include "SegmentsIntersect.hpp"

namespace algorithms {

#define uset_vec typename std::unordered_set<Vector<T>, VectorHash<T>>

template <typename T>
class VecPair {
	public:
		VecPair(): cached(false) {}
		VecPair(Vector<T> A, Vector<T> B): a(A), b(B), cached(false) {}
		T Dist() const {
			if (!cached) {
				T dx = a.x - b.x, dy = a.y - b.y;
				cache = dx * dx + dy * dy;
				cached = true;
			}
			return cache;
		}
		Vector<T> a, b;
		mutable T cache;
		mutable bool cached;
};

template <typename T>
VecPair<T> ClosestPairPoints(uset_vec& P, std::vector<Vector<T>>& X,
										std::vector<Vector<T>>& Y) {
	assert(P.size() == X.size() && X.size() == Y.size());
	if (X.size() <= 3) {
		VecPair<T> ans(X[0], X[1]);
		if (X.size() == 3) {
			VecPair<T> ans1(X[0], X[2]), ans2(X[1], X[2]);
			if (ans.Dist() > ans1.Dist())
				ans = ans1;
			if (ans.Dist() > ans2.Dist())
				ans = ans2;
		}
		return ans;
	}
	size_t index = X.size() / 2;
	T l = X[index].x;
	uset_vec PL(X.begin(), X.begin() + index), PR(X.begin() + index, X.end());
	std::vector<Vector<T>> XL(X.begin(), X.begin() + index);
	std::vector<Vector<T>> XR(X.begin() + index, X.end());
	std::vector<Vector<T>> YL, YR;
	for (auto i = Y.begin(); i != Y.end(); i++) {
		if (PL.find(*i) != PL.end())
			YL.push_back(*i);
		else
			YR.push_back(*i);
	}
	VecPair<T> delta = ClosestPairPoints(PL, XL, YL);
	VecPair<T> tmp = ClosestPairPoints(PR, XR, YR);
	if (tmp.Dist() < delta.Dist())
		delta = tmp;
	std::vector<Vector<T>> YY;
	for (auto i = Y.begin(); i != Y.end(); i++) {
		T d = i->x - l;
		if (d*d < delta.Dist())
			YY.push_back(*i);
	}
	for (size_t i = 0; i < YY.size(); i++)
		for (size_t j = i + 1; j <= i + 8 && j < YY.size(); j++) {
			VecPair<T> vp(YY[i], YY[j]);
			if (vp.Dist() < delta.Dist())
				delta = vp;
		}
	return delta;
}

template <typename T>
VecPair<T> ClosestPairPoints(std::vector<Vector<T>>& Q) {
	std::vector<Vector<T>> X(Q), Y(Q);
	uset_vec P(Q.begin(), Q.end());
	auto fX = [](const Vector<T>& a, const Vector<T>& b){ return a.x < b.x; };
	auto fY = [](const Vector<T>& a, const Vector<T>& b){ return a.y < b.y; };
	std::sort(X.begin(), X.end(), fX);
	std::sort(Y.begin(), Y.end(), fY);
	return ClosestPairPoints(P, X, Y);
}

}

#endif
