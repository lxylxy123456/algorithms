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

#include "AllPairsShortestPaths.hpp"

#include <iostream>

#include "Graph.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t v = get_argv(argc, argv, 1, 5);
	const std::size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = 1;
	const int weight_lower = get_argv<int>(argc, argv, 3, 0);
	const int weight_upper = get_argv<int>(argc, argv, 4, e);
	WeightedAdjMatrix<std::size_t, int> G(dir);
	G.random_graph(v, e, weight_lower, weight_upper);
	G.graphviz();
	std::cout << std::endl;
	Matrix<Weight<int>> W(v, v);
	G.to_matrix(W);
	Matrix<Weight<int>> ans1 = SlowAllPairsShortestPaths(W);
	std::cout << ans1 << std::endl;
	Matrix<Weight<int>> ans2 = FasterAllPairsShortestPaths(W);
	std::cout << ans2 << std::endl;
	std::cout << std::boolalpha << (ans1 == ans2) << std::endl;
	return 0;
}
