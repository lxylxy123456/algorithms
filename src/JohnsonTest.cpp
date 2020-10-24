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

#include "Johnson.hpp"
#include "utils.hpp"

#include "FloydWarshall.hpp"
#include <cassert>

using namespace algorithms;

int test(size_t v, size_t e) {
	const bool dir = 1;
	const int weight_lower = (0 - e) / 4;
	const int weight_upper = e;
	GraphAdjList<size_t> G(dir);
	random_graph(G, v, e);
	umap<Edge<size_t>, int, EdgeHash<size_t>> w;
	random_weight(G, w, weight_lower, weight_upper);
	auto f1 = [](size_t v) { return false; };
	auto f2 = [w](Edge<size_t> e) mutable {
		std::cout << " [label=\"" << w[e] << "\"]";
	};
	graphviz(G, f1, f2);
	try {
		Matrix<Weight<int>> ans = Johnson(G, w);
		// FloydWarshall
		WeightedAdjMatrix<size_t, int> GG(dir);
		for (size_t i = 0; i < v; i++)
			GG.add_vertex(i);
		for (auto i = G.all_edges(); !i.end(); i++)
			GG.add_edge(i.s(), i.d(), w[*i]);
		Matrix<Weight<int>> W(v, v);
		GG.to_matrix(W);
		Matrix<Weight<int>> ans_fw = FloydWarshall(W).first;
		assert(ans == ans_fw);
	} catch (std::invalid_argument& e) {
		assert(std::string(e.what()) == "negative-weight cycle");
		std::cout << e.what() << std::endl;
		bool found = false;
		for (size_t i = 0; i < v; i++) {
			umap<size_t, RelaxInfo<size_t, int>> BF_ans;
			if (!BellmanFord(G, w, i, BF_ans)) {
				found = true;
				break;
			}
		}
		assert(found);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<size_t> m = {5, 10, 23, 49, 100};
	for (std::vector<size_t>::iterator v = m.begin(); v < m.end(); v++)
		for (std::vector<size_t>::iterator e = m.begin(); e < m.end(); e++)
			for (int n = 0; n < 5; n++)
				test(*v, *e);
	return 0;
}
