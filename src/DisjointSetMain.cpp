//
//  algorithm - some algorithms in "Introduction to Algorithms", third edition
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

#include "DisjointSet.hpp"

#include <iostream>
#include <vector>

#include "Graph.hpp"
#include "graph_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 10);
	const size_t e = get_argv(argc, argv, 2, 10);
	const size_t n = get_argv(argc, argv, 3, 10);
	std::vector<size_t> c, d;
	random_integers<size_t>(c, 0, v - 1, n);
	random_integers<size_t>(d, 0, v - 1, n);
	GraphAdjList<size_t> G(false);
	random_graph(G, v, e);
	graphviz(G);
	ConnectedComponents<size_t> CC(G);
	for (size_t i = 0; i < n; i++) {
		std::cout << c[i] << "\t" << d[i] << "\tconnected = " << std::boolalpha;
		std::cout << CC.SameComponent(c[i], d[i]) << std::endl;
	}
	return 0;
}
