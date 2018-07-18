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
#include "utils.h"

#define uset typename std::unordered_set
#define umap typename std::unordered_map

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
		EdgeIteratorAL1(umap<T, uset<T>>& E, bool direction): dir(direction) {
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
		umap<T, uset<T>>::iterator mbegin, mend; 
		uset<T>::iterator sbegin, send; 
}; 

template <typename T>
class EdgeIteratorAL2 {
	public:
		EdgeIteratorAL2(T ss, uset<T>& E, bool direction): S(ss),dir(direction){
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
		uset<T>::iterator sbegin, send; 
}; 

template <typename T>
class EdgeIteratorAM1 {
	public:
		EdgeIteratorAM1(umap<T, umap<T, bool>>& E, bool direction) {
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
		umap<T, umap<T, bool>>::iterator mbegin, mend; 
		umap<T, bool>::iterator sbegin, send; 
}; 

template <typename T>
class EdgeIteratorAM2 {
	public:
		EdgeIteratorAM2(T ss, umap<T, bool>& E, bool direction): S(ss) {
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
		umap<T, bool>::iterator sbegin, send; 
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
		void add_edge(Edge<T> e) {
			this->add_edge(e.s, e.d); 
		}
		virtual void add_edge(T, T) = 0; 
		virtual bool is_edge(T u, T v) = 0; 
		virtual ~Graph() {}
		typedef T vertix_type; 
		bool dir; 
		uset<T> V; 
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
		umap<T, uset<T>> E; 
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
		umap<T, umap<T, bool>> E; 
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

template <typename T, typename F1, typename F2>
void graphviz(T& G, F1 f1, F2 f2) {
	if (G.dir)
		std::cout << "digraph G {" << std::endl; 
	else
		std::cout << "graph G {" << std::endl; 
	std::cout << '\t'; 
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		std::cout << *i; 
		if (f1(*i))
			std::cout << "; \n\t"; 
		else
			std::cout << "; "; 
	}
	std::cout << std::endl; 
	for (auto i = G.all_edges(); !i.end(); i++)
		if (G.dir || i.s() < i.d()) {
			std::cout << '\t' << *i; 
			f2(*i); 
			std::cout << "; " << std::endl; 
		}
	std::cout << "}" << std::endl; 
}

template <typename T>
void graphviz(T& G) {
	auto f1 = [](typename T::vertix_type v) { return false; }; 
	auto f2 = [](Edge<typename T::vertix_type>) {}; 
	graphviz(G, f1, f2); 
}
#endif

#ifdef MAIN_Graph
template <typename T>
void graph_test(const size_t v, const size_t e) {
	for (size_t dir = 0; dir <= 1; dir++) {
		T G(dir); 
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
}

int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5); 
	const size_t e = get_argv(argc, argv, 2, 10); 
	graph_test<GraphAdjList<size_t>>(v, e); 
	graph_test<GraphAdjMatrix<size_t>>(v, e); 
	return 0; 
}
#endif

