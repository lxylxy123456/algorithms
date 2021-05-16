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

#include "DynamicTable.hpp"

#include <iostream>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	DynamicTable<int> DT;
	std::cout << "i / I: insert" << std::endl;
	std::cout << "q / Q: quit" << std::endl;
	while (true) {
		char c; int x;
		std::cout << "num = " << DT.num << ", size = " << DT.size << std::endl;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		switch (c) {
			case 'i':
			case 'I':
				std::cout << "x = ";
				std::cin >> x;
				DT.TableInsert(x);
				break;
			case 'd':
			case 'D':
				std::cout << DT.TableDelete() << std::endl;
				break;
			case 'q':
			case 'Q':
				return 0;
		}
	}
	return 0;
}
