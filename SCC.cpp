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
#define MAIN_SCC
#endif

#ifndef FUNC_SCC
#define FUNC_SCC

#include <map>
#include "utils.h"

#include "DFS.cpp"
#include "DisjointSet.cpp"

template <typename GT, typename T, typename VT>
void DFSVisit_SCC(GT& G, VT& inf, DisjointSetForest<T>& D, T u, size_t& time) {
	DFSInfo<T>& info = inf[u]; 
	info.set_color(gray, time); 
	for (auto i = G.edges_from(u); !i.end(); i++) {
		T v = i.d(); 
		DFSInfo<T>& vinfo = inf[v]; 
		if (vinfo.color == white) {
			vinfo.set_pi(u); 
			D.Union(u, v); 
			DFSVisit_SCC(G, inf, D, v, time); 
		}
	}
	info.set_color(black, time); 
}

template <typename GT, typename T>
void DFS_SCC(GT& G, std::map<size_t, T>& f_order, DisjointSetForest<T>& D) {
	umap<T, DFSInfo<T>> inf; 
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		inf[*i] = DFSInfo<T>(); 
	size_t time = 0; 
	for (auto i = f_order.rbegin(); i != f_order.rend(); i++) {
		T v = i->second; 
		if (inf[v].color == white)
			DFSVisit_SCC(G, inf, D, v, time); 
	}
}

template <typename GT, typename T>
void StronglyConnectedComponents(GT& G, DisjointSetForest<T>& D) {
	umap<T, DFSInfo<T>> inf; 
	DFS<T>(G, inf, nullptr); 
	GT G_transpose = G; 
	G_transpose.transpose(); 
	std::map<size_t, T> f_order; 
	for (auto i = inf.begin(); i != inf.end(); i++) {
		f_order[i->second.f] = i->first; 
		D.MakeSet(i->first); 
	}
	DFS_SCC(G_transpose, f_order, D); 
}
#endif

#ifdef MAIN_SCC
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5); 
	const size_t e = get_argv(argc, argv, 2, 10); 
	const bool dir = get_argv(argc, argv, 3, 1); 
	GraphAdjList<size_t> G(dir); 
	random_graph(G, v, e); 
	DisjointSetForest<size_t> ans; 
	StronglyConnectedComponents(G, ans); 
	auto f1 = [](size_t v) { return false; }; 
	auto f2 = [](Edge<size_t> e) {}; 
	graphviz(G, f1, f2); 
	// print ans
	std::map<size_t, uset<size_t>> components; 
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		components[ans.FindSet(*i)].insert(*i); 
	for (auto i = components.begin(); i != components.end(); i++)
		output_integers(i->second); 
	return 0; 
}
#endif

