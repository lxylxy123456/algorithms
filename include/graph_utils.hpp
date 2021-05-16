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

#ifndef ALGORITHMS_GRAPH_UTILS
#define ALGORITHMS_GRAPH_UTILS

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Graph.hpp"
#include "random_integers.hpp"

namespace algorithms {

template <typename T, typename WT, typename F1, typename F2>
void graphviz(WeightedAdjMatrix<T, WT> G, F1 f1, F2 f2) {
	if (G.dir)
		std::cout << "digraph G {" << std::endl;
	else
		std::cout << "graph G {" << std::endl;
	std::cout << '\t';
	for (auto i = G.V.begin(); i != G.V.end(); i++) {
		std::cout << *i;
		if (f1(*i))
			std::cout << "; \n\t";
		else
			std::cout << "; ";
	}
	std::cout << std::endl;
	for (auto i = G.E.begin(); i != G.E.end(); i++) {
		for (auto j = i->second.begin(); j != i->second.end(); j++) {
			if (i->first != j->first && !j->second.inf &&
				(G.dir || i->first < j->first)) {
				Edge<T> e(i->first, j->first, G.dir);
				std::cout << '\t' << e;
				std::cout << " [label=\"" << j->second << "\"";
				f2(e, j->second);
				std::cout << "]; " << std::endl;
			}
		}
	}
	std::cout << "}" << std::endl;
}

template <typename T, typename WT>
void graphviz(WeightedAdjMatrix<T, WT> G) {
	auto f1 = [](T v) { return false; };
	auto f2 = [](Edge<T> e, Weight<WT> w) {};
	graphviz(G, f1, f2);
}

}

#endif

