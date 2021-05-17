//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#include "DFS.hpp"

#include <iostream>

#include "Graph.hpp"
#include "graph_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t v = get_argv(argc, argv, 1, 5);
	const std::size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = get_argv(argc, argv, 3, 0);
	GraphAdjList<std::size_t> G(dir);
	random_graph(G, v, e);
	umap<std::size_t, DFSInfo<std::size_t>> inf;
	umap<Edge<std::size_t>, DFSEdgeType, EdgeHash<std::size_t>> edge_inf;
	DFS(G, inf, &edge_inf);
	auto f1 = [inf](std::size_t v) mutable {
		DFSInfo<std::size_t>& i = inf[v];
		std::cout << " [";
		switch (i.color) {
			case dfs_white:
				break;
			case dfs_black:
				std::cout << "color=black style=filled fontcolor=white ";
				break;
			case dfs_gray:
				std::cout << "color=gray style=filled ";
				break;
		}
		std::cout << "label=\"" << v << "\\n" << "d = " << i.d;
		std::cout << "; f = " << i.f << "; pi = " << i.pi << "\"]";
		return true;
	};
	auto f2 = [edge_inf](Edge<std::size_t> e) mutable {
		std::cout << " [" << "label=\"" << edge_inf[e] << "\"]";
	};
	graphviz(G, f1, f2);
	return 0;
}
