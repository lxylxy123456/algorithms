//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#include "FordFulkerson.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "graph_utils.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(size_t v, size_t e) {
	const bool dir = true;
	const int weight_lower = 0;
	const int weight_upper = e;
	GraphAdjList<size_t> G(dir);
	random_flow(G, v, e);
	umap<Edge<size_t>, int, EdgeHash<size_t>> c;
	random_weight(G, c, weight_lower, weight_upper);
	umap<Edge<size_t>, int, EdgeHash<size_t>> f;
	size_t s = 0, t = v - 1;
	FordFulkerson(G, c, s, t, f);
	auto f1 = [v](size_t vv) {
		if (vv == v - 1 || vv == 0)
			std::cout << " [style=bold]";
		return false;
	};
	auto f2 = [c, f](Edge<size_t> e) mutable {
		std::cout << " [label=\"" << f[e] << "/" << c[e] << "\"";
		if (f[e])
			std::cout << " style=bold";
		std::cout << "]";
	};
	graphviz(G, f1, f2);
	umap<size_t, int> flow_map;
	for (auto i = G.all_edges(); !i.end(); i++) {
		assert(0 <= f[*i] && f[*i] <= c[*i]);
		if (i.d() == s)
			assert(f[*i] == 0);
		if (i.s() == t)
			assert(f[*i] == 0);
		flow_map[i.d()] += f[*i];
		flow_map[i.s()] -= f[*i];
	}
	assert(flow_map[s] == -flow_map[t]);
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		assert(flow_map[*i] == 0 || *i == s || *i == t);
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
