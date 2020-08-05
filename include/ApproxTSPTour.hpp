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

#ifndef ALGORITHMS_APPROXTSPTOUR
#define ALGORITHMS_APPROXTSPTOUR

#include "utils.h"

#include "MST.hpp"
#include "SegmentsIntersect.hpp"

namespace algorithms {

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

}

#endif
