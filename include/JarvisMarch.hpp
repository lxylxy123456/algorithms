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

#ifndef ALGORITHMS_JARVISMARCH
#define ALGORITHMS_JARVISMARCH

#include <algorithm>
#include "utils.h"

#include "SegmentsIntersect.hpp"

namespace algorithms {

template <typename T>
class Angle: public Vector<T> {
	public:
		Angle(): Vector<T>(0, 0) {}
		Angle(T X, T Y): Vector<T>(X, Y) {}
		Angle(Vector<T> a, Vector<T> b): Vector<T>(b - a) {}
		int get_partition() const {	// when x = y = 0, assume inf
			const T &x = this->x, &y = this->y;
			if (y > 0) {			//     2
				if (x > 0)			//   3 | 1
					return 1; 		// 4---+---0
				else if (x == 0)	//   5 | 7
					return 2; 		//     6
				else
					return 3;
			} else if (y == 0) {
				if (x > 0)
					return 0;
				else if (x == 0)
					return -1;
				else
					return 4;
			} else {
				if (x > 0)
					return 7;
				else if (x == 0)
					return 6;
				else
					return 5;
			}
		}
		bool operator<(const Angle<T>& rhs) const {
			const Angle<T>& lhs = *this;
			int lp = lhs.get_partition(), rp = rhs.get_partition();
			if (lp == -1)
				return false;
			else if (rp == -1)
				return true;
			else if (lp != rp)
				return lp < rp;
			else
				return lhs.Cross(rhs) > 0;
		}
		bool operator==(const Angle<T>& rhs) const {
			const Angle<T>& lhs = *this;
			int lp = lhs.get_partition(), rp = rhs.get_partition();
			if (lp == -1 || rp == -1)
				return false;
			else if (lp != rp)
				return false;
			else
				return lhs.Cross(rhs) == 0;
		}
};

template <typename T>
void JarvisMarch(std::vector<Vector<T>>& Q, std::vector<Vector<T>>& ans) {
	Vector<T> p0 = Q[0];
	for (auto i = Q.begin(); i != Q.end(); i++)
		if (i->y < p0.y || (i->y == p0.y && i->x < p0.x))
			p0 = *i;
	Angle<T> last_angle(1, 0);
	Vector<T> last = p0;
	while (true) {
		ans.push_back(last);
		Angle<T> candidate_angle;
		Vector<T> candidate;
		for (auto i = Q.begin(); i != Q.end(); i++) {
			Angle<T> current(last, *i);
			if (!(current < last_angle)) {
				if (current < candidate_angle ||
					(current == candidate_angle &&
					(candidate - last).Length() < (*i - last).Length())) {
					candidate_angle = current;
					candidate = *i;
				}
			}
		}
		if (candidate == p0)
			break;
		last = candidate;
		last_angle = candidate_angle;
	}
}

}

#endif
