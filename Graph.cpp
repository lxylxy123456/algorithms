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
#define MAIN_Graph
#endif

#ifndef FUNC_Graph
#define FUNC_Graph

#include <unordered_set>
#include <unordered_map>
#include <iterator>
#include "utils.h"

#define set typename std::unordered_set
#define map typename std::unordered_map

template <typename T>
class Edge {
	public:
		Edge(T ss, T dd, bool direction): s(ss), d(dd), dir(direction) {}
		friend std::ostream& operator<<(std::ostream& os, const Edge<T>& rhs) {
			if (rhs.dir)
				return os << rhs.s << " -> " << rhs.d; 
			else
				return os << rhs.s << " -- " << rhs.d; 
		}
		T s, d; 
		bool dir; 
}; 

template <typename T>
class EdgeIteratorAL1 {
	public:
		EdgeIteratorAL1(map<T, set<T>>& E, bool direction): dir(direction) {
			mbegin = E.begin(); 
			mend = E.end(); 
			sbegin = mbegin->second.begin(); 
			send = mbegin->second.end(); 
			next(); 
		}
		void operator++(int) {
			if (sbegin != send)
				sbegin++; 
			next(); 
		}
		void next() {
			if (mbegin != mend)
				while (sbegin == send || s() > d()) {
					if (sbegin == send) {
						mbegin++; 
						if (mbegin == mend)
							break; 
						sbegin = mbegin->second.begin(); 
						send = mbegin->second.end(); 
					} else
						sbegin++; 
				}
		}
		bool end() {
			return mbegin == mend; 
		}
		Edge<T> operator*() {
			return Edge<T>(mbegin->first, *sbegin, dir); 
		}
		T s() { return mbegin->first; }
		T d() { return *sbegin; }
		bool dir; 
		map<T, set<T>>::iterator mbegin, mend; 
		set<T>::iterator sbegin, send; 
}; 

template <typename T>
class EdgeIteratorAL2 {
	public:
		EdgeIteratorAL2(T ss, set<T>& E, bool direction): S(ss), dir(direction){
			sbegin = E.begin(); 
			send = E.end(); 
		}
		void operator++(int) {
			if (sbegin != send)
				sbegin++; 
		}
		bool end() {
			return sbegin == send; 
		}
		Edge<T> operator*() {
			return Edge<T>(S, *sbegin, dir); 
		}
		T s() { return S; }
		T d() { return *sbegin; }
		T S; 
		bool dir; 
		set<T>::iterator sbegin, send; 
}; 

template <typename T>
class EdgeIteratorAM1 {
	public:
		EdgeIteratorAM1(map<T, map<T, bool>>& E, bool direction) {
			dir = direction; 
			mbegin = E.begin(); 
			mend = E.end(); 
			sbegin = mbegin->second.begin(); 
			send = mbegin->second.end(); 
			next(); 
		}
		void operator++(int) {
			if (sbegin != send)
				sbegin++; 
			next(); 
		}
		void next() {
			if (mbegin != mend)
				while (sbegin == send || !sbegin->second || s() > d()) {
					if (sbegin == send) {
						mbegin++; 
						if (mbegin == mend)
							break; 
						sbegin = mbegin->second.begin(); 
						send = mbegin->second.end(); 
					} else
						sbegin++; 
				}
		}
		bool end() {
			return mbegin == mend; 
		}
		Edge<T> operator*() {
			return Edge<T>(mbegin->first, sbegin->first, dir); 
		}
		T s() { return mbegin->first; }
		T d() { return sbegin->first; }
		bool dir; 
		map<T, map<T, bool>>::iterator mbegin, mend; 
		map<T, bool>::iterator sbegin, send; 
}; 

template <typename T>
class EdgeIteratorAM2 {
	public:
		EdgeIteratorAM2(T ss, map<T, bool>& E, bool direction): S(ss) {
			dir = direction; 
			sbegin = E.begin(); 
			send = E.end(); 
			next(); 
		}
		void operator++(int) {
			if (sbegin != send)
				sbegin++; 
			next(); 
		}
		void next() {
			while (sbegin != send && !sbegin->second)
				sbegin++; 
		}
		bool end() {
			return sbegin == send; 
		}
		Edge<T> operator*() {
			return Edge<T>(S, sbegin->first, dir); 
		}
		T s() { return S; }
		T d() { return sbegin->first; }
		T S; 
		bool dir; 
		map<T, bool>::iterator sbegin, send; 
}; 

