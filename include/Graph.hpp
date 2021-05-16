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

#ifndef ALGORITHMS_GRAPH
#define ALGORITHMS_GRAPH

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "SquareMatrixMultiply.hpp"
#include "random_integers.hpp"

namespace algorithms {

#define uset typename std::unordered_set
#define umap typename std::unordered_map
#define umap_WT typename std::unordered_map<Edge<T>, WT, EdgeHash<T>>

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
		bool operator==(const Edge& rhs) const {
			return dir == rhs.dir && ((s == rhs.s && d == rhs.d) ||
					(d == rhs.s && s == rhs.d && !dir));
		}
		Edge<T> reverse() const {
			return Edge<T>(d, s, dir);
		}
		T s, d;
		bool dir;
};

template <typename T>
struct EdgeHash {
	std::size_t operator()(Edge<T> t) const {
		std::size_t a = std::hash<T>()(t.s);
		std::size_t b = std::hash<T>()(t.d);
		if (t.dir) {
			const std::size_t shift = sizeof(std::size_t) * 4;
			std::size_t B = b >> shift | b << shift;
			return a ^ B;
		} else
			return a ^ b ^ (a * b);
	}
};

template <typename T>
class Weight {
	public:
		typedef T value_type;
		Weight(): inf(1) {}
		Weight(T x): val(x), inf(0) {}
		Weight(T x, int i): val(x), inf(i) {}
		bool operator<(const Weight<T>& rhs) const {
			if (inf || rhs.inf)
				return inf < rhs.inf;
			else
				return val < rhs.val;
		}
		bool operator==(const Weight<T>& rhs) const {
			if (inf || rhs.inf)
				return inf == rhs.inf;
			else
				return val == rhs.val;
		}
		Weight<T> operator+(const Weight<T>& rhs) const {
			if (inf + rhs.inf > 0)
				return Weight<T>(0, 1);
			if (inf + rhs.inf < 0)
				return Weight<T>(0, -1);
			assert(!inf && !rhs.inf);
			return Weight<T>(val + rhs.val);
		}
		Weight<T> operator-(const Weight<T>& rhs) const {
			if (inf - rhs.inf > 0)
				return Weight<T>(0, 1);
			if (inf - rhs.inf < 0)
				return Weight<T>(0, -1);
			assert(!inf && !rhs.inf);
			return Weight<T>(val - rhs.val);
		}
		friend std::ostream& operator<<(std::ostream& os, const Weight<T>& rhs){
			switch (rhs.inf) {
				case -1:
					return os << "-inf";
				case 0:
					return os << rhs.val;
				case 1:
					return os << "inf";
				default:
					return os;
			}
		}
		T val;
		int inf;
};

template <typename T>
class T_ptr {
	public:
		T_ptr(): nil(true) {}
		T_ptr(T v): val(v), nil(false) {}
		bool operator==(const T_ptr<T>& rhs) const {
			return nil ? nil == rhs.nil : val == rhs.val;
		}
		friend std::ostream& operator<<(std::ostream& os, const T_ptr<T>& rhs) {
			if (rhs.nil)
				return os << "NIL";
			else
				return os << rhs.val;
		}
		T val;
		bool nil;
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
		virtual void transpose() = 0;
		virtual ~Graph() {}
		typedef T vertex_type;
		class iterator {
			public:
				virtual void operator++(int) = 0;
				virtual Edge<T> operator*() = 0;
				virtual T s() = 0;
				virtual T d() = 0;
		};
		bool dir;
		uset<T> V;
};

