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

#ifndef ALGORITHMS_DIJKSTRA
#define ALGORITHMS_DIJKSTRA

#include <map>

#include "BellmanFord.hpp"
#include "FibHeap.hpp"

using std::size_t;

namespace algorithms {

template <typename GT, typename T, typename WT>
void Dijkstra(GT& G, umap_WT& w, T s, umap<T, RelaxInfo<T, WT>>& ans) {
	using QT = std::pair<RelaxInfo<T, WT>, T>;
	InitializeSingleSource(G, s, ans);
	uset<T> S;
	FibHeap<QT> Q;
	umap<T, FNode<QT>*> Q_ptr;
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		Q_ptr[*i] = Q.FibHeapInsert(QT(ans[*i], *i));
	while (Q.FibHeapMinimum()) {
		FNode<QT>* m = Q.FibHeapExtractMin();
		T u = m->key.second;
		delete m;
		S.insert(u);
		for (auto i = G.edges_from(u); !i.end(); i++) {
			const T& v = i.d();
			if (S.find(v) == S.end()) {
				Relax(u, v, w, ans);
				Q.FibHeapDecreaseKey(Q_ptr[v], QT(ans[v], v));
			}
		}
	}
}

}

#endif
