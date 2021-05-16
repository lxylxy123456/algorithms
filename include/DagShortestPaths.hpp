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

#ifndef ALGORITHMS_DAGSHORTESTPATHS
#define ALGORITHMS_DAGSHORTESTPATHS

#include <deque>

#include "BellmanFord.hpp"
#include "TopologicalSort.hpp"

namespace algorithms {

template <typename GT, typename T, typename WT>
void DagShortestPaths(GT& G, umap_WT& w, T s, umap<T, RelaxInfo<T, WT>>& ans) {
	std::deque<T> order;
	TopologicalSort(G, order);
	InitializeSingleSource(G, s, ans);
	for (auto i = order.begin(); i != order.end(); i++)
		for (auto j = G.edges_from(*i); !j.end(); j++)
			Relax(j.s(), j.d(), w, ans);
}

}

#endif
