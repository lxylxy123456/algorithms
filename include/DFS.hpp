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

#ifndef ALGORITHMS_DFS
#define ALGORITHMS_DFS

#include "Graph.hpp"

namespace algorithms {

enum DFSColor { white, gray, black };

enum DFSEdgeType { tree, back, forward, cross };

template <typename T>
class DFSInfo {
	public:
		DFSInfo(): color(white), d(-1), f(-1) {}
		void set_color(DFSColor c, size_t& time) {
			color = c;
			switch (color) {
				case white:
					break;
				case gray:
					d = time++;
					break;
				case black:
					f = time++;
					break;
			}
		}
		void set_pi(T_ptr<T> p) {
			pi = p;
		}
		enum DFSColor color;
		size_t d, f;
		T_ptr<T> pi;
};

std::ostream& operator<<(std::ostream& os, const DFSEdgeType& rhs) {
	switch (rhs) {
		case tree:
			return os << "T";
		case back:
			return os << "B";
		case forward:
			return os << "F";
		case cross:
			return os << "C";
		default:
			return os;
	}
}

template <typename T, typename VT>
bool is_ancestor(VT& ans, T u, T v) {
	if (u == v)
		return true;
	DFSInfo<T>& info = ans[v];
	if (!info.pi.nil)
		return is_ancestor(ans, u, info.pi.val);
	else
		return false;
}

template <typename GT, typename T, typename VT, typename ET>
void DFSVisit(GT& G, VT& ans, ET edge_ans, T u, size_t& time) {
	DFSInfo<T>& info = ans[u];
	info.set_color(gray, time);
	for (auto i = G.edges_from(u); !i.end(); i++) {
		T v = i.d();
		DFSInfo<T>& vinfo = ans[v];
		switch (vinfo.color) {
			case white:
				if (edge_ans && edge_ans->find(*i) == edge_ans->end())
					(*edge_ans)[*i] = tree;
				vinfo.set_pi(u);
				DFSVisit(G, ans, edge_ans, v, time);
				break;
			case gray:
				if (edge_ans && edge_ans->find(*i) == edge_ans->end())
					(*edge_ans)[*i] = back;
				break;
			case black:
				if (edge_ans && edge_ans->find(*i) == edge_ans->end()) {
					if (is_ancestor(ans, u, v))
						(*edge_ans)[*i] = forward;
					else
						(*edge_ans)[*i] = cross;
				}
				break;
		}
	}
	info.set_color(black, time);
}

template <typename T, typename GT, typename VT>
void DFS(GT& G, VT& ans, umap<Edge<T>, DFSEdgeType, EdgeHash<T>>* edge_ans) {
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		ans[*i] = DFSInfo<T>();
	size_t time = 0;
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		if (ans[*i].color == white)
			DFSVisit(G, ans, edge_ans, *i, time);
}

}

#endif
