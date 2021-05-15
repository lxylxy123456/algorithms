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

#ifndef ALGORITHMS_PRINT_TREE
#define ALGORITHMS_PRINT_TREE

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::size_t;

namespace algorithms {

// A string with custom length
class StringLen: public std::string {
	public:
		StringLen(std::string s): std::string(s), len(s.size()) {}
		StringLen(std::string s, size_t l): std::string(s), len(l) {}
		size_t len;
};

// Helper class to navigate through a tree
template <typename NodeType>
class TreeNavigator {
	public:
		NodeType left(NodeType node);
		NodeType right(NodeType node);
		StringLen key(NodeType node);
		bool is_nil(NodeType node);
};

class TextMatrix {
	public:
		TextMatrix(std::string s): w(s.size()), h(1), l(0), r(w), m(1, s) {}
		TextMatrix(std::string s, size_t w): w(w), h(1), l(0), r(w), m(1, s) {}
		TextMatrix(StringLen s): w(s.len), h(1), l(0), r(w), m(1, s) {}
		TextMatrix(size_t w, size_t h): w(w), h(h), l(0), r(w), m() {}
		TextMatrix(size_t w, size_t h, char d):
			w(w), h(h), l(0), r(w), m(h, std::string(w, d)) {}
		TextMatrix(size_t w, size_t h, size_t l, size_t r):
			w(w), h(h), l(l), r(r), m() {}
		TextMatrix(size_t w, size_t h, size_t l, size_t r, char d):
			w(w), h(h), l(l), r(r), m(h, std::string(w, d)) {}
		friend std::ostream& operator<<(std::ostream& os, TextMatrix& rhs) {
			for (std::vector<std::string>::iterator i = rhs.m.begin();
				i < rhs.m.end(); i++)
				os << *i << std::endl;
			return os;
		}
		friend std::ostream& operator<<(std::ostream& os, TextMatrix&& rhs) {
			for (std::vector<std::string>::iterator i = rhs.m.begin();
				i < rhs.m.end(); i++)
				os << *i << std::endl;
			return os;
		}
		// w / h: width / height of matrix
		// l / r: left / right of root string
		size_t w, h, l, r;
		std::vector<std::string> m;
		//   0123456789
		//  +----------+
		// 0|   345    |	w = 10; h = 3; l = 3; r = 6;
		// 1|  /   \   |	m = {"   345    ", "  /   \   ", "12     678"};
		// 2|12     678|
		//  +----------+
};

template <typename NodeType, typename Navigator>
class TreePrinter {
	private:
		static TextMatrix lbranch(size_t w) {
			// 1     2      3       4        5         6
			// +---+ +----+ +-----+ +------+ +-------+ +--------+
			// |  r| |   r| |    r| |     r| |    _ r| |     _ r|
			// | / | | /  | |  /  | |  _/  | |  _/   | |  __/   |
			// |k  | |k   | |k    | |k     | |k      | |k       |
			// +---+ +----+ +-----+ +------+ +-------+ +--------+
			// First row: ' ' * ? + '_' * max((w - 3) // 2, 0) + (' ' if w != 1)
			// Second row: '_' * max((w - 2) // 2, 0) + '/' + (' ' if w == 2) +
			//             ' ' * max((w - 1) // 2, 0)
			size_t w11 = w > 1 ? 1 : 0;
			size_t w12 = w >= 3 ? (w - 3) / 2 : 0;
			size_t w13 = w - w11 - w12;
			size_t w22 = w >= 2 ? (w - 2) / 2 : 0;
			size_t w23 = w > 2 ? 1 : 0;
			size_t w21 = w - w22 - w23 - 1;
			TextMatrix ans(w, 2);
			ans.m.push_back(std::string(w13, ' ') + std::string(w12, '_') +
							std::string(w11, ' '));
			ans.m.push_back(std::string(w23, ' ') + std::string(w22, '_') + 
							"/" + std::string(w21, ' '));
			return ans;
		}
		static TextMatrix rbranch(size_t w) {
			// 1     2      3       4        5         6
			// +---+ +----+ +-----+ +------+ +-------+ +--------+
			// |r  | |r   | |r    | |r     | |r _    | |r _     |
			// | \ | |  \ | |  \  | |  \_  | |   \_  | |   \__  |
			// |  k| |   k| |    k| |     k| |      k| |       k|
			// +---+ +----+ +-----+ +------+ +-------+ +--------+
			// First row: (' ' if w != 1) + '_' * max((w - 3) // 2, 0) + ' ' * ?
			// Second row: (' ' if w == 2) + ' ' * max((w - 1) // 2, 0) + '\' +
			//             '_' * max((w - 2) // 2, 0)
			size_t w11 = w > 1 ? 1 : 0;
			size_t w12 = w >= 3 ? (w - 3) / 2 : 0;
			size_t w13 = w - w11 - w12;
			size_t w22 = w >= 2 ? (w - 2) / 2 : 0;
			size_t w23 = w > 2 ? 1 : 0;
			size_t w21 = w - w22 - w23 - 1;
			TextMatrix ans(w, 2);
			ans.m.push_back(std::string(w11, ' ') + std::string(w12, '_') +
							std::string(w13, ' '));
			ans.m.push_back(std::string(w21, ' ') + "\\" +
							std::string(w22, '_') + std::string(w23, ' '));
			return ans;
		}
	public:
		TreePrinter(NodeType root, Navigator nav): root(root), nav(nav) {}
		TextMatrix print(NodeType root) {
			TextMatrix tm_root(nav.key(root));
			if (nav.is_nil(nav.left(root))) {
				if (nav.is_nil(nav.right(root))) {
					// Leaf node
					return tm_root;
				} else {
					// Only have right sub-tree
					// +-----------+ +---------------+ +----------+
					// |4 __       | |root _         | |root      |
					// |    \__    | |      \_       | |    \     |
					// |        3  | |         kkk   | |     kkk  |
					// |       / \ | |    lllll   rrr| |        rr|
					// | 111112   4| |    lllll   rrr| |        rr|
					// +-----------+ +---------------+ +----------+
					//                                      ^ rseam
					TextMatrix tm_right(print(nav.right(root)));
					size_t rseam_w = tm_right.l == 0 ? 1 : 0;
					size_t rbranch_w = rseam_w + tm_right.l;
					TextMatrix ans(tm_root.w + rseam_w + tm_right.w,
									tm_right.h + 2, 0, tm_root.w);
					TextMatrix tm_rbranch = rbranch(rbranch_w);
					ans.m.push_back(tm_root.m[0] + tm_rbranch.m[0] +
									std::string(tm_right.w - tm_right.l, ' '));
					ans.m.push_back(std::string(tm_root.w, ' ') +
									tm_rbranch.m[1] +
									std::string(tm_right.w - tm_right.l, ' '));
					for (size_t i = 0; i < tm_right.h; i++) {
						ans.m.push_back(std::string(tm_root.w + rseam_w, ' ') +
										tm_right.m[i]);
					}
					return ans;
				}
			} else {
				if (nav.is_nil(nav.right(root))) {
					// Only have left sub-tree
					// +-----------+ +---------------+ +----------+
					// |       __ 4| |         _ root| |      root|
					// |    __/    | |       _/      | |     /    |
					// |  2        | |   kkk         | |  kkk     |
					// | / \       | |lll   rrrrr    | |ll        |
					// |1   333333 | |lll   rrrrr    | |ll        |
					// +-----------+ +---------------+ +----------+
					//                                       ^ lseam
					TextMatrix tm_left(print(nav.left(root)));
					size_t lseam_w = tm_left.r == tm_left.w ? 1 : 0;
					size_t lbranch_w = lseam_w + tm_left.w - tm_left.r;
					TextMatrix ans(tm_root.w + lseam_w + tm_left.w,
									tm_left.h + 2, lseam_w + tm_left.w,
									tm_root.w + lseam_w + tm_left.w);
					TextMatrix tm_lbranch = lbranch(lbranch_w);
					ans.m.push_back(std::string(tm_left.r, ' ') +
									tm_lbranch.m[0] + tm_root.m[0]);
					ans.m.push_back(std::string(tm_left.r, ' ') +
									tm_lbranch.m[1] +
									std::string(tm_root.w, ' '));
					for (size_t i = 0; i < tm_left.h; i++) {
						ans.m.push_back(tm_left.m[i] +
										std::string(tm_root.w + lseam_w, ' '));
					}
					return ans;
				} else {
					// Have both sub-trees
					TextMatrix tm_left(print(nav.left(root)));
					TextMatrix tm_right(print(nav.right(root)));
					size_t rseam_w = tm_right.l == 0 ? 1 : 0;
					size_t rbranch_w = rseam_w + tm_right.l;
					size_t lseam_w = tm_left.r == tm_left.w ? 1 : 0;
					size_t lbranch_w = lseam_w + tm_left.w - tm_left.r;
					TextMatrix tm_rbranch = rbranch(rbranch_w);
					TextMatrix tm_lbranch = lbranch(lbranch_w);
					TextMatrix ans(
						lseam_w + tm_left.w + tm_root.w + rseam_w + tm_right.w,
						std::max(tm_left.h, tm_right.h) + 2,
						lseam_w + tm_left.w, lseam_w + tm_left.w + tm_root.w);
					ans.m.push_back(
						std::string(tm_left.r, ' ') +
						tm_lbranch.m[0] + tm_root.m[0] + tm_rbranch.m[0] +
						std::string(tm_right.w - tm_right.l, ' '));
					ans.m.push_back(
						std::string(tm_left.r, ' ') +
						tm_lbranch.m[1] + std::string(tm_root.w, ' ') +
						tm_rbranch.m[1] +
						std::string(tm_right.w - tm_right.l, ' '));
					for (size_t i = 0; i < tm_left.h || i < tm_right.h; i++) {
						ans.m.push_back(
							(i < tm_left.h ? tm_left.m[i] :
											std::string(tm_left.w, ' ')) +
							std::string(lseam_w + tm_root.w + rseam_w, ' ') +
							(i < tm_right.h ? tm_right.m[i] :
											std::string(tm_right.w, ' '))
						);
					}
					return ans;
				}
			}
		}
		friend std::ostream& operator<<(std::ostream& os,
										TreePrinter<NodeType, Navigator> rhs) {
			if (rhs.nav.is_nil(rhs.root))
				return os << "(empty)" << std::endl;
			else
				return os << rhs.print(rhs.root);
		}
		NodeType root;
		Navigator nav;
};

template <typename NodeType, typename Navigator>
void TreePrint(NodeType root, Navigator nav) {
	std::cout << TreePrinter<NodeType, Navigator>(root, nav);
}

}

#endif
