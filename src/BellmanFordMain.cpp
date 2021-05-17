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

#include "BellmanFord.hpp"

#include <iostream>

#include "Graph.hpp"
#include "graph_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t v = get_argv(argc, argv, 1, 5);
	const std::size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = 1;
	const int weight_lower = get_argv<int>(argc, argv, 3, (0-e) / 4);
	const int weight_upper = get_argv<int>(argc, argv, 4, e);
	GraphAdjList<std::size_t> G(dir);
	random_graph(G, v, e);
	umap<Edge<std::size_t>, int, EdgeHash<std::size_t>> w;
	random_weight(G, w, weight_lower, weight_upper);
	umap<std::size_t, RelaxInfo<std::size_t, int>> ans;
	bool valid = BellmanFord(G, w, *G.V.begin(), ans);
	std::cout << std::boolalpha << valid << std::endl;
	auto f1 = [ans](std::size_t v) mutable {
		std::cout << " [label=\"" << v << " (" << ans[v] << ")\"]";
		return true;
	};
	auto f2 = [w, ans](Edge<std::size_t> e) mutable {
		std::cout << " [label=\"" << w[e] << "\"";
		if (!ans[e.d].pi.nil && ans[e.d].pi == e.s)
			std::cout << " style=bold";
		std::cout << "]";
	};
	graphviz(G, f1, f2);
	return 0;
}
