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

#include "ApproxVertexCover.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "Graph.hpp"
#include "graph_utils.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t v, std::size_t e) {
	const bool dir = 0;
	GraphAdjList<std::size_t> G(dir);
	random_graph(G, v, e);
	uset<std::size_t> ans;
	ApproxVertexCover(G, ans);
	auto f1 = [ans](std::size_t v) {
		if (ans.find(v) != ans.end())
			std::cout << " [color=green]";
		return false;
	};
	auto f2 = [](Edge<std::size_t>) mutable {};
	graphviz(G, f1, f2);
	for (auto i = G.all_edges(); !i.end(); i++)
		assert(ans.find(i.s()) != ans.end() || ans.find(i.d()) != ans.end());
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<std::size_t> m = {5, 10, 23, 49, 100};
	for (std::vector<std::size_t>::iterator v = m.begin(); v < m.end(); v++)
		for (std::vector<std::size_t>::iterator e = m.begin(); e < m.end(); e++)
			for (int n = 0; n < 5; n++)
				test(*v, *e);
	return 0;
}
