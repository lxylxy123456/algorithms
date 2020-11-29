//
//  algorithm - some algorithms in "Introduction to Algorithms", third edition
//  Copyright (C) 2020  lxylxy123456
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
#include "utils.hpp"

#include "Graph.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace algorithms;

int test(size_t v, size_t e) {
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
	ApproxMinWeightVC(G, w, ans, 1e-7);
	auto f1 = [w, ans](size_t v) mutable {
		std::cout << " [label=" << w[v];
		if (ans.find(v) != ans.end())
			std::cout << " color=green";
		std::cout << "]";
		return true;
	};
	auto f2 = [](Edge<size_t>) mutable {};
	graphviz(G, f1, f2);
	for (auto i = G.all_edges(); !i.end(); i++)
		assert(ans.find(i.s()) != ans.end() || ans.find(i.d()) != ans.end());
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<size_t> m = {5, 10, 23, 49};
	for (std::vector<size_t>::iterator v = m.begin(); v < m.end(); v++)
		for (std::vector<size_t>::iterator e = m.begin(); e < m.end(); e++)
			for (int n = 0; n < 5; n++)
				test(*v, *e);
	return 0;
}
