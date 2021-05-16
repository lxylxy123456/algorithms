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

#include "BTree.hpp"

#include <iostream>
#include <map>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	size_t t = get_argv(argc, argv, 1, 3);
	debug = get_argv(argc, argv, 2, 1);
	BTree<int> BT(t);
	std::cout << "s / S: search" << std::endl;
	std::cout << "i / I: insert" << std::endl;
	std::cout << "d / D: delete" << std::endl;
	std::cout << "p / P: print tree (two styles)" << std::endl;
	std::cout << "q / Q: quit" << std::endl;
	// Generate tree in Page 498, Figure 18.7 (a):
	// 	i10 i11 i13 i14 i15 i1 i3 i7 i4 i5 i16 i18 i19 i24 i25 i26 i20 i21 i22
	// In Figure 18.7: i2 i17 i12 i6
	// In Figure 18.8: d6 d13 d7 d4 d2
	while (true) {
		char c; int x; std::pair<BNode<int>*, size_t> search_ans;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		switch (c) {
			case 's':
			case 'S':
				std::cout << "x = ";
				std::cin >> x;
				search_ans = BT.BTreeSearch(x);
				std::cout << static_cast<void*>(search_ans.first) << ", ";
				std::cout << search_ans.second << std::endl;
				break;
			case 'i':
			case 'I':
				std::cout << "x = ";
				std::cin >> x;
				BT.BTreeInsert(x);
				break;
			case 'd':
			case 'D':
				std::cout << "x = ";
				std::cin >> x;
				std::cout << std::boolalpha << BT.BTreeDelete(x) << std::endl;
				break;
			case 'p':
				BT.print_tree(true);
				break;
			case 'P':
				BT.print_tree(false);
				break;
			case 'q':
			case 'Q':
				return 0;
		}
	}
	return 0;
}
