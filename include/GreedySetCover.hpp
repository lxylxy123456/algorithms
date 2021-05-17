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

#ifndef ALGORITHMS_GREEDYSETCOVER
#define ALGORITHMS_GREEDYSETCOVER

#include <cassert>
#include <set>
#include <vector>

namespace algorithms {

#define set_T typename std::set<T>

template <typename T>
std::set<std::size_t> GreedySetCover(set_T& X, std::vector<set_T>& F) {
	std::size_t U_size = X.size();
	std::set<std::size_t> e;
	std::vector<set_T> FU = F;
	while (U_size) {
		std::size_t s, s_size = 0;
		for (std::size_t i = 0; i < FU.size(); i++) {
			std::size_t i_size = FU[i].size();
			if (s_size < i_size) {
				s = i;
				s_size = i_size;
			}
		}
		assert(s_size);
		for (auto i = FU[s].begin(); i != FU[s].end(); i++) {
			U_size--;
			for (std::size_t j = 0; j < FU.size(); j++)
				if (j != s)
					FU[j].erase(*i);
		}
		FU[s].clear();
		e.insert(s);
	}
	return e;
}

}

#endif
