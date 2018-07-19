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
#define MAIN_DisjointSet
#endif

#ifndef FUNC_DisjointSet
#define FUNC_DisjointSet

#include <map>
#include "utils.h"

#include "Graph.cpp"

const size_t NIL = -1; 

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
		ConnectedComponents(T n, GraphAdjList<T>& G) {
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
#endif

#ifdef MAIN_DisjointSet
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 10); 
	const size_t e = get_argv(argc, argv, 2, 10); 
	const size_t n = get_argv(argc, argv, 3, 10); 
	std::vector<size_t> c, d; 
	random_integers<size_t>(c, 0, v - 1, n); 
	random_integers<size_t>(d, 0, v - 1, n); 
	GraphAdjList<size_t> G(false); 
	random_graph(G, v, e); 
	graphviz(G); 
	ConnectedComponents<size_t> CC(n, G); 
	for (size_t i = 0; i < n; i++) {
		std::cout << c[i] << "\t" << d[i] << "\tconnected = " << std::boolalpha;
		std::cout << CC.SameComponent(c[i], d[i]) << std::endl; 
	}
	return 0; 
}
#endif

