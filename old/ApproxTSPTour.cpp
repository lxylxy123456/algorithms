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
#define MAIN_ApproxTSPTour
#endif

#ifndef FUNC_ApproxTSPTour
#define FUNC_ApproxTSPTour

#include "utils.h"

#include "MST.cpp"
#include "SegmentsIntersect.cpp"

template <typename GT, typename T>
void TreeWalk(GT& G, T current, T* last, std::vector<T>& H) {
	H.push_back(current);
	for (auto i = G.edges_from(current); !i.end(); i++)
		if (!last || i.d() != *last)
			TreeWalk(G, i.d(), &current, H);
}

template <typename GT, typename T, typename WT>
void ApproxTSPTour(GT& G, umap_WT& c, std::vector<T>& H) {
	T r = *G.V.begin();
	umap<T, MSTPrimInfo<T, WT>> MST_info;
	MSTPrim(G, c, r, MST_info);
	GT MST_Graph(false);
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		const MSTPrimInfo<T, WT>& info = MST_info[*i];
		if (!info.pi_nil)
			MST_Graph.add_edge(*i, info.pi);
	}
	H.reserve(G.V.size() + 1);
	TreeWalk<GT, T>(MST_Graph, r, nullptr, H);
	H.push_back(r);
}
#endif

#ifdef MAIN_ApproxTSPTour
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 200);
	const size_t m = get_argv(argc, argv, 2, 10);
	const bool dir = 0;
	std::vector<int> b;
	random_integers(b, -n, n, m * 2);
	using T = size_t;
	using WT = double;
	GraphAdjList<size_t> G(dir);
	umap_WT c;
	std::vector<Vector<T>> S;
	S.reserve(m);
	for (size_t i = 0; i < m; i++) {
		S.push_back(Vector<T>(b[2 * i + 0], b[2 * i + 1]));
		for (size_t j = 0; j < i; j++) {
			G.add_edge(i, j);
			c[Edge<T>(i, j, false)] = (S[i] - S[j]).Length();
		}
	}
	std::vector<size_t> H;
	ApproxTSPTour(G, c, H);
	std::cout << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?>"
				 << std::endl;
	std::cout << "<svg height=\"" << 2 * n << "\" width=\"" << 2 * n << "\">"
				 << std::endl;
	std::cout << "\t<rect fill=\"#ffffff\" x=\"0\" y=\"0\" width=\"" << 2 * n
				 << "\" height=\"" << 2 * n << "\"/>" << std::endl;
	std::cout << "\t<polygon stroke=\"#000000\" fill=\"#cccccc\" points=\"";
	for (auto i = H.begin(); i != H.end(); i++)
		std::cout << n + S[*i].x + 1 << "," << n + S[*i].y + 1 << " ";
	std::cout << "\"/>" << std::endl;
	for (size_t i = 0; i < m; i++)
		std::cout << "\t<circle cx=\"" << n + S[i].x + 1 << "\" cy=\""
				 << n + S[i].y + 1 << "\" r=\"2\"/>" << std::endl;
	std::cout << "</svg>" << std::endl;
	return 0;
}
#endif

