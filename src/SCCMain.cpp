//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#include "SCC.hpp"

#include <map>

#include "DisjointSet.hpp"
#include "TopologicalSort.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t v = get_argv(argc, argv, 1, 5);
	const size_t e = get_argv(argc, argv, 2, 10);
	const bool dir = get_argv(argc, argv, 3, 1);
	GraphAdjList<size_t> G(dir);
	random_graph(G, v, e);
	DisjointSetForest<size_t> ans;
	StronglyConnectedComponents(G, ans);
	auto f1 = [](size_t v) { return false; };
	auto f2 = [](Edge<size_t> e) {};
	graphviz(G, f1, f2);
	// print ans
	std::map<size_t, uset<size_t>> components;
	for (auto i = G.V.begin(); i != G.V.end(); i++)
		components[ans.FindSet(*i)].insert(*i);
	for (auto i = components.begin(); i != components.end(); i++)
		output_integers(i->second);
	return 0;
}
