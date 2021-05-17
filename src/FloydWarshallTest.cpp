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

#include "FloydWarshall.hpp"

#include <cassert>
#include <vector>

#include "BellmanFord.hpp"
#include "graph_utils.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t v, std::size_t e) {
	const bool dir = 1;
	const int weight_lower = 0;
	const int weight_upper = e;
	WeightedAdjMatrix<std::size_t, int> G(dir);
	random_weighted_adj_matrix(G, v, e, weight_lower, weight_upper);
	graphviz(G);
	Matrix<Weight<int>> W(v, v);
	G.to_matrix(W);
	auto ans = FloydWarshall(W);
	Matrix<Weight<int>> D = ans.first;
	Matrix<T_ptr<std::size_t>> PI = ans.second;
	GraphAdjList<std::size_t> GG(dir);
	umap<Edge<std::size_t>, int, EdgeHash<std::size_t>> w;
	for (std::size_t i = 0; i < v; i++) {
		GG.add_vertex(i);
		for (std::size_t j = 0; j < v; j++)
			if (i != j && !G.get_edge(i, j).inf) {
				GG.add_edge(i, j);
				w[Edge<std::size_t>(i, j, dir)] = G.get_edge(i, j).val;
			}
	}
	for (std::size_t i = 0; i < v; i++) {
		umap<std::size_t, RelaxInfo<std::size_t, int>> ans_bf;
		assert(BellmanFord(GG, w, i, ans_bf));
		for (std::size_t j = 0; j < v; j++)
			if (i != j) {
				std::vector<std::size_t> ans;
				PrintAllPairsShortestPath(PI, i, j, ans);
				if (ans.size()) {
					assert(!ans_bf[j].d.inf && D[i][j].val == ans_bf[j].d.val);
					int d = 0;
					for (std::vector<std::size_t>::iterator k = ans.begin();
						k + 1 < ans.end(); k++) {
						assert(!G.get_edge(*k, *(k + 1)).inf);
						d += G.get_edge(*k, *(k + 1)).val;
					}
					assert(d == D[i][j].val);
				} else
					assert(ans_bf[j].d.inf);
			}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<std::size_t> m = {5, 10, 23, 49};
	for (std::vector<std::size_t>::iterator v = m.begin(); v < m.end(); v++)
		for (std::vector<std::size_t>::iterator e = m.begin(); e < m.end(); e++)
			for (int n = 0; n < 5; n++)
				test(*v, *e);
	return 0;
}
