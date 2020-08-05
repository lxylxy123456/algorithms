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
#define MAIN_FordFulkerson
#endif

#ifndef FUNC_FordFulkerson
#define FUNC_FordFulkerson

#include "utils.h"

#include "BFS.cpp"

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
#endif

#ifdef MAIN_FordFulkerson
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5);
	const size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = true;
	const int weight_lower = get_argv<int>(argc, argv, 3, 0);
	const int weight_upper = get_argv<int>(argc, argv, 4, e);
	GraphAdjList<size_t> G(dir);
	random_flow(G, v, e);
	umap<Edge<size_t>, int, EdgeHash<size_t>> c;
	random_weight(G, c, weight_lower, weight_upper);
	umap<Edge<size_t>, int, EdgeHash<size_t>> f;
	FordFulkerson(G, c, 0ul, v - 1ul, f);
	auto f1 = [v](size_t vv) {
		if (vv == v - 1 || vv == 0)
			std::cout << " [style=bold]";
		return false;
	};
	auto f2 = [c, f](Edge<size_t> e) mutable {
		std::cout << " [label=\"" << f[e] << "/" << c[e] << "\"";
		if (f[e])
			std::cout << " style=bold";
		std::cout << "]";
	};
	graphviz(G, f1, f2);
	return 0;
}
#endif

