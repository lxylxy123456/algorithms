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

#include "StorageManage.hpp"

#include <cassert>
#include <exception>
#include "utils.h"

using namespace algorithms;

int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 16);
	StorageManage<long int> S(n);
	std::vector<Data<long int>*> allocated;
	std::cout << "a: alloc" << std::endl;
	std::cout << "f: free" << std::endl;
	std::cout << "q: quit" << std::endl;
	while (true) {
		char c; int x; Data<long int>* ans;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		if (c == 'q')
			break;
		switch (c) {
			case 'a':
				ans = S.AllocateObject();
				allocated.push_back(ans);
				std::cout << static_cast<void*>(ans) << std::endl;
				break;
			case 'f':
				for (size_t i = 0; i < allocated.size(); i++)
					std::cout << "[" << i << "] = "
							 << static_cast<void*>(allocated[i]) << std::endl;
				std::cout << "x = ";
				std::cin >> x;
				S.FreeObject(allocated[x]);
				allocated.erase(allocated.begin() + x, allocated.begin() + x+1);
				break;
		}
	}
	return 0;
}
