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

#include "MST.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "DisjointSet.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t v, size_t e) {
	const bool dir = 0;
	GraphAdjList<std::size_t> G(dir);
	random_graph(G, v, e);
	umap<Edge<std::size_t>, size_t, EdgeHash<size_t>> w;
	random_weight(G, w, (std::size_t) 0, e - 1);
	uset<Edge<std::size_t>, EdgeHash<size_t>> A;
	MSTKruskal(G, w, A);
	umap<std::size_t, MSTPrimInfo<size_t, size_t>> ans;
	MSTPrim(G, w, *G.V.begin(), ans);
	DisjointSetForest<std::size_t> F_kruskal, F_prim, F_all;
	std::size_t span_kruskal = 0, span_prim = 0;
	graphviz(G);
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		F_kruskal.MakeSet(*i);
		F_prim.MakeSet(*i);
		F_all.MakeSet(*i);
	}
	for (auto i = G.all_edges(); !i.end(); i++) {
		bool ans_kruskal = (A.find(*i) != A.end());
		bool ans_prim = ((!ans[i.s()].pi_nil && ans[i.s()].pi == i.d()) ||
						(!ans[i.d()].pi_nil && ans[i.d()].pi == i.s()));
		if (ans_kruskal) {
			span_kruskal += w[*i];
			assert(F_kruskal.FindSet(i.s()) != F_kruskal.FindSet(i.d()));
			F_kruskal.Union(i.s(), i.d());
		}
		if (ans_prim) {
			span_prim += w[*i];
			assert(F_prim.FindSet(i.s()) != F_prim.FindSet(i.d()));
			F_prim.Union(i.s(), i.d());
		}
		F_all.Union(i.s(), i.d());
	}
	assert(span_kruskal == span_prim);
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		for (auto j = G.V.begin(); j != G.V.end(); j++) {
			assert((F_all.FindSet(*i) == F_all.FindSet(*j)) ==
					(F_kruskal.FindSet(*i) == F_kruskal.FindSet(*j)));
			assert((F_all.FindSet(*i) == F_all.FindSet(*j)) ==
					(F_prim.FindSet(*i) == F_prim.FindSet(*j)));
		}
	}
	auto f1 = [](std::size_t v) { return false; };
	auto f2 = [w, ans, A](Edge<std::size_t> e) mutable {
		std::cout << " [label=\"" << w[e] << "\"";
		if ((!ans[e.s].pi_nil && ans[e.s].pi == e.d) ||
			(!ans[e.d].pi_nil && ans[e.d].pi == e.s))
			std::cout << " style=bold";
		if (A.find(e) != A.end())
			std::cout << " color=red";
		std::cout << "]";
	};
	graphviz(G, f1, f2);
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<std::size_t> m = {5, 10, 23, 49, 100};
	for (std::vector<std::size_t>::iterator v = m.begin(); v < m.end(); v++)
		for (std::vector<std::size_t>::iterator e = m.begin(); e < m.end(); e++)
			for (int n = 0; n < 5; n++)
				test(*v, *e);
	return 0;
}
