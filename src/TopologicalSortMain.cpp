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

#include "TopologicalSort.hpp"

#include <deque>
#include <iostream>

#include "DFS.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t v = get_argv(argc, argv, 1, 5);
	const std::size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = get_argv(argc, argv, 3, 0);
	GraphAdjList<std::size_t> G(dir);
	random_graph(G, v, e);
	umap<std::size_t, DFSInfo<size_t>> inf;
	std::deque<std::size_t> ans;
	TopologicalSort(G, inf, ans);
	auto f1 = [inf](std::size_t v) mutable {
		DFSInfo<std::size_t>& i = inf[v];
		std::cout << " [label=\"" << v << "\\nd = " << i.d << "; f = " << i.f;
		std::cout << "; pi = " << i.pi << "\"]";
		return true;
	};
	auto f2 = [](Edge<std::size_t> e) mutable {};
	graphviz(G, f1, f2);
	output_integers(ans);
	return 0;
}
