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

#ifndef ALGORITHMS_ACTIVITYSELECTOR
#define ALGORITHMS_ACTIVITYSELECTOR

#define EVENTS std::vector<Event<T>>

#include <algorithm>
#include <iostream>
#include <vector>

namespace algorithms {

template <typename T>
class Event {
	public:
		Event(T start, T finish): s(start), f(finish) {
			if (s > f)
				std::swap(s, f);
		}
		bool operator<=(const Event<T>& rhs) const { return f <= rhs.f; }
		bool operator==(const Event<T>& rhs) const { return f == rhs.f; }
		friend std::ostream& operator<<(std::ostream& os, const Event<T>& rhs) {
			return os << rhs.s << '~' << rhs.f;
		}
		T s, f;
};

template <typename T>
void RecursiveActivitySelector(const EVENTS& e, std::size_t k, EVENTS& ans) {
	const std::size_t n = e.size();
	std::size_t m = k;
	while (m < n && k && e[m].s < e[k - 1].f)
		m++;
	if (m < n) {
		ans.push_back(e[m]);
		RecursiveActivitySelector(e, m + 1, ans);
	}
}

template <typename T>
void GreedyActivitySelector(const EVENTS& e, EVENTS& ans) {
	const std::size_t n = e.size();
	T k = e[0].s;
	for (std::size_t i = 0; i < n; i++) {
		if (e[i].s >= k) {
			ans.push_back(e[i]);
			k = e[i].f;
		}
	}
}

}

#endif