template <typename T>
class Graph {
	public:
		Graph(bool directed): dir(directed), V() {}
		virtual bool add_vertex(T u) {
			if (V.find(u) != V.end())
				return false; 
			V.insert(u); 
			return true; 
		}
		virtual void add_edge(T, T) = 0; 
		virtual bool is_edge(T u, T v) = 0; 
		virtual ~Graph() {}
		bool dir; 
		set<T> V; 
}; 

template <typename T>
class GraphAdjList: public Graph<T> {
	public:
		GraphAdjList(bool directed): Graph<T>(directed) {}
		virtual void add_edge(T s, T d) {
			this->add_vertex(s); 
			this->add_vertex(d); 
			E[s].insert(d); 
			if (!this->dir && s != d)
				E[d].insert(s); 
		}
		virtual bool is_edge(T u, T v) {
			return E[u].find(v) != E[u].end(); 
		}
		EdgeIteratorAL1<T> all_edges() {
			return EdgeIteratorAL1<T>(E, this->dir); 
		}
		EdgeIteratorAL2<T> edges_from(T s) {
			return EdgeIteratorAL2<T>(s, E[s], this->dir); 
		}
		virtual ~GraphAdjList() {}
		map<T, set<T>> E; 
}; 

template <typename T>
class GraphAdjMatrix: public Graph<T> {
	public:
		GraphAdjMatrix(bool directed): Graph<T>(directed) {}
		virtual bool add_vertex(T u) {
			if (Graph<T>::add_vertex(u)) {
				for (auto i = this->V.begin(); i != this->V.end(); i++) {
					E[*i][u] = false; 
					E[u][*i] = false; 
				}
				return true; 
			}
			return false; 
		}
		virtual void add_edge(T s, T d) {
			this->add_vertex(s); 
			this->add_vertex(d); 
			E[s][d] = true; 
			if (!this->dir)
				E[d][s] = true; 
		}
		virtual bool is_edge(T u, T v) {
			return E[u][v]; 
		}
		EdgeIteratorAM1<T> all_edges() {
			return EdgeIteratorAM1<T>(E, this->dir); 
		}
		EdgeIteratorAM2<T> edges_from(T s) {
			return EdgeIteratorAM2<T>(s, E[s], this->dir); 
		}
		virtual ~GraphAdjMatrix() {}
		map<T, map<T, bool>> E; 
}; 

template <typename T>
void random_graph(Graph<T>& G, T v, T e) {
	for (T i = 0; i < v; i++)
		G.add_vertex(i); 
	std::vector<T> d; 
	random_integers<T>(d, 0, v - 1, 2 * e); 
	for (size_t i = 0; i < e; i++)
		G.add_edge(d[2 * i], d[2 * i + 1]); 
}

template <typename T>
void graphviz(T& G) {
	if (G.dir)
		std::cout << "digraph G {" << std::endl; 
	else
		std::cout << "graph G {" << std::endl; 
	std::cout << '\t'; 
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		std::cout << *i << "; "; 
	std::cout << std::endl; 
	for (auto i = G.all_edges(); !i.end(); i++)
		if (G.dir || i.s() < i.d())
			std::cout << '\t' << *i << "; " << std::endl; 
	std::cout << "}" << std::endl; 
}
#endif

#ifdef MAIN_Graph
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5); 
	const size_t e = get_argv(argc, argv, 2, 10); 
	for (size_t dir = 0; dir <= 1; dir++) {
		GraphAdjList<size_t> G(dir); 
		random_graph(G, v, e); 
		for (auto i = G.all_edges(); !i.end(); i++)
			std::cout << *i << std::endl; 
		std::cout << std::endl; 
		for (auto i = G.V.begin(); i != G.V.end(); i++) {
			std::cout << *i << std::endl; 
			for (auto j = G.edges_from(*i); !j.end(); j++)
				std::cout << '\t' << *j << std::endl; 
		}
		std::cout << std::endl; 
		graphviz(G); 
		std::cout << std::endl; 
	}
	for (size_t dir = 0; dir <= 1; dir++) {
		GraphAdjMatrix<size_t> G(dir); 
		random_graph(G, v, e); 
		for (auto i = G.all_edges(); !i.end(); i++)
			std::cout << *i << std::endl; 
		std::cout << std::endl; 
		for (auto i = G.V.begin(); i != G.V.end(); i++) {
			std::cout << *i << std::endl; 
			for (auto j = G.edges_from(*i); !j.end(); j++)
				std::cout << '\t' << *j << std::endl; 
		}
		std::cout << std::endl; 
		graphviz(G); 
		std::cout << std::endl; 
	}
	return 0; 
}
#endif

