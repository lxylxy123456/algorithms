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

#ifndef ALGORITHMS_ANYSEGMENTSINTERSECT
#define ALGORITHMS_ANYSEGMENTSINTERSECT

#include <algorithm>
#include <cassert>
#include <vector>

#include "RedBlackTree.hpp"
#include "SegmentsIntersect.hpp"

using std::size_t;

namespace algorithms {

/*
	Exercise 33.2-2
		(Not following hints in the book)
		Suppose p1p2 and p3p4 are the line segments; p1 and p3 are on the left
		x = x1 + (x2 - x1) * a
		a = (x - x1) / (x2 - x1)
		y12 = y1 + (y2 - y1) * (x - x1) / (x2 - x1)
		y34 = y3 + (y4 - y3) * (x - x3) / (x4 - x3)
		y12 -> y1 * (x2 - x1) * (x4 - x3) + (y2 - y1) * (x - x1) * (x4 - x3)
		y34 -> y3 * (x2 - x1) * (x4 - x3) + (y4 - y3) * (x - x3) * (x2 - x1)
*/

template <typename T>
class Segment {
	public:
		Segment() {}
		Segment(Vector<T> A, Vector<T> B, T& X): a(A), b(B), x(&X) {
			assert(a.x != b.x);
			if (a.x > b.x)
				std::swap(a, b);
		}
		bool operator==(const Segment& r) const {
			return a == r.a && b == r.b;
		}
		bool operator<(const Segment& r) const {
			const Segment& l = *this;
			Vector<T> d12 = l.b - l.a, d34 = r.b - r.a;
			T y12 = (l.a.y * d12.x + d12.y * (*x - l.a.x)) * d34.x;
			T y34 = (r.a.y * d34.x + d34.y * (*x - r.a.x)) * d12.x;
			return y12 < y34;
		}
		Vector<T> a, b;
		T* x;
};

template <typename T>
bool SegmentsIntersect(const Segment<T>& a, const Segment<T>& b) {
	return SegmentsIntersect(a.a, a.b, b.a, b.b);
}

template <typename T>
class EndPoint {
	public:
		EndPoint(Segment<T>& S, bool st): s(&S), start(st) {
			if (st)
				p = &s->a;
			else
				p = &s->b;
		}
		bool operator<(const EndPoint<T>& rhs) const {
			if (p->x < rhs.p->x)
				return true;
			if (rhs.p->x < p->x)
				return false;
			if (start && !rhs.start)
				return true;
			if (rhs.start && !start)
				return false;
			return p->y < rhs.p->y;
		}
		Segment<T>* s;
		Vector<T>* p;
		bool start;
};

template <typename T>
class SweepLineStatus {
	public:
		void Insert(const Segment<T>& s) {
			RB.TreeInsert(s);
		}
		void Delete(const Segment<T>& s) {
			RB.TreeDelete(RB.TreeSearch(s));
		}
		Segment<T>* Above(const Segment<T>& s) {
			Node<CData<Segment<T>>>* ans = RB.TreeSuccessor(RB.TreeSearch(s));
			if (ans != RB.nil)
				return &ans->data.data;
			else
				return nullptr;
		}
		Segment<T>* Below(const Segment<T>& s) {
			Node<CData<Segment<T>>>* ans = RB.TreePredecessor(RB.TreeSearch(s));
			if (ans != RB.nil)
				return &ans->data.data;
			else
				return nullptr;
		}
		RedBlackTree<Segment<T>> RB;
};

template <typename T>
bool AnySegmentsIntersect(std::vector<Segment<T>>& S) {
	T& x = *S[0].x;
	SweepLineStatus<T> SLS;
	std::vector<EndPoint<T>> endpoints;
	endpoints.reserve(S.size() * 2);
	for (auto i = S.begin(); i != S.end(); i++) {
		endpoints.push_back(EndPoint<T>(*i, false));
		endpoints.push_back(EndPoint<T>(*i, true));
	}
	std::sort(endpoints.begin(), endpoints.end());
	for (auto i = endpoints.begin(); i != endpoints.end(); i++) {
		Segment<T>& s = *i->s;
		x = i->p->x;
		if (i->start) {
			SLS.Insert(s);
			Segment<T>* a = SLS.Above(s), *b = SLS.Below(s);
			if ((a && SegmentsIntersect(s, *a)) ||
				(b && SegmentsIntersect(s, *b)))
				return true;
		} else {
			Segment<T>* a = SLS.Above(s), *b = SLS.Below(s);
			if (a && b && SegmentsIntersect(*a, *b))
				return true;
			SLS.Delete(s);
		}
	}
	return false;
}

}

#endif
