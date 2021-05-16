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

#include "MaximumBipartiteMatching.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "graph_utils.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t vl, std::size_t vr, std::size_t e) {
	const bool dir = false;
	Bipartite<GraphAdjList<std::size_t>> G(dir);
	random_bipartite(G, vl, vr, e);
	uset<Edge<std::size_t>, EdgeHash<std::size_t>> ans;
	MaximumBipartiteMatching(G, ans);
	auto f1 = [](std::size_t v) { return false; };
	auto f2 = [ans](Edge<std::size_t> e) mutable {
		if (ans.find(e) != ans.end())
			std::cout << " [style=bold]";
	};
	graphviz(G, f1, f2);
	uset<std::size_t> used;
	for (auto i = G.all_edges(); !i.end(); i++) {
		std::size_t l = i.s(), r = i.d();
		if (G.L.find(l) == G.L.end())
			std::swap(l, r);
		assert(G.L.find(l) != G.L.end() && G.R.find(r) != G.R.end());
		if (ans.find(*i) != ans.end()) {
			assert(used.find(i.s()) == used.end());
			assert(used.find(i.d()) == used.end());
			used.insert(i.s());
			used.insert(i.d());
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<std::size_t> m = {5, 10, 23, 49, 100};
	for (std::vector<std::size_t>::iterator vl = m.begin(); vl < m.end(); vl++)
		for (std::vector<std::size_t>::iterator vr = m.begin(); vr < m.end();
			vr++)
			for (std::vector<std::size_t>::iterator e = m.begin(); e < m.end();
				e++)
				for (int n = 0; n < 5; n++)
					test(*vl, *vr, *e);
	return 0;
}
