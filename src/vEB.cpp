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

#include "vEB.hpp"

#include "utils.h"

using namespace algorithms;

void print(size_t x) {
	if (x == NIL)
		std::cout << "NIL" << std::endl;
	else
		std::cout << x << std::endl;
}

void print(bool x) {
	std::cout << std::boolalpha << x << std::endl;
}

int main(int argc, char *argv[]) {
	const size_t k = get_argv(argc, argv, 1, 16);
	if (k > 16)
		throw std::invalid_argument("k too large");
	vEB Pv(k);
	std::cout << "m: member" << std::endl;
	std::cout << "-: minimum" << std::endl;
	std::cout << "+: maximum" << std::endl;
	std::cout << "p: predecessor" << std::endl;
	std::cout << "s: successor" << std::endl;
	std::cout << "i: insert" << std::endl;
	std::cout << "d: delete" << std::endl;
	std::cout << "P: print all" << std::endl;
	std::cout << "q: quit" << std::endl;
	while (true) {
		char c; size_t x; std::vector<size_t> l;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		switch (c) {
			case 'm':
				std::cout << "x = ";
				std::cin >> x;
				print(Pv.vEBTreeMember(x));
				break;
			case '-':
				print(Pv.vEBTreeMinimum());
				break;
			case '+':
				print(Pv.vEBTreeMaximum());
				break;
			case 'p':
				std::cout << "x = ";
				std::cin >> x;
				print(Pv.vEBTreePredecessor(x));
				break;
			case 's':
				std::cout << "x = ";
				std::cin >> x;
				print(Pv.vEBTreeSuccessor(x));
				break;
			case 'i':
				std::cout << "x = ";
				std::cin >> x;
				Pv.vEBTreeInsert(x);
				break;
			case 'd':
				std::cout << "x = ";
				std::cin >> x;
				Pv.vEBTreeDelete(x);
				break;
			case 'P':
				for (size_t i = 0; i < Pv.u; i++)
					if (Pv.vEBTreeMember(i))
						l.push_back(i);
				output_integers(l);
				break;
			case 'q':
				return 0;
		}
	}
	return 0;
}
