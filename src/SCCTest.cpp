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

#include "SCC.hpp"
#include "utils.hpp"

#include "FloydWarshall.hpp"
#include <cassert>
#include <vector>

using namespace algorithms;

int test(size_t v, size_t e) {
	GraphAdjList<size_t> G(true);
	random_graph(G, v, e);
	graphviz(G);
	DisjointSetForest<size_t> ans;
	StronglyConnectedComponents(G, ans);
	Matrix<Weight<int>> W(v, v, Weight<int>());
	for (auto i = G.all_edges(); !i.end(); i++)
		W[(*i).s][(*i).d] = 0;
	auto fw = FloydWarshall(W);
	for (size_t i = 0; i < v; i++)
		for (size_t j = 0; j < v; j++)
			if (i != j) {
				bool actual = ans.FindSet(i) == ans.FindSet(j);
				bool expected = fw.first[i][j] == 0 && fw.first[j][i] == 0;
				assert(actual == expected);
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
