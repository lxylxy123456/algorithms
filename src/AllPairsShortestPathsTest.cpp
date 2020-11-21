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

#include "AllPairsShortestPaths.hpp"
#include "utils.hpp"

#include "FloydWarshall.hpp"
#include <cassert>

using namespace algorithms;

int test(size_t v, size_t e) {
	const bool dir = 1;
	const int weight_lower = 0;
	const int weight_upper = e;
	WeightedAdjMatrix<size_t, int> G(dir);
	G.random_graph(v, e, weight_lower, weight_upper);
	G.graphviz();
	Matrix<Weight<int>> W(v, v);
	G.to_matrix(W);
	Matrix<Weight<int>> ans1 = SlowAllPairsShortestPaths(W);
	Matrix<Weight<int>> ans2 = FasterAllPairsShortestPaths(W);
	Matrix<Weight<int>> ans_fw = FloydWarshall(W).first;
	assert(ans1 == ans2);
	assert(ans1 == ans_fw);
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<size_t> m = {5, 10, 23, 49};
	for (std::vector<size_t>::iterator v = m.begin(); v < m.end(); v++)
		for (std::vector<size_t>::iterator e = m.begin(); e < m.end(); e++)
			for (int n = 0; n < 5; n++)
				test(*v, *e);
	return 0;
}