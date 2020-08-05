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

#ifndef ALGORITHMS_MAXIMUMBIPARTITEMATCHING
#define ALGORITHMS_MAXIMUMBIPARTITEMATCHING

#include "utils.h"

#include "FordFulkerson.hpp"

namespace algorithms {

template <typename GT>
class Bipartite: public GT {
	public:
		using T = typename GT::vertex_type;
		Bipartite(bool direction): GT(direction) {}
		template <typename F1, typename F2>
		void graphviz(F1 f1, F2 f2) {
			if (GT::dir)
				std::cout << "digraph G {" << std::endl;
			else
				std::cout << "graph G {" << std::endl;
			std::cout << '\t';
			std::cout << "subgraph clusterL {\n\t";
			bool newline = true;
			for (auto i = L.begin(); i != L.end(); i++) {
				if (newline)
					std::cout << '\t';
				std::cout << *i;
				if (f1(*i)) {
					std::cout << "; \n\t";
					newline = true;
				} else {
					std::cout << "; ";
					newline = false;
				}
			}
			if (!newline)
				std::cout << "\n\t";
			std::cout << '}' << std::endl;
			std::cout << '\t';
			std::cout << "subgraph clusterR {\n\t";
			newline = true;
			for (auto i = R.begin(); i != R.end(); i++) {
				if (newline)
					std::cout << '\t';
				std::cout << *i;
				if (f1(*i)) {
					std::cout << "; \n\t";
					newline = true;
				} else {
					std::cout << "; ";
					newline = false;
				}
			}
			if (!newline)
				std::cout << "\n\t";
			std::cout << '}' << std::endl;
			for (auto i = GT::all_edges(); !i.end(); i++) {
				std::cout << '\t' << *i;
				f2(*i);
				std::cout << "; " << std::endl;
			}
			std::cout << "}" << std::endl;
		}
		void graphviz() {
			auto f1 = [](T v) { return false; };
			auto f2 = [](Edge<T> e) {};
			graphviz(f1, f2);
		}
		uset<T> L, R;
};

template <typename GT, typename T>
void random_bipartite(Bipartite<GT>& G, T vl, T vr, size_t e) {
	for (T i = 0; i < vl; i++) {
		G.add_vertex(i);
		G.L.insert(i);
	}
	for (T i = vl; i < vl + vr; i++) {
		G.add_vertex(i);
		G.R.insert(i);
	}
	std::vector<T> dl, dr;
	random_integers<T>(dl, 0, vl - 1, e);
	random_integers<T>(dr, vl, vl + vr - 1, e);
	for (size_t i = 0; i < e; i++)
		G.add_edge(dl[i], dr[i]);
}

template <typename GT, typename T>
void MaximumBipartiteMatching(GT& G, uset<Edge<T>, EdgeHash<T>>& ans) {
	GraphAdjList<T> GF(true);
	umap<Edge<T>, T, EdgeHash<size_t>> c, f;
	T s = G.V.size(), t = s + 1;
	assert(G.V.find(s) == G.V.end() && G.V.find(t) == G.V.end());
	for (auto i = G.L.begin(); i != G.L.end(); i++) {
		GF.add_edge(s, *i);
		c[Edge<T>(s, *i, true)] = 1;
	}
	for (auto i = G.R.begin(); i != G.R.end(); i++) {
		GF.add_edge(*i, t);
		c[Edge<T>(*i, t, true)] = 1;
	}
	for (auto i = G.all_edges(); !i.end(); i++) {
		GF.add_edge(i.s(), i.d());
		c[Edge<T>(i.s(), i.d(), true)] = 1;
	}
	FordFulkerson(GF, c, s, t, f);
	for (auto i = G.all_edges(); !i.end(); i++)
		if (f[Edge<T>(i.s(), i.d(), true)])
			ans.insert(*i);
}

}

#endif
