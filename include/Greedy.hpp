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

#ifndef ALGORITHMS_GREEDY
#define ALGORITHMS_GREEDY

#include <map>
#include <set>

using std::size_t;

namespace algorithms {

template <typename T>
class Matroid {
	public :
		Matroid(const std::set<T>& s): S(s) {}
		virtual bool I(const std::set<T>& A) const { return true; }
		std::set<T> S;
};

template <typename T, typename W>
void Greedy(const Matroid<T>& M, W(*w)(T), std::set<T>& A) {
	A.clear();
	std::multimap<W, T> S;
	for (auto i = M.S.begin(); i != M.S.end(); i++)
		S.insert(std::pair<W, T>(w(*i), *i));
	for (auto i = S.rbegin(); i != S.rend(); i++) {
		T& x = i->second;
		A.insert(x);
		if (!M.I(A))
			A.erase(x);
	}
}

}

#endif
