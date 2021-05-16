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

#include <cassert>
#include <iostream>

#include "SquareMatrixMultiply.hpp"
#include "graph_utils.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

template <typename GT>
void graph_test(const typename GT::vertex_type v, const std::size_t e) {
	using T = typename GT::vertex_type;
	for (std::size_t dir = 0; dir <= 1; dir++) {
		GT G(dir);
		random_graph(G, v, e);
		for (typename GT::iterator i = G.all_edges(); !i.end(); i++)
			std::cout << *i << std::endl;
		std::cout << std::endl;
		for (uset<T>::iterator i = G.V.begin(); i != G.V.end(); i++) {
			std::cout << *i << std::endl;
			for (typename GT::iterator j = G.edges_from(*i); !j.end(); j++)
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
	for (std::size_t dir = 0; dir <= 1; dir++) {
		// Constant test for iterators
		GT G(dir);
		G.add_edge(0, 1);
		G.add_edge(1, 2);
		G.add_edge(1, 0);
		G.add_edge(3, 4);
		G.add_edge(4, 4);
		{
			uset<int> expected = {1, 102, 100, 304, 404};
			if (!dir)
				expected.erase(100);
			for (typename GT::iterator i = G.all_edges(); !i.end(); i++) {
				int a = i.s() * 100 + i.d();
				assert(expected.find(a) != expected.end());
				expected.erase(a);
			}
			assert(expected.size() == 0);
		}
		{
			uset<int> expected = {100, 102};
			for (typename GT::iterator i = G.edges_from(1); !i.end(); i++) {
				int a = i.s() * 100 + i.d();
				assert(expected.find(a) != expected.end());
				expected.erase(a);
			}
			assert(expected.size() == 0);
		}
		{
			uset<int> expected = {};
			if (!dir)
				expected.insert(201);
			for (typename GT::iterator i = G.edges_from(2); !i.end(); i++) {
				int a = i.s() * 100 + i.d();
				assert(expected.find(a) != expected.end());
				expected.erase(a);
			}
			assert(expected.size() == 0);
		}
		{
			uset<int> expected = {304};
			for (typename GT::iterator i = G.edges_from(3); !i.end(); i++) {
				int a = i.s() * 100 + i.d();
				assert(expected.find(a) != expected.end());
				expected.erase(a);
			}
			assert(expected.size() == 0);
		}
		{
			uset<int> expected = {404};
			if (!dir)
				expected.insert(403);
			for (typename GT::iterator i = G.edges_from(4); !i.end(); i++) {
				int a = i.s() * 100 + i.d();
				assert(expected.find(a) != expected.end());
				expected.erase(a);
			}
			assert(expected.size() == 0);
		}
		{
			uset<int> expected = {};
			for (typename GT::iterator i = G.edges_from(5); !i.end(); i++) {
				int a = i.s() * 100 + i.d();
				assert(expected.find(a) != expected.end());
				expected.erase(a);
			}
			assert(expected.size() == 0);
		}
	}
}

template <typename T, typename WT>
void graph_weighted_test(const T v, const std::size_t e) {
	for (std::size_t dir = 0; dir <= 1; dir++) {
		WeightedAdjMatrix<T, WT> G(dir);
		G.random_graph(v, e, 1 - e, e);
		graphviz(G);
		std::cout << std::endl;
		Matrix<Weight<WT>> M(v, v);
		G.to_matrix(M);
		std::cout << M;
		std::cout << std::endl;
	}
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	const std::size_t v = 5;
	const std::size_t e = 10;
	std::cout << "GraphAdjList<size_t>" << std::endl;
	graph_test<GraphAdjList<std::size_t>>(v, e);
	std::cout << "GraphAdjMatrix<size_t>" << std::endl;
	graph_test<GraphAdjMatrix<std::size_t>>(v, e);
	std::cout << "WeightedAdjMatrix<size_t, int>" << std::endl;
	graph_weighted_test<std::size_t, int>(v, e);
	std::cout << "GraphAdjList<int>" << std::endl;
	graph_test<GraphAdjList<int>>(v, e);
	std::cout << "GraphAdjMatrix<int>" << std::endl;
	graph_test<GraphAdjMatrix<int>>(v, e);
	std::cout << "WeightedAdjMatrix<int, long long int>" << std::endl;
	graph_weighted_test<int, long long int>(v, e);
	return 0;
}
