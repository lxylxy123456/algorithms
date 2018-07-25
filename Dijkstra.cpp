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

#ifndef MAIN
#define MAIN
#define MAIN_Dijkstra
#endif

#ifndef FUNC_Dijkstra
#define FUNC_Dijkstra

#include "utils.h"

#include "FibHeap.cpp"
#include "BellmanFord.cpp"

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
#endif

#ifdef MAIN_Dijkstra
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5); 
	const size_t e = get_argv(argc, argv, 2, 10); 
	const bool dir = 1; 
	const int weight_lower = get_argv<int>(argc, argv, 3, 0); 
	const int weight_upper = get_argv<int>(argc, argv, 4, e); 
	GraphAdjList<size_t> G(dir); 
	random_graph(G, v, e); 
	umap<Edge<size_t>, int, EdgeHash<size_t>> w; 
	random_weight(G, w, weight_lower, weight_upper); 
	umap<size_t, RelaxInfo<size_t, int>> ans; 
	Dijkstra(G, w, *G.V.begin(), ans); 
	auto f1 = [ans](size_t v) mutable {
		std::cout << " [label=\"" << v << " (" << ans[v] << ")\"]"; 
		return true; 
	}; 
	auto f2 = [w, ans](Edge<size_t> e) mutable {
		std::cout << " [label=\"" << w[e] << "\""; 
		if (ans[e.d].pi == e.s)
			std::cout << " style=bold"; 
		std::cout << "]"; 
	}; 
	graphviz(G, f1, f2); 
	return 0; 
}
#endif

