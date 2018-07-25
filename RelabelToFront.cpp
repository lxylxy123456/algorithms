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
#define MAIN_RelabelToFront
#endif

#ifndef FUNC_RelabelToFront
#define FUNC_RelabelToFront

#include <list>
#include "utils.h"

#include "Graph.cpp"

#define list_T typename std::list<T>

template <typename GT, typename T, typename WT>
WT cf(GT& G, umap_WT& c, umap_WT& f, T u, T v) {
	if (G.is_edge(u, v)) {
		Edge<T> e = Edge<T>(u, v, G.dir); 
		return c[e] - f[e]; 
	} else if (G.is_edge(v, u))
		return f[Edge<T>(v, u, G.dir)]; 
	else
		return 0; 
}; 

template <typename GT, typename T, typename WT>
void Push(GT& G, umap_WT& c, umap_WT& f, umap<T, WT>& e, T u, T v) {
	WT delta = std::min(e[u], cf(G, c, f, u, v)); 
	if (G.is_edge(u, v))
		f[Edge<T>(u, v, G.dir)] += delta; 
	else
		f[Edge<T>(v, u, G.dir)] -= delta; 
	e[u] -= delta; 
	e[v] += delta; 
}

template <typename GT, typename T, typename WT>
void Relabel(GT& G, umap_WT& c, umap_WT& f, umap<T, list_T>& N, umap<T, T>& h, 
			T u) {
	Weight<T> min_h; 
	for (auto i = N[u].begin(); i != N[u].end(); i++)
		if (cf(G, c, f, u, *i))
			min_h = std::min(min_h, Weight<T>(h[*i])); 
	assert(!min_h.inf); 
	h[u] = 1 + min_h.val; 
}

template <typename GT, typename T, typename WT>
void InitializePreflow(GT& G, umap_WT& c, umap_WT& f, umap<T, WT>& e, 
						umap<T, T>& h, T s) {
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		const T& v = *i; 
		h[v] = 0; 
		e[v] = 0; 
	}
	for (auto i = G.all_edges(); !i.end(); i++)
		f[*i] = 0; 
	h[s] = G.V.size(); 
	for (auto i = G.edges_from(s); !i.end(); i++) {
		f[*i] = c[*i]; 
		e[i.d()] = c[*i]; 
		e[s] -= c[*i]; 
	}
}

template <typename GT, typename T, typename WT>
void Discharge(GT& G, umap_WT& c, umap_WT& f, umap<T, WT>& e, 
	umap<T, list_T>& N, umap<T, T>& h, umap<T, list_T::iterator>& cur, T u) {
	while (e[u]) {
		if (cur[u] == N[u].end()) {
			Relabel(G, c, f, N, h, u); 
			cur[u] = N[u].begin(); 
		} else if (cf(G, c, f, u, *(cur[u])) && h[u] == h[*(cur[u])] + 1)
			Push(G, c, f, e, u, *(cur[u])); 
		else
			cur[u]++; 
	}
}

template <typename GT, typename T, typename WT>
void RelabelToFront(GT& G, umap_WT& c, T s, T t, umap_WT& f) {
	umap<T, WT> e; 
	umap<T, T> h; 
	umap<T, list_T> N; 
	umap<T, list_T::iterator> cur; 
	list_T L; 
	InitializePreflow(G, c, f, e, h, s); 
	for (auto i = G.all_edges(); !i.end(); i++) {
		T u = i.s(), v = i.d(); 
		if (u != s && u != t)
			N[u].push_back(v); 
		if (v != s && v != t)
			N[v].push_back(u); 
	}
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		T u = *i; 
		if (u != s && u != t) {
			cur[u] = N[u].begin(); 
			L.push_back(u); 
		}
	}
	for (auto i = L.begin(); i != L.end(); i++) {
		T u = *i; 
		T old_height = h[u]; 
		Discharge(G, c, f, e, N, h, cur, u); 
		if (h[u] > old_height) {
			L.erase(i); 
			L.push_front(u); 
			i = L.begin(); 
		}
	}
}
#endif

#ifdef MAIN_RelabelToFront
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5); 
	const size_t e = get_argv(argc, argv, 2, 10); 
	const bool dir = true; 
	const int weight_lower = get_argv<int>(argc, argv, 3, 0); 
	const int weight_upper = get_argv<int>(argc, argv, 4, e); 
	GraphAdjList<size_t> G(dir); 
	random_flow(G, v, e); 
	umap<Edge<size_t>, int, EdgeHash<size_t>> c; 
	random_weight(G, c, weight_lower, weight_upper); 
	umap<Edge<size_t>, int, EdgeHash<size_t>> f; 
	for (auto i = G.all_edges(); !i.end(); i++)
		if (i.s() == i.d())
			c[*i] = 0; 
	RelabelToFront(G, c, 0ul, v - 1ul, f); 
	auto f1 = [v](size_t vv) {
		if (vv == v - 1 || vv == 0)
			std::cout << " [style=bold]"; 
		return false; 
	}; 
	auto f2 = [c, f](Edge<size_t> e) mutable {
		std::cout << " [label=\"" << f[e] << "/" << c[e] << "\""; 
		if (f[e])
			std::cout << " style=bold"; 
		std::cout << "]"; 
	}; 
	graphviz(G, f1, f2); 
	return 0; 
}
#endif

