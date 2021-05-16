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

#include "DisjointSet.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "FloydWarshall.hpp"
#include "graph_utils.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(size_t v, size_t e, size_t n) {
	std::vector<size_t> c, d;
	random_integers<size_t>(c, 0, v - 1, n);
	random_integers<size_t>(d, 0, v - 1, n);
	GraphAdjList<size_t> G(false);
	random_graph(G, v, e);
	graphviz(G);
	ConnectedComponents<size_t> CC(G);
	Matrix<Weight<int>> W(v, v, Weight<int>());
	for (auto i = G.all_edges(); !i.end(); i++) {
		W[(*i).s][(*i).d] = 0;
		W[(*i).d][(*i).s] = 0;
	}
	auto ans = FloydWarshall(W);
	for (size_t i = 0; i < n; i++) {
		std::cout << c[i] << "\t" << d[i] << "\tconnected = " << std::boolalpha;
		std::cout << CC.SameComponent(c[i], d[i]) << std::endl;
		bool actual = CC.SameComponent(c[i], d[i]);
		bool expected = (ans.first[c[i]][d[i]] == 0 || c[i] == d[i]);
		assert(actual == expected);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<size_t> ns = {200, 400, 1000};
	std::vector<size_t> m = {5, 10, 23, 49, 100};
	for (std::vector<size_t>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<size_t>::iterator v = m.begin(); v < m.end(); v++)
			for (std::vector<size_t>::iterator e = m.begin(); e < m.end(); e++)
					test(*v, *e, *n);
	return 0;
}
