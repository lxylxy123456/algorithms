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

#include "DFS.hpp"

#include <cassert>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t v, std::size_t e, bool dir) {
	GraphAdjList<std::size_t> G(dir);
	random_graph(G, v, e);
	graphviz(G);
	umap<std::size_t, DFSInfo<std::size_t>> inf;
	umap<Edge<std::size_t>, DFSEdgeType, EdgeHash<std::size_t>> edge_inf;
	DFS(G, inf, &edge_inf);
	for (std::size_t i = 0; i < v; i++) {
		assert(inf[i].color == dfs_black);
		if (!inf[i].pi.nil) {
			std::size_t p = inf[i].pi.val;
			assert(inf[i].d > inf[p].d);
			assert(inf[i].f < inf[p].f);
		}
	}
	for (auto i = G.all_edges(); !i.end(); i++) {
		switch (edge_inf[*i]) {
			case tree:
				if (dir || inf[i.d()].pi == i.s()) {
					assert(inf[i.s()].d < inf[i.d()].d &&
							inf[i.d()].d < inf[i.d()].f &&
							inf[i.d()].f < inf[i.s()].f);
				} else {
					assert(inf[i.s()].pi == i.d());
					assert(inf[i.d()].d < inf[i.s()].d &&
							inf[i.s()].d < inf[i.s()].f &&
							inf[i.s()].f < inf[i.d()].f);
				}
				break;
			case back:
				if (dir)
					assert(inf[i.d()].d <= inf[i.s()].d &&
							inf[i.s()].d < inf[i.s()].f && 
							inf[i.s()].f <= inf[i.d()].f);
				else
					assert((inf[i.d()].d <= inf[i.s()].d &&
							inf[i.s()].d < inf[i.s()].f && 
							inf[i.s()].f <= inf[i.d()].f) ||
							(inf[i.s()].d <= inf[i.d()].d &&
							inf[i.d()].d < inf[i.d()].f && 
							inf[i.d()].f <= inf[i.s()].f));
				break;
			case forward:
				assert(dir);
				assert(inf[i.s()].d < inf[i.d()].d &&
						inf[i.d()].d < inf[i.d()].f &&
						inf[i.d()].f < inf[i.s()].f);
				break;
			case cross:
				assert(dir);
				assert(inf[i.d()].d < inf[i.d()].f &&
						inf[i.d()].f < inf[i.s()].d &&
						inf[i.s()].d < inf[i.s()].f);
				break;
			default:
				assert(0);
				break;
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<std::size_t> m = {5, 10, 23, 49, 100};
	for (std::vector<std::size_t>::iterator v = m.begin(); v < m.end(); v++)
		for (std::vector<std::size_t>::iterator e = m.begin(); e < m.end(); e++)
			for (int i = 0; i < 2; i++)
				test(*v, *e, (bool) i);
	return 0;
}
