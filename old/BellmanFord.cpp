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
#define MAIN_BellmanFord
#endif

#ifndef FUNC_BellmanFord
#define FUNC_BellmanFord

#include "utils.h"

#include "Graph.cpp"

template <typename T, typename WT>
class RelaxInfo {
	public:
		RelaxInfo() {}
		RelaxInfo(Weight<WT> k): d(k) {}
		void set_pi(T_ptr<T> p) { pi = p; }
		void set_d(Weight<WT> k) { d = k; }
		void set_d(const RelaxInfo<T, WT>& k) { d = k.d; }
		bool operator<(const RelaxInfo<T, WT>& rhs) const {
			return d < rhs.d;
		}
		bool operator>(const RelaxInfo<T, WT>& rhs) const {
			return rhs < *this;
		}
		RelaxInfo<T, WT> operator+(WT rhs) const {
			return RelaxInfo<T, WT>(d + rhs);
		}
		friend std::ostream& operator<<(std::ostream& os,
										const RelaxInfo<T, WT>& rhs) {
			return os << rhs.d;
		}
		T_ptr<T> pi;
		Weight<WT> d;
};

template <typename GT, typename T, typename WT>
void InitializeSingleSource(GT& G, T s, umap<T, RelaxInfo<T, WT>>& inf) {
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		inf[*i] = RelaxInfo<T, WT>();
	inf[s].set_d(0);
}

template <typename T, typename WT>
void Relax(T u, T v, umap_WT& w, umap<T, RelaxInfo<T, WT>>& inf) {
	WT weight = w[Edge<T>(u, v, true)];
	if (inf[v] > inf[u] + weight) {
		inf[v].set_d(inf[u] + weight);
		inf[v].set_pi(u);
	}
}

template <typename GT, typename T, typename WT>
bool BellmanFord(GT& G, umap_WT& w, T s, umap<T, RelaxInfo<T, WT>>& ans) {
	InitializeSingleSource(G, s, ans);
	for (size_t i = 0; i < G.V.size() - 1; i++)
		for (auto j = G.all_edges(); !j.end(); j++)
			Relax(j.s(), j.d(), w, ans);
	for (auto j = G.all_edges(); !j.end(); j++)
		if (ans[j.d()] > ans[j.s()] + w[*j])
			return false;
	return true;
}
#endif

#ifdef MAIN_BellmanFord
int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5);
	const size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = 1;
	const int weight_lower = get_argv<int>(argc, argv, 3, (0-e) / 4);
	const int weight_upper = get_argv<int>(argc, argv, 4, e);
	GraphAdjList<size_t> G(dir);
	random_graph(G, v, e);
	umap<Edge<size_t>, int, EdgeHash<size_t>> w;
	random_weight(G, w, weight_lower, weight_upper);
	umap<size_t, RelaxInfo<size_t, int>> ans;
	bool valid = BellmanFord(G, w, *G.V.begin(), ans);
	std::cout << std::boolalpha << valid << std::endl;
	auto f1 = [ans](size_t v) mutable {
		std::cout << " [label=\"" << v << " (" << ans[v] << ")\"]";
		return true;
	};
	auto f2 = [w, ans](Edge<size_t> e) mutable {
		std::cout << " [label=\"" << w[e] << "\"";
		if (!ans[e.d].pi.nil && ans[e.d].pi == e.s)
			std::cout << " style=bold";
		std::cout << "]";
	};
	graphviz(G, f1, f2);
	return 0;
}
#endif

