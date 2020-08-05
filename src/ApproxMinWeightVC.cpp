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

#include "ApproxMinWeightVC.hpp"

#include "utils.h"
#include "Graph.hpp"
#include "Simplex.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 10);
	const size_t e = get_argv(argc, argv, 2, 20);
	const bool dir = 0;
	GraphAdjList<size_t> G(dir);
	random_graph(G, v, e);
	uset<size_t> ans;
	std::vector<int> weight;
	random_integers(weight, 1, v, v);
	using WT = double;
	umap<size_t, WT> w;
	for (size_t i = 0; i < v; i++)
		w[i] = weight[i];
	ApproxMinWeightVC(G, w, ans);
	auto f1 = [w, ans](size_t v) mutable {
		std::cout << " [label=" << w[v];
		if (ans.find(v) != ans.end())
			std::cout << " color=green";
		std::cout << "]";
		return true;
	};
	auto f2 = [](Edge<size_t>) mutable {};
	graphviz(G, f1, f2);
	return 0;
}
