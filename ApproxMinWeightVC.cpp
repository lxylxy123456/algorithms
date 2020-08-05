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
#define MAIN_ApproxMinWeightVC
#endif

#ifndef FUNC_ApproxMinWeightVC
#define FUNC_ApproxMinWeightVC

#include "utils.h"

#include "Graph.cpp"
#include "Simplex.cpp"

template <typename GT, typename T, typename WT>
void ApproxMinWeightVC(GT& G, umap<T, WT>& w, uset<T>& C) {
	umap<size_t, umap<size_t, WT>> A;
	umap<size_t, WT> b, c;
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		c[*i + 1] = -w[*i];
	const size_t n = G.V.size();
	size_t e = n + 1;
	for (auto i = G.all_edges(); !i.end(); i++, e++) {
		for (auto j = G.V.begin(); j != G.V.end(); j++)
			A[e][*j + 1] = 0;
		A[e][i.s() + 1] = -1;
		A[e][i.d() + 1] = -1;
		b[e] = -1;
	}
	for (auto i = G.V.begin(); i != G.V.end(); i++, e++) {
		for (auto j = G.V.begin(); j != G.V.end(); j++)
			A[e][*j + 1] = 0;
		A[e][*i + 1] = 1;
		b[e] = 1;
	}
	umap<size_t, WT> x = Simplex(A, b, c);
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		if (x[*i + 1] >= (WT) 1 / (WT) 2)
			C.insert(*i);
}
#endif

#ifdef MAIN_ApproxMinWeightVC
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 10);
	const size_t e = get_argv(argc, argv, 2, 20);
	const bool dir = 0;
	GraphAdjList<size_t> G(dir);
	random_graph(G, v, e);
	uset<size_t> ans;
	std::vector<int> weight;
	random_integers(weight, 1, v, v);
	using WT = double;
	umap<size_t, WT> w;
	for (size_t i = 0; i < v; i++)
		w[i] = weight[i];
	ApproxMinWeightVC(G, w, ans);
	auto f1 = [w, ans](size_t v) mutable {
		std::cout << " [label=" << w[v];
		if (ans.find(v) != ans.end())
			std::cout << " color=green";
		std::cout << "]";
		return true;
	};
	auto f2 = [](Edge<size_t>) mutable {};
	graphviz(G, f1, f2);
	return 0;
}
#endif

