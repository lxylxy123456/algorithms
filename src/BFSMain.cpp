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

#include "BFS.hpp"

#include <iostream>
#include <vector>

#include "Graph.hpp"
#include "Queue.hpp"
#include "graph_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t v = get_argv(argc, argv, 1, 5);
	const std::size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = get_argv(argc, argv, 3, 0);
	GraphAdjList<std::size_t> G(dir);
	random_graph(G, v, e);
	umap<std::size_t, BFSInfo<std::size_t>> inf;
	std::size_t s = 0;
	BFS(G, s, inf);
	auto f1 = [inf](std::size_t v) mutable {
		BFSInfo<std::size_t>& i = inf[v];
		std::cout << " [";
		switch (i.color) {
			case bfs_white:
				break;
			case bfs_black:
				std::cout << "color=black style=filled fontcolor=white ";
				break;
			case bfs_gray:
				std::cout << "color=gray style=filled ";
				break;
		}
		std::cout << "label=\"" << v << "\\n";
		if (i.d == 0 || i.d.inf)
			std::cout << "d = " << i.d;
		else
			std::cout << "d = " << i.d << "; pi = " << i.pi;
		std::cout << "\"]";
		return true;
	};
	auto f2 = [](Edge<std::size_t> e) {};
	graphviz(G, f1, f2);
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		std::vector<std::size_t> ans;
		PrintPath(s, *i, inf, ans);
		std::cout << *i << '\t';
		if (ans.size())
			output_integers(ans);
		else
			std::cout << "no path from " << s << " exists" << std::endl;
	}
	return 0;
}
