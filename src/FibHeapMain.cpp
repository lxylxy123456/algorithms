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

#include "FibHeap.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "RedBlackTree.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	std::vector<FibHeap<int>> FH_list(get_argv<std::size_t>(argc, argv, 1, 10));
	FibHeap<int>* FH = &(FH_list[0]);
	std::cout << "s: select" << std::endl;
	std::cout << "i: insert" << std::endl;
	std::cout << "m: minimum" << std::endl;
	std::cout << "u: union" << std::endl;
	std::cout << "e: extract minimum" << std::endl;
	std::cout << "d: decrease key" << std::endl;
	std::cout << "D: delete" << std::endl;
	std::cout << "p: parent" << std::endl;
	std::cout << "c: child" << std::endl;
	std::cout << "l: left" << std::endl;
	std::cout << "r: right" << std::endl;
	std::cout << "P: print tree" << std::endl;
	std::cout << "q: quit" << std::endl;
	FNode<int>* ptr = nullptr;
	std::size_t n = 0;
	while (true) {
		char c; int x; std::size_t n2;
		std::cout << "n   = " << n << std::endl;
		std::cout << "ptr = " << pptr(ptr) << std::endl;
		if (ptr)
			std::cout << "    = " << ptr->key << std::endl;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		switch (c) {
			case 's':
				std::cout << "n = ";
				std::cin >> n;
				assert(n < FH_list.size());
				FH = &(FH_list[n]);
				ptr = FH->min;
				break;
			case 'i':
				std::cout << "x = ";
				std::cin >> x;
				ptr = FH->FibHeapInsert(x);
				break;
			case 'm':
				ptr = FH->FibHeapMinimum();
				break;
			case 'u':
				std::cout << "n = ";
				std::cin >> n2;
				FH->FibHeapUnion(FH_list[n2]);
				break;
			case 'e':
				ptr = FH->FibHeapExtractMin();
				if (ptr) {
					std::cout << "min = " << ptr->key << std::endl;
					delete ptr;
					ptr = FH->min;
				} else
					std::cout << "empty heap" << std::endl;
				break;
			case 'd':
				std::cout << "x = ";
				std::cin >> x;
				FH->FibHeapDecreaseKey(ptr, x);
				break;
			case 'D':
				FH->FibHeapDelete(ptr);
				ptr = FH->min;
				break;
			case 'p':
				ptr = ptr->p;
				break;
			case 'c':
				ptr = ptr->child;
				break;
			case 'l':
				ptr = ptr->left;
				break;
			case 'r':
				ptr = ptr->right;
				break;
			case 'P':
				FH->print_tree();
				break;
			case 'q':
				return 0;
		}
	}
	return 0;
}
