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

#include "MaximumBipartiteMatching.hpp"

#include "utils.h"
#include "FordFulkerson.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t vl = get_argv(argc, argv, 1, 5);
	const size_t vr = get_argv(argc, argv, 2, 5);
	const size_t e = get_argv(argc, argv, 3, 10);
	const bool dir = false;
	Bipartite<GraphAdjList<size_t>> G(dir);
	random_bipartite(G, vl, vr, e);
	uset<Edge<size_t>, EdgeHash<size_t>> ans;
	MaximumBipartiteMatching(G, ans);
	auto f1 = [](size_t v) { return false; };
	auto f2 = [ans](Edge<size_t> e) mutable {
		if (ans.find(e) != ans.end())
			std::cout << " [style=bold]";
	};
	G.graphviz(f1, f2);
	return 0;
}