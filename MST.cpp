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
#define MAIN_MST
#endif

#ifndef FUNC_MST
#define FUNC_MST

#include <map>
#include "utils.h"

#include "Graph.cpp"
#include "DisjointSet.cpp"
#include "FibHeap.cpp"

template <typename T, typename WT>
class MSTPrimInfo {
	public:
		MSTPrimInfo(): pi_nil(true), key_inf(true), in_Q(true) {}
		MSTPrimInfo(WT k): key(k), pi_nil(true), key_inf(false), in_Q(true) {}
		void set_pi(T p) {
			pi = p; 
			pi_nil = false; 
		}
		void set_key(WT k) {
			key = k; 
			key_inf = false; 
		}
		bool operator<(const MSTPrimInfo& rhs) const {
			if (key_inf)
				return false; 
			else if (rhs.key_inf)
				return true; 
			else
				return key < rhs.key; 
		}
		T pi; 
		WT key; 
		bool pi_nil, key_inf, in_Q; 
}; 

template <typename GT, typename T, typename WT, typename AT>
void MSTKruskal(GT& G, umap<Edge<T>, WT, EdgeHash<T>>& w, AT& A) {
	A.clear(); 
	DisjointSetForest<T> DF; 
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		DF.MakeSet(*i); 
	std::multimap<WT, Edge<T>> E; 
	for (auto i = G.all_edges(); !i.end(); i++)
		E.insert(std::pair<WT, Edge<T>>(w[*i], *i)); 
	for (auto i = E.begin(); i != E.end(); i++)
		if (DF.FindSet(i->second.s) != DF.FindSet(i->second.d)) {
			A.insert(i->second); 
			DF.Union(i->second.s, i->second.d); 
		}
}

template <typename GT, typename T, typename WT, typename IT>
void MSTPrim(GT& G, umap<Edge<T>, WT, EdgeHash<T>>& w, T r, IT& ans) {
	using QT = std::pair<MSTPrimInfo<T, WT>, T>; 
	FibHeap<QT> Q; 
	umap<T, FNode<QT>*> Q_ptr; 
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		if (*i == r)
			ans[*i] = MSTPrimInfo<T, WT>(0); 
		else
			ans[*i] = MSTPrimInfo<T, WT>(); 
		Q_ptr[*i] = Q.FibHeapInsert(QT(ans[*i], *i)); 
	}
	while (Q.FibHeapMinimum()) {
		FNode<QT>* m = Q.FibHeapExtractMin(); 
		T u = m->key.second; 
		delete m; 
		ans[u].in_Q = false; 
		for (auto i = G.edges_from(u); !i.end(); i++) {
			MSTPrimInfo<T, WT>& info = ans[i.d()]; 
			if (info.in_Q && MSTPrimInfo<T, WT>(w[*i]) < info) {
				info.set_pi(u); 
				info.set_key(w[*i]); 
				Q.FibHeapDecreaseKey(Q_ptr[i.d()], QT(info, i.d())); 
			}
		}
	}
}
#endif

#ifdef MAIN_MST
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5); 
	const size_t e = get_argv(argc, argv, 2, 10); 
	const bool dir = 0; 
	const size_t algorithm = get_argv(argc, argv, 3, 0); 
	GraphAdjList<size_t> G(dir); 
	random_graph(G, v, e); 
	umap<Edge<size_t>, size_t, EdgeHash<size_t>> w; 
	random_weight(G, w, (size_t) 0, e - 1); 
	if (algorithm == 0) {
		uset<Edge<size_t>, EdgeHash<size_t>> A; 
		MSTKruskal(G, w, A); 
		auto f1 = [](size_t v) { return false; }; 
		auto f2 = [w, A](Edge<size_t> e) mutable {
			std::cout << " [label=\"" << w[e] << "\""; 
			if (A.find(e) != A.end())
				std::cout << " style=bold"; 
			std::cout << "]"; 
		}; 
		graphviz(G, f1, f2); 
	} else {
		umap<size_t, MSTPrimInfo<size_t, size_t>> ans; 
		MSTPrim(G, w, *G.V.begin(), ans); 
		auto f1 = [](size_t v) { return false; }; 
		auto f2 = [w, ans](Edge<size_t> e) mutable {
			std::cout << " [label=\"" << w[e] << "\""; 
			if ((!ans[e.s].pi_nil && ans[e.s].pi == e.d) || 
				(!ans[e.d].pi_nil && ans[e.d].pi == e.s))
				std::cout << " style=bold"; 
			std::cout << "]"; 
		}; 
		graphviz(G, f1, f2); 
	}
	return 0; 
}
#endif

