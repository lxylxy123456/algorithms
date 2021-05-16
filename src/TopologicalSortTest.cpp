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

#include "TopologicalSort.hpp"

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t v, std::size_t e) {
	GraphAdjList<std::size_t> G(true);
	random_graph(G, v, e);
	{
		umap<std::size_t, DFSInfo<std::size_t>> inf;
		umap<Edge<std::size_t>, DFSEdgeType, EdgeHash<std::size_t>> edge_inf;
		DFS(G, inf, &edge_inf);
		graphviz(G);
		for (auto i = G.all_edges(); !i.end(); i++)
			if (edge_inf[*i] == back)
				return 0;
	}
	std::cout << "TopologicalSort" << std::endl;
	umap<std::size_t, DFSInfo<std::size_t>> inf;
	std::deque<std::size_t> ans;
	TopologicalSort(G, inf, ans);
	for (auto i = G.all_edges(); !i.end(); i++) {
		std::deque<std::size_t>::iterator s = std::find(ans.begin(), ans.end(),
														i.s());
		std::deque<std::size_t>::iterator d = std::find(ans.begin(), ans.end(),
														i.d());
		assert(s < d);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<std::size_t> m = {5, 10, 23, 49, 100};
	for (std::vector<std::size_t>::iterator v = m.begin(); v < m.end(); v++)
		for (std::vector<std::size_t>::iterator e = m.begin(); e < m.end(); e++)
			for (int n = 0; n < 100; n++)
				test(*v, *e);
	return 0;
}
