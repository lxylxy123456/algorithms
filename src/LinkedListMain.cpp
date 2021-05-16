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

#include "LinkedList.hpp"

#include <iostream>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t n = get_argv(argc, argv, 1, 0);
	LinkedListBase<int>* S;
	if (n)
		S = new LinkedList_prime<int>;
	else
		S = new LinkedList<int>;
	std::cout << "d: delete" << std::endl;
	std::cout << "i: insert" << std::endl;
	std::cout << "s: search" << std::endl;
	std::cout << "q: quit" << std::endl;
	while (true) {
		char c; int x;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		if (c == 'q')
			break;
		std::cout << "x = ";
		std::cin >> x;
		switch (c) {
			case 'i':
				S->ListInsert(x);
				break;
			case 'd':
				S->ListDelete(S->ListSearch(x));
				break;
			case 's':
				std::cout << pptr(S->ListSearch(x)) << std::endl;
				break;
		}
	}
	delete S;
	return 0;
}
