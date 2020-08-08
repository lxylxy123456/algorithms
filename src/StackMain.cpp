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

#include "Stack.hpp"

#include <exception>
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 16);
	Stack<int> S(n);
	std::cout << "e / E: test empty" << std::endl;
	std::cout << "p / u: push" << std::endl;
	std::cout << "P / o: pop" << std::endl;
	std::cout << "m / M: multi pop" << std::endl;
	std::cout << "q / Q: quit" << std::endl;
	while (true) {
		char c; int x;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		switch (c) {
			case 'e':
			case 'E':
				std::cout << std::boolalpha << S.StackEmpty() << std::endl;
				break;
			case 'p':
			case 'u':
				std::cout << "x = ";
				std::cin >> x;
				S.Push(x);
				break;
			case 'P':
			case 'o':
				std::cout << S.Pop() << std::endl;
				break;
			case 'm':
			case 'M':
				std::cout << "k = ";
				std::cin >> x;
				S.MultiPop(x);
				break;
			case 'q':
			case 'Q':
				return 0;
		}
	}
	return 0;
}