template <typename T>
class EdgeIteratorAL1 {
	public:
		EdgeIteratorAL1(umap<T, uset<T>>::iterator mbegin,
						umap<T, uset<T>>::iterator mend, bool direction):
						dir(direction), mbegin(mbegin), mend(mend) {
			if (mbegin != mend) {
				sbegin = mbegin->second.begin();
				send = mbegin->second.end();
			}
			next();
		}
		void operator++(int) {
			if (sbegin != send)
				sbegin++;
			next();
		}
		void next() {
			if (mbegin != mend)
				while (sbegin == send || (!dir && s() > d())) {
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
		EdgeIteratorAM1(umap<T, umap<T, bool>>::iterator mbegin,
						umap<T, umap<T, bool>>::iterator mend, bool direction):
						dir(direction), mbegin(mbegin), mend(mend) {
			if (mbegin != mend) {
				sbegin = mbegin->second.begin();
				send = mbegin->second.end();
			}
			next();
		}
		void operator++(int) {
			if (sbegin != send)
				sbegin++;
			next();
		}
		void next() {
			if (mbegin != mend)
				while (sbegin == send || !sbegin->second || (!dir && s()>d())) {
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
			return EdgeIteratorAL1<T>(E.begin(), E.end(), this->dir);
		}
		EdgeIteratorAL2<T> edges_from(T s) {
//			umap<T, uset<T>>::iterator i = E.find(s), j = i;
//			return EdgeIteratorAL1<T>(i, j, this->dir);
			return EdgeIteratorAL2<T>(s, E[s], this->dir);
		}
		virtual void transpose() {
			assert(this->dir);
			umap<T, uset<T>> old_E = E;
			E.clear();
			for (auto i = old_E.begin(); i != old_E.end(); i++)
				for (auto j = i->second.begin(); j != i->second.end(); j++)
					E[*j].insert(i->first);
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
			return EdgeIteratorAM1<T>(E.begin(), E.end(), this->dir);
		}
		EdgeIteratorAM2<T> edges_from(T s) {
//			umap<T, umap<T, bool>>::iterator i = E.find(s), j = i;
//			return EdgeIteratorAM1<T>(i, ++j, this->dir);
			return EdgeIteratorAM2<T>(s, E[s], this->dir);
		}
		virtual void transpose() {
			assert(this->dir);
			for (auto i = this->V.begin(); i != this->V.end(); i++)
				for (auto j = this->V.begin(); j != this->V.end(); j++)
					if (*i < *j)
						std::swap(E[*i][*j], E[*j][*i]);
		}
		virtual ~GraphAdjMatrix() {}
		umap<T, umap<T, bool>> E;
};

template <typename T, typename WT>
class WeightedAdjMatrix {
	public:
		WeightedAdjMatrix(bool direction): dir(direction) {}
		bool add_vertex(T u) {
			if (V.find(u) != V.end())
				return false;
			V.insert(u);
			for (auto i = V.begin(); i != V.end(); i++) {
				const T& v = *i;
				if (u == v)
					E[u][u] = Weight<WT>(0);
				else
					E[u][v] = E[v][u] = Weight<WT>();
			}
			return true;
		}
		void add_edge(T s, T d, WT w) {
			add_vertex(s);
			if (s != d) {
				add_vertex(d);
				E[s][d] = w;
				if (!dir)
					E[d][s] = w;
			}
		}
		bool is_edge(T u, T v) {
			return u != v && !E[u][v].inf;
		}
		Weight<WT> get_edge(T u, T v) {
			return E[u][v];
		}
		void random_graph(T v, std::size_t e, WT l, WT h) {
			for (T i = 0; i < v; i++)
				add_vertex(i);
			std::vector<T> d;
			std::vector<WT> w;
			random_integers<T>(d, 0, v - 1, 2 * e);
			random_integers<WT>(w, l, h, e);
			for (std::size_t i = 0; i < e; i++)
				add_edge(d[2 * i], d[2 * i + 1], w[i]);
		}
		template <typename F1, typename F2>
		void graphviz(F1 f1, F2 f2) {
			if (dir)
				std::cout << "digraph G {" << std::endl;
			else
				std::cout << "graph G {" << std::endl;
			std::cout << '\t';
			for (auto i = V.begin(); i != V.end(); i++) {
				std::cout << *i;
				if (f1(*i))
					std::cout << "; \n\t";
				else
					std::cout << "; ";
			}
			std::cout << std::endl;
			for (auto i = E.begin(); i != E.end(); i++) {
				for (auto j = i->second.begin(); j != i->second.end(); j++) {
					if (i->first != j->first && !j->second.inf &&
						(dir || i->first < j->first)) {
						Edge<T> e(i->first, j->first, dir);
						std::cout << '\t' << e;
						std::cout << " [label=\"" << j->second << "\"";
						f2(e, j->second);
						std::cout << "]; " << std::endl;
					}
				}
			}
			std::cout << "}" << std::endl;
		}
		void graphviz() {
			auto f1 = [](T v) { return false; };
			auto f2 = [](Edge<T> e, Weight<WT> w) {};
			graphviz(f1, f2);
		}
		void to_matrix(Matrix<Weight<WT>>& ans) {
			const std::size_t n = V.size();
			for (std::size_t i = 0; i < n; i++)
				assert(V.find(i) != V.end());
			ans.cols = ans.rows = n;
			ans.data.reserve(n);
			for (std::size_t i = 0; i < n; i++) {
				MatrixRow<Weight<WT>> row;
				row.reserve(n);
				for (std::size_t j = 0; j < n; j++)
					row.push_back(E[i][j]);
				ans.data.push_back(row);
			}
		}
		bool dir;
		uset<T> V;
		umap<T, umap<T, Weight<WT>>> E;
};

template <typename T>
void random_graph(Graph<T>& G, T v, std::size_t e) {
	for (T i = 0; i < v; i++)
		G.add_vertex(i);
	std::vector<T> d;
	random_integers<T>(d, 0, v - 1, 2 * e);
	for (std::size_t i = 0; i < e; i++)
		G.add_edge(d[2 * i], d[2 * i + 1]);
}

template <typename T>
void random_dag(Graph<T>& G, T v, std::size_t e) {
	for (T i = 0; i < v; i++)
		G.add_vertex(i);
	std::vector<T> d;
	random_integers<T>(d, 0, v - 1, 2 * e);
	for (std::size_t i = 0; i < e; i++) {
		T a = d[2 * i], b = d[2 * i + 1];
		if (a < b)
			G.add_edge(a, b);
		else if (a > b)
			G.add_edge(b, a);
	}
}

template <typename T>
void random_flow(Graph<T>& G, T v, std::size_t e) {
	// disables (u, v) and (v, u)
	for (T i = 0; i < v; i++)
		G.add_vertex(i);
	std::vector<T> d;
	random_integers<T>(d, 0, v - 1, 2 * e);
	for (std::size_t i = 0; i < e; i++) {
		T a = d[2 * i], b = d[2 * i + 1];
		if (a != b && !G.is_edge(a, b) && !G.is_edge(b, a))
			G.add_edge(a, b);
	}
}

template <typename WT, typename T, typename GT>
void random_weight(GT& G, umap_WT& w, WT l, WT u) {
	std::uniform_int_distribution<T> d(l, u);
	for (auto i = G.all_edges(); !i.end(); i++)
		w[*i] = random_integer(d);
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
	for (auto i = G.all_edges(); !i.end(); i++) {
		std::cout << '\t' << *i;
		f2(*i);
		std::cout << "; " << std::endl;
	}
	std::cout << "}" << std::endl;
}

template <typename T>
void graphviz(T& G) {
	auto f1 = [](typename T::vertex_type v) { return false; };
	auto f2 = [](Edge<typename T::vertex_type>) {};
	graphviz(G, f1, f2);
}

}

#endif
