//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#ifndef ALGORITHMS_BFS
#define ALGORITHMS_BFS

#include <vector>

#include "Graph.hpp"
#include "Queue.hpp"

using std::size_t;

namespace algorithms {

enum BFSColor { bfs_white, bfs_gray, bfs_black };

template <typename T>
class BFSInfo {
	public:
		BFSInfo(): color(bfs_white) {}
		BFSInfo(enum BFSColor c, size_t dist): color(c), d(dist) {}
		BFSInfo(enum BFSColor c, size_t dist, T p): color(c), d(dist), pi(p) {}
		enum BFSColor color;
		Weight<size_t> d;
		T pi;
};

template <typename GT, typename T>
void BFS(GT& G, T s, umap<T, BFSInfo<T>>& ans) {
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		if (*i == s)
			ans[*i] = BFSInfo<T>(bfs_gray, 0);
		else
			ans[*i] = BFSInfo<T>();
	}
	Queue<T> Q(G.V.size());
	Q.Enqueue(s);
	while (!Q.Empty()) {
		T u = Q.Dequeue();
		for (auto i = G.edges_from(u); !i.end(); i++)
			if (ans[i.d()].color == bfs_white) {
				ans[i.d()].color = bfs_gray;
				ans[i.d()].d = ans[u].d + 1;
				ans[i.d()].pi = u;
				Q.Enqueue(i.d());
			}
		ans[u].color = bfs_black;
	}
}

template <typename T>
void PrintPath(T s, T v, umap<T, BFSInfo<T>> inf, std::vector<T>& ans) {
	if (v == s)
		ans.push_back(v);
	else if (!inf[v].d.inf) {
		PrintPath(s, inf[v].pi, inf, ans);
		ans.push_back(v);
	}
}

}

#endif
