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

#ifndef MAIN
#define MAIN
#define MAIN_FloydWarshall
#endif

#ifndef FUNC_FloydWarshall
#define FUNC_FloydWarshall

#include "utils.h"

#include "Graph.cpp"

void PrintAllPairsShortestPath(Matrix<T_ptr<size_t>>& PI, size_t i, size_t j,
	std::vector<size_t>& ans) {
	if (i == j)
		ans.push_back(i);
	else if (!PI[i][j].nil) {
		PrintAllPairsShortestPath(PI, i, PI[i][j].val, ans);
		ans.push_back(j);
	}
}

template <typename T>
std::pair<Matrix<T>, Matrix<T_ptr<size_t>>> FloydWarshall(Matrix<T>& W) {
	const size_t n = W.rows;
	Matrix<T> D = W;
	Matrix<T_ptr<size_t>> PI(n, n, T_ptr<size_t>());
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			if (i != j && !W[i][j].inf)
				PI[i][j] = i;
	for (size_t k = 0; k < n; k++) {
		Matrix<T> D_new = D;
		Matrix<T_ptr<size_t>> PI_new = PI;
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++) {
				T n = D[i][k] + D[k][j];
				if (n < D_new[i][j]) {
					D_new[i][j] = n;
					PI_new[i][j] = PI[k][j];
				}
			}
		D = D_new;
		PI = PI_new;
	}
	return std::pair<Matrix<T>, Matrix<T_ptr<size_t>>>(D, PI);
}
#endif

#ifdef MAIN_FloydWarshall
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5);
	const size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = 1;
	const int weight_lower = get_argv<int>(argc, argv, 3, 0);
	const int weight_upper = get_argv<int>(argc, argv, 4, e);
	WeightedAdjMatrix<size_t, int> G(dir);
	G.random_graph(v, e, weight_lower, weight_upper);
	G.graphviz();
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
#endif

