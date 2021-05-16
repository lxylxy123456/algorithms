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

#ifndef ALGORITHMS_DISJOINTSET
#define ALGORITHMS_DISJOINTSET

#include <map>

#include "Graph.hpp"
#include "ProtovEB.hpp"

using std::size_t;

namespace algorithms {

template <typename T>
class DisjointSetForest {
	public:
		DisjointSetForest() {}
		void MakeSet(T x) {
			p[x] = x;
			rank[x] = 0;
		}
		void Link(T x, T y) {
			if (rank[x] > rank[y])
				p[y] = x;
			else {
				p[x] = y;
				if (rank[x] == rank[y])
					rank[y]++;
			}
		}
		T FindSet(T x) {
			if (p[x] == NIL)
				return x;
			if (x != p[x])
				p[x] = FindSet(p[x]);
			return p[x];
		}
		void Union(T x, T y) {
			Link(FindSet(x), FindSet(y));
		}
		std::map<T, T> p;
		std::map<T, size_t> rank;
};

template <typename T>
class ConnectedComponents {
	public:
		ConnectedComponents(GraphAdjList<T>& G) {
			for (auto i = G.V.begin(); i != G.V.end(); i++)
				F.MakeSet(*i);
			for (auto i = G.all_edges(); !i.end(); i++)
				if (F.FindSet(i.s()) != F.FindSet(i.d()))
					F.Union(i.s(), i.d());
		}
		bool SameComponent(T u, T v) {
			return F.FindSet(u) == F.FindSet(v);
		}
		DisjointSetForest<T> F;
};

}

#endif
