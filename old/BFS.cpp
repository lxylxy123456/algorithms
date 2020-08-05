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
#define MAIN_BFS
#endif

#ifndef FUNC_BFS
#define FUNC_BFS

#include "utils.h"

#include "Queue.cpp"
#include "Graph.cpp"

enum BFSColor { white, gray, black };

template <typename T>
class BFSInfo {
	public:
		BFSInfo(): color(white) {}
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
			ans[*i] = BFSInfo<T>(gray, 0);
		else
			ans[*i] = BFSInfo<T>();
	}
	Queue<T> Q(G.V.size());
	Q.Enqueue(s);
	while (!Q.Empty()) {
		T u = Q.Dequeue();
		for (auto i = G.edges_from(u); !i.end(); i++)
			if (ans[i.d()].color == white) {
				ans[i.d()].color = gray;
				ans[i.d()].d = ans[u].d + 1;
				ans[i.d()].pi = u;
				Q.Enqueue(i.d());
			}
		ans[u].color = black;
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
#endif

#ifdef MAIN_BFS
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5);
	const size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = get_argv(argc, argv, 3, 0);
	GraphAdjList<size_t> G(dir);
	random_graph(G, v, e);
	umap<size_t, BFSInfo<size_t>> inf;
	size_t s = 0;
	BFS(G, s, inf);
	auto f1 = [inf](size_t v) mutable {
		BFSInfo<size_t>& i = inf[v];
		std::cout << " [";
		switch (i.color) {
			case white:
				break;
			case black:
				std::cout << "color=black style=filled fontcolor=white ";
				break;
			case gray:
				std::cout << "color=gray style=filled ";
				break;
		}
		std::cout << "label=\"" << v << "\\n";
		if (i.d == 0 || i.d.inf)
			std::cout << "d = " << i.d;
		else
			std::cout << "d = " << i.d << "; pi = " << i.pi;
		std::cout << "\"]";
		return true;
	};
	auto f2 = [](Edge<size_t> e) {};
	graphviz(G, f1, f2);
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		std::vector<size_t> ans;
		PrintPath(s, *i, inf, ans);
		std::cout << *i << '\t';
		if (ans.size())
			output_integers(ans);
		else
			std::cout << "no path from " << s << " exists" << std::endl;
	}
	return 0;
}
#endif

