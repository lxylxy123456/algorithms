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

#include "MST.hpp"

#include <iostream>

#include "DisjointSet.hpp"
#include "FibHeap.hpp"
#include "Graph.hpp"
#include "graph_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5);
	const size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = 0;
	const size_t algorithm = get_argv(argc, argv, 3, 0);
	GraphAdjList<size_t> G(dir);
	random_graph(G, v, e);
	umap<Edge<size_t>, size_t, EdgeHash<size_t>> w;
	random_weight(G, w, (size_t) 0, e - 1);
	if (algorithm == 0) {
		uset<Edge<size_t>, EdgeHash<size_t>> A;
		MSTKruskal(G, w, A);
		auto f1 = [](size_t v) { return false; };
		auto f2 = [w, A](Edge<size_t> e) mutable {
			std::cout << " [label=\"" << w[e] << "\"";
			if (A.find(e) != A.end())
				std::cout << " style=bold";
			std::cout << "]";
		};
		graphviz(G, f1, f2);
	} else {
		umap<size_t, MSTPrimInfo<size_t, size_t>> ans;
		MSTPrim(G, w, *G.V.begin(), ans);
		auto f1 = [](size_t v) { return false; };
		auto f2 = [w, ans](Edge<size_t> e) mutable {
			std::cout << " [label=\"" << w[e] << "\"";
			if ((!ans[e.s].pi_nil && ans[e.s].pi == e.d) ||
				(!ans[e.d].pi_nil && ans[e.d].pi == e.s))
				std::cout << " style=bold";
			std::cout << "]";
		};
		graphviz(G, f1, f2);
	}
	return 0;
}
