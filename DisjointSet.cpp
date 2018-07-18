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

#include "utils.h"

#include "Graph.cpp"

const size_t NIL = -1; 

class DisjointSetForest {
	public:
		DisjointSetForest(size_t n): p(n, NIL), rank(n, 0) {}
		void MakeSet(size_t x) {
			p[x] = x; 
			rank[x] = 0; 
		}
		void Link(size_t x, size_t y) {
			if (rank[x] > rank[y])
				p[y] = x; 
			else {
				p[x] = y; 
				if (rank[x] == rank[y])
					rank[y]++; 
			}
		}
		size_t FindSet(size_t x) {
			if (p[x] == NIL)
				return x; 
			if (x != p[x])
				p[x] = FindSet(p[x]); 
			return p[x]; 
		}
		void Union(size_t x, size_t y) {
			Link(FindSet(x), FindSet(y)); 
		}
		std::vector<size_t> p, rank; 
}; 

class ConnectedComponents {
	public:
		ConnectedComponents(size_t n, GraphAdjList<size_t>& G): F(n) {
			for (auto i = G.V.begin(); i != G.V.end(); i++)
				F.MakeSet(*i); 
			for (auto i = G.all_edges(); !i.end(); i++)
				if (F.FindSet(i.s()) != F.FindSet(i.d()))
					F.Union(i.s(), i.d()); 
		}
		bool SameComponent(size_t u, size_t v) {
			return F.FindSet(u) == F.FindSet(v); 
		}
		DisjointSetForest F; 
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
	ConnectedComponents CC(n, G); 
	for (size_t i = 0; i < n; i++) {
		std::cout << c[i] << "\t" << d[i] << "\tconnected = " << std::boolalpha;
		std::cout << CC.SameComponent(c[i], d[i]) << std::endl; 
	}
	return 0; 
}
#endif

