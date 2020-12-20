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

#include "Queue.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

int test(int n) {
	std::cout << n << std::endl;
	Queue<int> S(n);
	for (int i = 1; i < n; i++) {
		assert(S.Empty() == (i == 1));
		S.Enqueue(i);
	}
	for (int i = 1; i < n; i++) {
		assert(!S.Empty());
		assert(S.Dequeue() == i);
	}
	assert(S.Empty());
	return 0;
}

int test2() {
	std::cout << "test2" << std::endl;
	Queue<int> S(5);
	S.Enqueue(1);
	S.Enqueue(2);
	S.Enqueue(3);
	assert(S.Dequeue() == 1);
	S.Enqueue(4);
	S.Enqueue(5);
	assert(S.Dequeue() == 2);
	assert(S.Dequeue() == 3);
	assert(S.Dequeue() == 4);
	assert(S.Dequeue() == 5);
	try {
		S.Dequeue();
		assert(false);
	} catch (std::invalid_argument& e) {
		assert(std::string(e.what()) == "underflow");
	}
	for (int i = 0; i < 4; i++)
		S.Enqueue(i);
	try {
		S.Enqueue(4);
		assert(false);
	} catch (std::invalid_argument& e) {
		assert(std::string(e.what()) == "overflow");
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<int> ns{0, 1, 2, 5, 8, 19, 52, 100};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		test(*n);
	test2();
	return 0;
}
