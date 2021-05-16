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
#include <unordered_map>
#include <unordered_set>

#include "SquareMatrixMultiply.hpp"

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
		/*
		// TODO: create a GraphIterator class outside
		template <typename I>
		class iterator {
			public:
				iterator(I itr): itr(itr) {}
				void operator++(int) { itr++; }
				Edge<T> operator*() { return *itr; }
				T s() { return itr.s(); }
				T d() { return itr.d(); }
				I itr;
		};
		*/
		bool dir;
		uset<T> V;
};

template <typename T>
class GraphAdjList: public Graph<T> {
	public:
		class iterator {
			public:
				iterator(umap<T, uset<T>>::iterator mbegin,
							umap<T, uset<T>>::iterator mend, bool direction,
							bool rm_reverse):
							dir(direction), rm_reverse(rm_reverse),
							mbegin(mbegin), mend(mend) {
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
						while (sbegin == send ||
								(!dir && rm_reverse && s() > d())) {
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
				const bool dir, rm_reverse;
				umap<T, uset<T>>::iterator mbegin, mend;
				uset<T>::iterator sbegin, send;
		};
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
		typename GraphAdjList<T>::iterator all_edges() {
			return typename GraphAdjList<T>::iterator(E.begin(), E.end(),
														this->dir, true);
		}
		typename GraphAdjList<T>::iterator edges_from(T s) {
			umap<T, uset<T>>::iterator i = E.find(s), j = i;
			if (i != E.end())
				j++;
			return typename GraphAdjList<T>::iterator(i, j, this->dir, false);
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
		class iterator {
			public:
				iterator(umap<T, umap<T, bool>>::iterator mbegin,
							umap<T, umap<T, bool>>::iterator mend,
							bool direction, bool rm_reverse):
							dir(direction), rm_reverse(rm_reverse),
							mbegin(mbegin), mend(mend) {
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
						while (sbegin == send || !sbegin->second ||
								(!dir && rm_reverse && s() > d())) {
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
				const bool dir, rm_reverse;
				umap<T, umap<T, bool>>::iterator mbegin, mend;
				umap<T, bool>::iterator sbegin, send;
		};
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
		typename GraphAdjMatrix<T>::iterator all_edges() {
			return typename GraphAdjMatrix<T>::iterator(E.begin(), E.end(),
														this->dir, true);
		}
		typename GraphAdjMatrix<T>::iterator edges_from(T s) {
			umap<T, umap<T, bool>>::iterator i = E.find(s), j = i;
			if (i != E.end())
				j++;
			return typename GraphAdjMatrix<T>::iterator(i, j, this->dir, false);
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
		typedef T vertex_type;
		bool dir;
		uset<T> V;
		umap<T, umap<T, Weight<WT>>> E;
};

template <typename GT>
class Bipartite: public GT {
	public:
		using T = typename GT::vertex_type;
		Bipartite(bool direction): GT(direction) {}
		uset<T> L, R;
};

}

#endif
