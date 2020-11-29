//
//  algorithm - some algorithms in "Introduction to Algorithms", third edition
//  Copyright (C) 2020  lxylxy123456
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
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "utils.hpp"

using namespace algorithms;

int test(size_t n) {
	std::cout << n << std::endl;
	StorageManage<long int> S(n);
	std::vector<Data<long int>*> allocated;
	std::uniform_int_distribution<size_t> d1(0, 5);
	std::uniform_int_distribution<size_t> d2(0, n * 5);
	for (size_t i = 0; i < (n + 5) * 5; i++) {
		if (random_integer(d1) < 3) {
			if (allocated.size() < n) {
				Data<long int>* ans = S.AllocateObject();
				allocated.push_back(ans);
				std::cout << "a, " << static_cast<void*>(ans) << std::endl;
			} else {
				std::cout << "a" << std::endl;
				try {
					S.AllocateObject();
				} catch (std::invalid_argument& e) {
					assert(std::string(e.what()) == "out of space");
				}
			}
		} else {
			if (!allocated.size())
				continue;
			size_t x = random_integer(d2) % allocated.size();
			std::cout << "f, " << static_cast<void*>(allocated[x]) << std::endl;
			S.FreeObject(allocated[x]);
			allocated.erase(allocated.begin() + x, allocated.begin() + x + 1);
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<size_t> ns{1, 2, 5, 8, 19, 52, 100};
	for (std::vector<size_t>::iterator n = ns.begin(); n < ns.end(); n++)
		test(*n);
	return 0;
}
