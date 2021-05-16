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

#ifndef ALGORITHMS_HIREASSISTANT
#define ALGORITHMS_HIREASSISTANT

#include <cassert>
#include <vector>

namespace algorithms {

template <typename T>
class Candidate {
	public:
	Candidate(T a, T c_i, T c_h, bool i_ed): abl(a),ci(c_i),ch(c_h),ied(i_ed) {}
	T ability(void) const { assert(ied); return abl; }
	void interview(T& tc) { ied = true; tc += ci; }
	void hire(T& tc) const { tc += ch; }
	private:
	T abl, ci, ch;
	bool ied;
};

template <typename T>
T HireAssistant(std::vector<Candidate<T>*> candidates) {
	typename std::vector<Candidate<T>*>::iterator i = candidates.begin();
	Candidate<T>* best = *i;
	T total_cost = 0;
	for (i++; i != candidates.end(); i++) {
		(*i)->interview(total_cost);
		if ((*i)->ability() > best->ability()) {
			best = *i;
			best->hire(total_cost);
		}
	}
	return total_cost;
}

}

#endif
