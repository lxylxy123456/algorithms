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

#ifndef ALGORITHMS_JOHNSON
#define ALGORITHMS_JOHNSON

#include <cassert>
#include <stdexcept>
#include <type_traits>

#include "Dijkstra.hpp"
#include "SquareMatrixMultiply.hpp"

namespace algorithms {

template <typename GT, typename T, typename WT>
Matrix<Weight<WT>> Johnson(GT& G, umap_WT& w) {
	static_assert(std::is_same<T, size_t>::value, "Only supports T = size_t");
	const size_t n = G.V.size();
	T s;
	GT G_prime = G;
	umap_WT w_prime = w;
	for (s = n; G.V.find(s) != G.V.end(); s++);
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		G_prime.add_edge(s, *i);
		w_prime[Edge<T>(s, *i, G.dir)] = 0;
	}
	umap<T, RelaxInfo<T, WT>> BF_ans;
	if (!BellmanFord(G_prime, w_prime, s, BF_ans))
		throw std::invalid_argument("negative-weight cycle");
	umap<T, WT> h;
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		const T& v = *i;
		assert(!BF_ans[v].d.inf);
		h[v] = BF_ans[v].d.val;
	}
	umap_WT w_hat;
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

}

#endif
