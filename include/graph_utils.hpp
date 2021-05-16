//
//  algorithm - some algorithms in "Introduction to Algorithms", third edition
//  Copyright (C) 2020  lxylxy123456
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

#ifndef ALGORITHMS_GRAPH_UTILS
#define ALGORITHMS_GRAPH_UTILS

#include <iostream>
#include <random>
#include <vector>

#include "Graph.hpp"
#include "random_integers.hpp"

namespace algorithms {

template <typename T, typename F1, typename F2>
void graphviz(T& G, F1 f1, F2 f2) {
	// TODO: constrain to Graph<T>
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
void graphviz(GraphAdjList<T>& G) {
	// TODO: constrain to Graph; combine with below
	auto f1 = [](T v) { return false; };
	auto f2 = [](Edge<T>) {};
	graphviz(G, f1, f2);
}

template <typename T>
void graphviz(GraphAdjMatrix<T>& G) {
	// TODO: constrain to Graph; combine with above
	auto f1 = [](T v) { return false; };
	auto f2 = [](Edge<T>) {};
	graphviz(G, f1, f2);
}

template <typename T, typename WT, typename F1, typename F2>
void graphviz(WeightedAdjMatrix<T, WT> G, F1 f1, F2 f2) {
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
	for (auto i = G.E.begin(); i != G.E.end(); i++) {
		for (auto j = i->second.begin(); j != i->second.end(); j++) {
			if (i->first != j->first && !j->second.inf &&
				(G.dir || i->first < j->first)) {
				Edge<T> e(i->first, j->first, G.dir);
				std::cout << '\t' << e;
				std::cout << " [label=\"" << j->second << "\"";
				f2(e, j->second);
				std::cout << "]; " << std::endl;
			}
		}
	}
	std::cout << "}" << std::endl;
}

template <typename T, typename WT>
void graphviz(WeightedAdjMatrix<T, WT> G) {
	auto f1 = [](T v) { return false; };
	auto f2 = [](Edge<T> e, Weight<WT> w) {};
	graphviz(G, f1, f2);
}

template <typename GT, typename F1, typename F2>
void graphviz(Bipartite<GT> G, F1 f1, F2 f2) {
	if (G.dir)
		std::cout << "digraph G {" << std::endl;
	else
		std::cout << "graph G {" << std::endl;
	std::cout << '\t';
	std::cout << "subgraph clusterL {\n\t";
	bool newline = true;
	for (auto i = G.L.begin(); i != G.L.end(); i++) {
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
	for (auto i = G.R.begin(); i != G.R.end(); i++) {
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
	for (auto i = G.all_edges(); !i.end(); i++) {
		std::cout << '\t' << *i;
		f2(*i);
		std::cout << "; " << std::endl;
	}
	std::cout << "}" << std::endl;
}

template <typename GT>
void graphviz(Bipartite<GT> G) {
	auto f1 = [](typename GT::vertex_type v) { return false; };
	auto f2 = [](Edge<typename GT::vertex_type> e) {};
	graphviz(G, f1, f2);
}

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

template <typename T, typename WT>
void random_weighted_adj_matrix(WeightedAdjMatrix<T, WT>& G, T v, std::size_t e,
								WT l, WT h) {
	for (T i = 0; i < v; i++)
		G.add_vertex(i);
	std::vector<T> d;
	std::vector<WT> w;
	random_integers<T>(d, 0, v - 1, 2 * e);
	random_integers<WT>(w, l, h, e);
	for (std::size_t i = 0; i < e; i++)
		G.add_edge(d[2 * i], d[2 * i + 1], w[i]);
}

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

}

#endif

