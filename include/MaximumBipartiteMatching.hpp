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

#ifndef ALGORITHMS_MAXIMUMBIPARTITEMATCHING
#define ALGORITHMS_MAXIMUMBIPARTITEMATCHING

#include <cassert>

#include "FordFulkerson.hpp"

using std::size_t;

namespace algorithms {

template <typename GT, typename T>
void MaximumBipartiteMatching(GT& G, uset<Edge<T>, EdgeHash<T>>& ans) {
	GraphAdjList<T> GF(true);
	umap<Edge<T>, T, EdgeHash<size_t>> c, f;
	T s = G.V.size(), t = s + 1;
	assert(G.V.find(s) == G.V.end() && G.V.find(t) == G.V.end());
	for (auto i = G.L.begin(); i != G.L.end(); i++) {
		GF.add_edge(s, *i);
		c[Edge<T>(s, *i, true)] = 1;
	}
	for (auto i = G.R.begin(); i != G.R.end(); i++) {
		GF.add_edge(*i, t);
		c[Edge<T>(*i, t, true)] = 1;
	}
	for (auto i = G.all_edges(); !i.end(); i++) {
		GF.add_edge(i.s(), i.d());
		c[Edge<T>(i.s(), i.d(), true)] = 1;
	}
	FordFulkerson(GF, c, s, t, f);
	for (auto i = G.all_edges(); !i.end(); i++)
		if (f[Edge<T>(i.s(), i.d(), true)])
			ans.insert(*i);
}

}

#endif
