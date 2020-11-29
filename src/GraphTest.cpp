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

#include "Graph.hpp"

#include "utils.hpp"
#include "SquareMatrixMultiply.hpp"
#include <iostream>

using namespace algorithms;

template <typename T>
void graph_test(const size_t v, const size_t e) {
	for (size_t dir = 0; dir <= 1; dir++) {
		T G(dir);
		random_graph(G, v, e);
		for (auto i = G.all_edges(); !i.end(); i++)
			std::cout << *i << std::endl;
		std::cout << std::endl;
		for (auto i = G.V.begin(); i != G.V.end(); i++) {
			std::cout << *i << std::endl;
			for (auto j = G.edges_from(*i); !j.end(); j++)
				std::cout << '\t' << *j << std::endl;
		}
		std::cout << std::endl;
		graphviz(G);
		if (dir) {
			G.transpose();
			graphviz(G);
		}
		std::cout << std::endl;
	}
}

template <typename T, typename WT>
void graph_weighted_test(const size_t v, const size_t e) {
	for (size_t dir = 0; dir <= 1; dir++) {
		WeightedAdjMatrix<T, WT> G(dir);
		G.random_graph(v, e, 1 - e, e);
		G.graphviz();
		std::cout << std::endl;
		Matrix<Weight<int>> M(v, v);
		G.to_matrix(M);
		std::cout << M;
		std::cout << std::endl;
	}
}

int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5);
	const size_t e = get_argv(argc, argv, 2, 10);
	std::cout << "GraphAdjList" << std::endl;
	graph_test<GraphAdjList<size_t>>(v, e);
	std::cout << "GraphAdjMatrix" << std::endl;
	graph_test<GraphAdjMatrix<size_t>>(v, e);
	std::cout << "WeightedAdjMatrix" << std::endl;
	graph_weighted_test<size_t, int>(v, e);
	return 0;
}
