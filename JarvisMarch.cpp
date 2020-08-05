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

#ifndef MAIN
#define MAIN
#define MAIN_JarvisMarch
#endif

#ifndef FUNC_JarvisMarch
#define FUNC_JarvisMarch

#include <algorithm>
#include "utils.h"

#include "SegmentsIntersect.cpp"

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
#endif

#ifdef MAIN_JarvisMarch
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 200);
	const size_t m = get_argv(argc, argv, 2, 10);
	std::vector<int> b;
	random_integers(b, -n, n, m * 2);
	using T = double;
	std::vector<Vector<T>> Q, S;
	Q.reserve(m);
	for (size_t i = 0; i < m; i++)
		Q.push_back(Vector<T>(b[2 * i + 0], b[2 * i + 1]));
	JarvisMarch(Q, S);
	std::cout << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?>"
				 << std::endl;
	std::cout << "<svg height=\"" << 2 * n << "\" width=\"" << 2 * n << "\">"
				 << std::endl;
	std::cout << "\t<rect fill=\"#ffffff\" x=\"0\" y=\"0\" width=\"" << 2 * n
				 << "\" height=\"" << 2 * n << "\"/>" << std::endl;
	std::cout << "\t<polygon stroke=\"#000000\" fill=\"#cccccc\" points=\"";
	for (auto i = S.begin(); i != S.end(); i++)
		std::cout << n + i->x + 1 << "," << n + i->y + 1 << " ";
	std::cout << "\"/>" << std::endl;
	for (auto i = Q.begin(); i != Q.end(); i++)
		std::cout << "\t<circle cx=\"" << n + i->x + 1 << "\" cy=\""
				 << n + i->y + 1 << "\" r=\"2\"/>" << std::endl;
	std::cout << "</svg>" << std::endl;
	return 0;
}
#endif

