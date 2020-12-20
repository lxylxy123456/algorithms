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

#include "Dijkstra.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "BellmanFord.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(size_t v, size_t e) {
	const bool dir = 1;
	const int weight_lower = 0;
	const int weight_upper = e;
	GraphAdjList<size_t> G(dir);
	random_graph(G, v, e);
	umap<Edge<size_t>, int, EdgeHash<size_t>> w;
	random_weight(G, w, weight_lower, weight_upper);
	umap<size_t, RelaxInfo<size_t, int>> ans, ans_bf;
	size_t s = *G.V.begin();
	Dijkstra(G, w, s, ans);
	assert(BellmanFord(G, w, s, ans_bf));
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		assert(ans[*i].d == ans_bf[*i].d);
	auto f1 = [ans](size_t v) mutable {
		std::cout << " [label=\"" << v << " (" << ans[v] << ")\"]";
		return true;
	};
	auto f2 = [w, ans](Edge<size_t> e) mutable {
		std::cout << " [label=\"" << w[e] << "\"";
		if (ans[e.d].pi == e.s)
			std::cout << " style=bold";
		std::cout << "]";
	};
	graphviz(G, f1, f2);
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<size_t> m = {5, 10, 23, 49, 100};
	for (std::vector<size_t>::iterator v = m.begin(); v < m.end(); v++)
		for (std::vector<size_t>::iterator e = m.begin(); e < m.end(); e++)
			for (int n = 0; n < 5; n++)
				test(*v, *e);
	return 0;
}
