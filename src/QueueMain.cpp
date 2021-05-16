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

#include "Queue.hpp"

#include <iostream>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const std::size_t n = get_argv(argc, argv, 1, 16);
	Queue<int> S(n);
	std::cout << "d: dequeue" << std::endl;
	std::cout << "e: enqueue" << std::endl;
	std::cout << "E: empty" << std::endl;
	std::cout << "q: quit" << std::endl;
	while (true) {
		char c; int x;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		switch (c) {
			case 'e':
				std::cout << "x = ";
				std::cin >> x;
				S.Enqueue(x);
				break;
			case 'd':
				std::cout << S.Dequeue() << std::endl;
				break;
			case 'E':
				std::cout << std::boolalpha << S.Empty() << std::endl;
				break;
			case 'q':
				return 0;
		}
	}
	return 0;
}
