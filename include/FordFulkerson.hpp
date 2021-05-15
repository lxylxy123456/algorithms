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

#ifndef ALGORITHMS_FORDFULKERSON
#define ALGORITHMS_FORDFULKERSON

#include <algorithm>
#include <vector>

#include "BFS.hpp"

namespace algorithms {

template <typename GT, typename T, typename WT>
void FordFulkerson(GT& G, umap_WT& c, T s, T t, umap_WT& f) {
	for (auto i = G.all_edges(); !i.end(); i++)
		f[*i] = 0;
	auto cf = [&G, &c, &f](T u, T v) mutable -> WT {
		if (G.is_edge(u, v)) {
			Edge<T> e = Edge<T>(u, v, G.dir);
			return c[e] - f[e];
		} else if (G.is_edge(v, u))
			return f[Edge<T>(v, u, G.dir)];
		else
			return 0;
	};
	while (true) {
		GT Gf(G.dir);
		for (auto i = G.V.begin(); i != G.V.end(); i++)
			Gf.add_vertex(*i);
		for (auto i = G.all_edges(); !i.end(); i++) {
			T u = i.s(), v = i.d();
			if (cf(u, v))
				Gf.add_edge(u, v);
			if (cf(v, u))
				Gf.add_edge(v, u);
		}
		umap<T, BFSInfo<T>> BFS_ans;
		BFS(Gf, s, BFS_ans);
		std::vector<size_t> p;
		PrintPath(s, t, BFS_ans, p);
		if (!p.size())
			break;
		WT cfp = cf(p[0], p[1]);
		for (size_t i = 2; i < p.size(); i++)
			cfp = std::min(cfp, cf(p[i - 1], p[i]));
		for (size_t i = 1; i < p.size(); i++) {
			if (G.is_edge(p[i - 1], p[i]))
				f[Edge<T>(p[i - 1], p[i], G.dir)] += cfp;
			else
				f[Edge<T>(p[i], p[i - 1], G.dir)] -= cfp;
		}
	}
}

}

#endif
