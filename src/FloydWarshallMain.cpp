//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#include "FloydWarshall.hpp"

#include <iostream>
#include <vector>

#include "Graph.hpp"
#include "graph_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5);
	const size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = 1;
	const int weight_lower = get_argv<int>(argc, argv, 3, 0);
	const int weight_upper = get_argv<int>(argc, argv, 4, e);
	WeightedAdjMatrix<size_t, int> G(dir);
	random_weighted_adj_matrix(G, v, e, weight_lower, weight_upper);
	graphviz(G);
	std::cout << std::endl;
	Matrix<Weight<int>> W(v, v);
	G.to_matrix(W);
	auto ans = FloydWarshall(W);
	Matrix<Weight<int>> D = ans.first;
	Matrix<T_ptr<size_t>> PI = ans.second;
	std::cout << D << std::endl;
	std::cout << PI << std::endl;
	for (size_t i = 0; i < v; i++)
		for (size_t j = 0; j < v; j++)
			if (i != j) {
				std::cout << i << " ~> " << j << ": ";
				std::vector<size_t> ans;
				PrintAllPairsShortestPath(PI, i, j, ans);
				if (ans.size())
					output_integers(ans);
				else
					std::cout << "no path from " << i << " to " << j
							 << " exists" << std::endl;
			}
	return 0;
}
