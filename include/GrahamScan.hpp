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

#ifndef ALGORITHMS_GRAHAMSCAN
#define ALGORITHMS_GRAHAMSCAN

#include <algorithm>
#include "utils.h"

#include "SegmentsIntersect.hpp"

namespace algorithms {

template <typename T>
class PolarPoint {
	public:
		PolarPoint() {}
		PolarPoint(Vector<T> P, Vector<T>& P0): p(P), p0(&P0) {}
		bool operator<(const PolarPoint<T>& rhs) const {
			Vector<T> l = this->p - *p0;
			Vector<T> r = rhs.p - *p0;
			T cross = l.Cross(r);
			if (cross > 0)
				return true;
			else if (cross < 0)
				return false;
			else
				return l.Length() < r.Length();
		}
		Vector<T> p, *p0;
};

template <typename T>
void GrahamScan(std::vector<Vector<T>>& Q, std::vector<Vector<T>>& ans) {
	Vector<T> p0 = Q[0];
	std::vector<PolarPoint<T>> Q_sorted;
	Q_sorted.reserve(Q.size() - 1);
	for (auto i = Q.begin(); i != Q.end(); i++) {
		Vector<T> pi = *i;
		if (pi.y < p0.y || (pi.y == p0.y && pi.x < p0.x))
			std::swap(p0, pi);
		Q_sorted.push_back(PolarPoint<T>(pi, p0));
	}
	std::sort(Q_sorted.begin(), Q_sorted.end());
	std::vector<Vector<T>> P;
	for (auto i = Q_sorted.begin(); i != Q_sorted.end(); i++) {
		while (i+1 != Q_sorted.end() && (i->p - p0).Cross((i+1)->p - p0) == 0)
			i++;
		P.push_back(i->p);
	}
	ans.push_back(p0);
	ans.push_back(P[0]);
	ans.push_back(P[1]);
	for (size_t i = 2; i < P.size(); i++) {
		while (ans.size() >= 2) {
			Vector<T>& top = ans[ans.size() - 1];
			Vector<T>& next_to_top = ans[ans.size() - 2];
			if ((top - next_to_top).Cross(P[i] - next_to_top) > 0)
				break;
			else
				ans.pop_back();
		}
		ans.push_back(P[i]);
	}
}

}

#endif
