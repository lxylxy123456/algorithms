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

#include "ApproxTSPTour.hpp"

#include <cassert>
#include <vector>

#include "RandomPermute.hpp"
#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(std::size_t n, std::size_t m) {
	const bool dir = 0;
	std::vector<int> b;
	random_integers(b, -n, n, m * 2);
	output_integers(b);
	using T = std::size_t;
	using WT = double;
	GraphAdjList<std::size_t> G(dir);
	umap_WT c;
	std::vector<Vector<T>> S;
	S.reserve(m);
	for (std::size_t i = 0; i < m; i++) {
		S.push_back(Vector<T>(b[2 * i + 0], b[2 * i + 1]));
		for (std::size_t j = 0; j < i; j++) {
			G.add_edge(i, j);
			c[Edge<T>(i, j, false)] = (S[i] - S[j]).Length();
		}
	}
	std::vector<std::size_t> H;
	ApproxTSPTour(G, c, H);
	assert(H.size() == m + 1 && H[m] == H[0]);
	WT approx_dist = 0.0, random_dist = 0.0;
	std::vector<std::size_t> visited(m, 0), R(H);
	RandomizeInPlace(R);
	for (std::size_t i = 0; i < m; i++) {
		approx_dist += sqrt((S[H[i]] - S[H[i + 1]]).Length());
		random_dist += sqrt((S[R[i]] - S[R[i + 1]]).Length());
		visited[H[i]]++;
	}
	for (std::size_t i = 0; i < m; i++)
		assert(visited[i] == 1);
	assert(random_dist * 2 >= approx_dist);
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<std::size_t> ns = {100, 1024, 10000};
	std::vector<std::size_t> ms = {2, 5, 10, 23, 49, 100};
	for (std::vector<std::size_t>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<std::size_t>::iterator m = ms.begin(); m < ms.end(); m++)
			test(*n, *m);
	return 0;
}
