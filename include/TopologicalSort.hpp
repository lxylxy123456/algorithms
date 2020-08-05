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

#ifndef ALGORITHMS_TOPOLOGICALSORT
#define ALGORITHMS_TOPOLOGICALSORT

#include <deque>
#include "utils.h"

#include "DFS.hpp"

namespace algorithms {


template <typename GT, typename T, typename VT>
void DFSVisit_TS(GT& G, VT& inf, std::deque<T>& ans, T u, size_t& time) {
	DFSInfo<T>& info = inf[u];
	info.set_color(gray, time);
	for (auto i = G.edges_from(u); !i.end(); i++) {
		T v = i.d();
		DFSInfo<T>& vinfo = inf[v];
		if (vinfo.color == white) {
			vinfo.set_pi(u);
			DFSVisit_TS(G, inf, ans, v, time);
		}
	}
	info.set_color(black, time);
	ans.push_front(u);
}

template <typename GT, typename VT, typename T>
void DFS_TS(GT& G, VT& inf, std::deque<T>& ans) {
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		inf[*i] = DFSInfo<T>();
	size_t time = 0;
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		if (inf[*i].color == white)
			DFSVisit_TS(G, inf, ans, *i, time);
}

template <typename GT, typename VT, typename T>
void TopologicalSort(GT& G, VT& inf, std::deque<T>& ans) {
	DFS_TS(G, inf, ans);
}

template <typename GT, typename T>
void TopologicalSort(GT& G, std::deque<T>& ans) {
	umap<T, DFSInfo<T>> inf;
	TopologicalSort(G, inf, ans);
}

}

#endif
