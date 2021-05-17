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

#include "ChainedHash.hpp"

#include <iostream>

#include "LinkedList.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t n = get_argv(argc, argv, 1, 16);
	ChainedHash<int> D(n);
	std::cout << "d: delete" << std::endl;
	std::cout << "i: insert" << std::endl;
	std::cout << "s: search" << std::endl;
	std::cout << "q: quit" << std::endl;
	while (true) {
		char c; std::size_t k; int v;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		if (c == 'q')
			break;
		std::cout << "k = ";
		std::cin >> k;
		switch (c) {
			case 'i':
				std::cout << "v = ";
				std::cin >> v;
				D.ChainedHashInsert(k, v);
				break;
			case 'd':
				D.ChainedHashDelete(D.ChainedHashSearch(k));
				break;
			case 's':
				Element<Pair<int>>* ans = D.ChainedHashSearch(k);
				if (ans)
					std::cout << ans->key.key << ": "
							 << ans->key.value << std::endl;
				else
					std::cout << "nullptr" << std::endl;
				break;
		}
	}
	return 0;
}
