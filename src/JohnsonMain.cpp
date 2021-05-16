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

#include "Johnson.hpp"

#include <iostream>

#include "Dijkstra.hpp"
#include "SquareMatrixMultiply.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t v = get_argv(argc, argv, 1, 5);
	const std::size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = get_argv<int>(argc, argv, 3, 1);
	const int weight_lower = get_argv<int>(argc, argv, 4, (0-e) / 4);
	const int weight_upper = get_argv<int>(argc, argv, 5, e);
	GraphAdjList<std::size_t> G(dir);
	random_graph(G, v, e);
	umap<Edge<std::size_t>, int, EdgeHash<size_t>> w;
	random_weight(G, w, weight_lower, weight_upper);
	Matrix<Weight<int>> ans = Johnson(G, w);
	auto f1 = [](std::size_t v) { return false; };
	auto f2 = [w](Edge<std::size_t> e) mutable {
		std::cout << " [label=\"" << w[e] << "\"]";
	};
	graphviz(G, f1, f2);
	std::cout << ans << std::endl;
	return 0;
}
