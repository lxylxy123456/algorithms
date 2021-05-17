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

#include "ProtovEB.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "utils.hpp"

using namespace algorithms;

void print(std::size_t x) {
	if (x == NIL)
		std::cout << "NIL" << std::endl;
	else
		std::cout << x << std::endl;
}

void print(bool x) {
	std::cout << std::boolalpha << x << std::endl;
}

int main(int argc, char *argv[]) {
	const std::size_t k = get_argv(argc, argv, 1, 4);
	if (k > 4)
		throw std::invalid_argument("k too large");
	ProtovEB Pv(k);
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
		char c; std::size_t x; std::vector<std::size_t> l;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		switch (c) {
			case 'm':
				std::cout << "x = ";
				std::cin >> x;
				print(Pv.ProtovEBMember(x));
				break;
			case '-':
				print(Pv.ProtovEBMinimum());
				break;
			case '+':
				print(Pv.ProtovEBMaximum());
				break;
			case 'p':
				std::cout << "x = ";
				std::cin >> x;
				print(Pv.ProtovEBPredecessor(x));
				break;
			case 's':
				std::cout << "x = ";
				std::cin >> x;
				print(Pv.ProtovEBSuccessor(x));
				break;
			case 'i':
				std::cout << "x = ";
				std::cin >> x;
				Pv.ProtovEBInsert(x);
				break;
			case 'd':
				std::cout << "x = ";
				std::cin >> x;
				Pv.ProtovEBDelete(x);
				break;
			case 'P':
				for (std::size_t i = 0; i < Pv.u; i++)
					if (Pv.ProtovEBMember(i))
						l.push_back(i);
				output_integers(l);
				break;
			case 'q':
				return 0;
		}
	}
	return 0;
}
