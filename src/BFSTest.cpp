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

#include "BFS.hpp"

#include <cassert>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test1(bool dir) {
	GraphAdjList<std::size_t> G(dir);
	G.add_edge(0, 1);
	G.add_edge(1, 2);
	G.add_edge(2, 3);
	G.add_edge(3, 4);
	G.add_edge(5, 6);
	umap<std::size_t, BFSInfo<size_t>> inf;
	std::size_t s = 0;
	graphviz(G);
	BFS(G, s, inf);
	std::vector<std::vector<std::size_t>> expected = {
		{0},
		{0, 1},
		{0, 1, 2},
		{0, 1, 2, 3},
		{0, 1, 2, 3, 4},
		{},
		{}
	};
	for (std::size_t i = 0; i < expected.size(); i++) {
		std::vector<std::size_t> ans;
		PrintPath(s, i, inf, ans);
		assert(ans == expected[i]);
	}
	return 0;
}

int test2(bool dir) {
	GraphAdjList<std::size_t> G(dir);
	G.add_edge(0, 1);
	G.add_edge(0, 2);
	G.add_edge(0, 3);
	G.add_edge(1, 4);
	G.add_edge(1, 5);
	G.add_edge(2, 6);
	G.add_edge(2, 7);
	umap<std::size_t, BFSInfo<size_t>> inf;
	std::size_t s = 0;
	graphviz(G);
	BFS(G, s, inf);
	std::vector<std::vector<std::size_t>> expected = {
		{0},
		{0, 1},
		{0, 2},
		{0, 3},
		{0, 1, 4},
		{0, 1, 5},
		{0, 2, 6},
		{0, 2, 7}
	};
	for (std::size_t i = 0; i < expected.size(); i++) {
		std::vector<std::size_t> ans;
		PrintPath(s, i, inf, ans);
		assert(ans == expected[i]);
	}
	return 0;
}


int test3() {
	GraphAdjList<std::size_t> G(true);
	G.add_edge(0, 1);
	G.add_edge(0, 2);
	G.add_edge(0, 3);
	G.add_edge(1, 4);
	G.add_edge(1, 5);
	G.add_edge(2, 6);
	G.add_edge(2, 7);
	umap<std::size_t, BFSInfo<size_t>> inf;
	std::size_t s = 1;
	graphviz(G);
	BFS(G, s, inf);
	std::vector<std::vector<std::size_t>> expected = {
		{},
		{1},
		{},
		{},
		{1, 4},
		{1, 5},
		{},
		{}
	};
	for (std::size_t i = 0; i < expected.size(); i++) {
		std::vector<std::size_t> ans;
		PrintPath(s, i, inf, ans);
		assert(ans == expected[i]);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	test1(true);
	test2(true);
	test1(false);
	test2(false);
	test3();
	return 0;
}
