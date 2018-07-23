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
#define MAIN_Johnson
#endif

#ifndef FUNC_Johnson
#define FUNC_Johnson

#include "utils.h"

#include "SquareMatrixMultiply.cpp"
#include "Dijkstra.cpp"

template <typename GT, typename T, typename WT>
Matrix<Weight<WT>> Johnson(GT& G, umap<Edge<T>, WT, EdgeHash<size_t>>& w) {
	static_assert(std::is_same<T, size_t>::value); 
	const size_t n = G.V.size(); 
	T s; 
	GT G_prime = G; 
	umap<Edge<T>, WT, EdgeHash<size_t>> w_prime = w; 
	for (s = n; G.V.find(s) != G.V.end(); s++); 
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		G_prime.add_edge(s, *i); 
		w_prime[Edge<T>(s, *i, G.dir)] = 0; 
	}
	umap<T, RelaxInfo<T, WT>> BF_ans; 
	assert(BellmanFord(G_prime, w_prime, s, BF_ans)); 
	umap<T, WT> h; 
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		const T& v = *i; 
		assert(!BF_ans[v].d.inf); 
		h[v] = BF_ans[v].d.val; 
	}
	umap<Edge<T>, WT, EdgeHash<size_t>> w_hat; 
	for (auto i = G.all_edges(); !i.end(); i++)
		w_hat[*i] = w[*i] + h[i.s()] - h[i.d()]; 
	Matrix<Weight<WT>> D(n, n, WT()); 
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		const T& u = *i; 
		umap<T, RelaxInfo<T, WT>> D_ans; 
		Dijkstra(G, w_hat, u, D_ans); 
		for (auto j = G.V.begin(); j != G.V.end(); j++) {
			const T& v = *j; 
			D[u][v] = D_ans[v].d + h[v] - h[u]; 
		}
	}
	return D; 
}
#endif

#ifdef MAIN_Johnson
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5); 
	const size_t e = get_argv(argc, argv, 2, 10); 
	const bool dir = get_argv<int>(argc, argv, 3, 1); 
	const int weight_lower = get_argv<int>(argc, argv, 3, (0-e) / 4); 
	const int weight_upper = get_argv<int>(argc, argv, 4, e); 
	GraphAdjList<size_t> G(dir); 
	random_graph(G, v, e); 
	umap<Edge<size_t>, int, EdgeHash<size_t>> w; 
	random_weight(G, w, weight_lower, weight_upper); 
	Matrix<Weight<int>> ans = Johnson(G, w); 
	auto f1 = [](size_t v) { return false; }; 
	auto f2 = [w](Edge<size_t> e) mutable {
		std::cout << " [label=\"" << w[e] << "\"]"; 
	}; 
	graphviz(G, f1, f2); 
	std::cout << ans << std::endl; 
	return 0; 
}
#endif

