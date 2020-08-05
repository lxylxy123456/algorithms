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
#define MAIN_ApproxVertexCover
#endif

#ifndef FUNC_ApproxVertexCover
#define FUNC_ApproxVertexCover

#include "utils.h"

#include "Graph.cpp"

template <typename GT, typename T>
void ApproxVertexCover(GT& G, uset<T>& C) {
	uset<Edge<T>, EdgeHash<T>> E;
	for (auto i = G.all_edges(); !i.end(); i++)
		E.insert(*i);
	while (E.begin() != E.end()) {
		Edge<T> e = *E.begin();
		const T &u = e.s, &v = e.d;
		C.insert(u);
		C.insert(v);
		for (auto i = G.edges_from(u); !i.end(); i++)
			E.erase(*i);
		for (auto i = G.edges_from(v); !i.end(); i++)
			E.erase(*i);
	}
}
#endif

#ifdef MAIN_ApproxVertexCover
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 10);
	const size_t e = get_argv(argc, argv, 2, 20);
	const bool dir = 0;
	GraphAdjList<size_t> G(dir);
	random_graph(G, v, e);
	uset<size_t> ans;
	ApproxVertexCover(G, ans);
	auto f1 = [ans](size_t v) {
		if (ans.find(v) != ans.end())
			std::cout << " [color=green]";
		return false;
	};
	auto f2 = [](Edge<size_t>) mutable {};
	graphviz(G, f1, f2);
	return 0;
}
#endif

