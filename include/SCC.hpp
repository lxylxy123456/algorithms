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

#ifndef ALGORITHMS_SCC
#define ALGORITHMS_SCC

#include <deque>

#include "DisjointSet.hpp"
#include "TopologicalSort.hpp"

using std::size_t;

namespace algorithms {

template <typename GT, typename T, typename VT>
void DFSVisit_SCC(GT& G, VT& inf, DisjointSetForest<T>& D, T u, size_t& time) {
	DFSInfo<T>& info = inf[u];
	info.set_color(dfs_gray, time);
	for (auto i = G.edges_from(u); !i.end(); i++) {
		T v = i.d();
		DFSInfo<T>& vinfo = inf[v];
		if (vinfo.color == dfs_white) {
			vinfo.set_pi(u);
			D.Union(u, v);
			DFSVisit_SCC(G, inf, D, v, time);
		}
	}
	info.set_color(dfs_black, time);
}

template <typename GT, typename T>
void DFS_SCC(GT& G, std::deque<T>& order, DisjointSetForest<T>& D) {
	umap<T, DFSInfo<T>> inf;
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		inf[*i] = DFSInfo<T>();
	size_t time = 0;
	for (auto i = order.begin(); i != order.end(); i++) {
		if (inf[*i].color == dfs_white)
			DFSVisit_SCC(G, inf, D, *i, time);
	}
}

template <typename GT, typename T>
void StronglyConnectedComponents(GT& G, DisjointSetForest<T>& D) {
	std::deque<T> order;
	TopologicalSort(G, order);
	GT G_transpose = G;
	G_transpose.transpose();
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		D.MakeSet(*i);
	DFS_SCC(G_transpose, order, D);
}

}

#endif
