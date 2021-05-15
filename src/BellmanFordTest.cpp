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

#include "BellmanFord.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(size_t v, size_t e, int weight_lower) {
	const bool dir = 1;
	const int weight_upper = e;
	GraphAdjList<size_t> G(dir);
	random_graph(G, v, e);
	umap<Edge<size_t>, int, EdgeHash<size_t>> w;
	random_weight(G, w, weight_lower, weight_upper);
	umap<size_t, RelaxInfo<size_t, int>> ans;
	bool valid = BellmanFord(G, w, *G.V.begin(), ans);
	std::cout << std::boolalpha << valid << std::endl;
	auto f1 = [ans](size_t v) mutable {
		std::cout << " [label=\"" << v << " (" << ans[v] << ")\"]";
		return true;
	};
	auto f2 = [w, ans](Edge<size_t> e) mutable {
		std::cout << " [label=\"" << w[e] << "\"";
		if (!ans[e.d].pi.nil && ans[e.d].pi == e.s)
			std::cout << " style=bold";
		std::cout << "]";
	};
	graphviz(G, f1, f2);
	if (valid) {
		for (auto i = G.V.begin(); i != G.V.end(); i++) {
			if (i == G.V.begin()) {
				assert(ans[*i].d == 0);
				assert(ans[*i].pi.nil);
			} else if (!ans[*i].pi.nil) {
				size_t j = ans[*i].pi.val;
				assert(ans[*i].d - ans[j].d == w[Edge<size_t>(j, *i, dir)]);
			}
		}
		for (auto i = G.all_edges(); !i.end(); i++) {
			if (!ans[i.s()].d.inf) {
				assert(!ans[i.d()].d.inf);
				assert(ans[i.d()].d.val - ans[i.s()].d.val <= w[*i]);
			}
		}
	} else {
		assert(weight_lower < 0);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<size_t> m = {5, 10, 23, 49, 100};
	for (std::vector<size_t>::iterator v = m.begin(); v < m.end(); v++)
		for (std::vector<size_t>::iterator e = m.begin(); e < m.end(); e++)
			for (int n = 0; n < 5; n++) {
				test(*v, *e, (0 - *e) / 4);
				test(*v, *e, 0);
			}
	return 0;
}
