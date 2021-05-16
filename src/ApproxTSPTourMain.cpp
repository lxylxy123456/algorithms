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

#include "ApproxTSPTour.hpp"

#include <iostream>
#include <vector>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t n = get_argv(argc, argv, 1, 200);
	const std::size_t m = get_argv(argc, argv, 2, 10);
	const bool dir = 0;
	std::vector<int> b;
	random_integers(b, -n, n, m * 2);
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
	std::cout << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?>"
				 << std::endl;
	std::cout << "<svg height=\"" << 2 * n << "\" width=\"" << 2 * n << "\">"
				 << std::endl;
	std::cout << "\t<rect fill=\"#ffffff\" x=\"0\" y=\"0\" width=\"" << 2 * n
				 << "\" height=\"" << 2 * n << "\"/>" << std::endl;
	std::cout << "\t<polygon stroke=\"#000000\" fill=\"#cccccc\" points=\"";
	for (auto i = H.begin(); i != H.end(); i++)
		std::cout << n + S[*i].x + 1 << "," << n + S[*i].y + 1 << " ";
	std::cout << "\"/>" << std::endl;
	for (std::size_t i = 0; i < m; i++)
		std::cout << "\t<circle cx=\"" << n + S[i].x + 1 << "\" cy=\""
				 << n + S[i].y + 1 << "\" r=\"2\"/>" << std::endl;
	std::cout << "</svg>" << std::endl;
	return 0;
}
