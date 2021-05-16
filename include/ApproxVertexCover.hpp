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

#ifndef ALGORITHMS_APPROXVERTEXCOVER
#define ALGORITHMS_APPROXVERTEXCOVER

#include "Graph.hpp"

using std::size_t;

namespace algorithms {

template <typename GT, typename T>
void ApproxVertexCover(GT& G, uset<T>& C) {
	uset<Edge<T>, EdgeHash<T>> E;
	for (auto i = G.all_edges(); !i.end(); i++)
		E.insert(*i);
	while (E.begin() != E.end()) {
		Edge<T> e = *E.begin();
		const T &u = e.s, &v = e.d;
		C.insert(u);
		C.insert(v);
		for (auto i = G.edges_from(u); !i.end(); i++)
			E.erase(*i);
		for (auto i = G.edges_from(v); !i.end(); i++)
			E.erase(*i);
	}
}

}

#endif
