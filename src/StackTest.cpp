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

#include "Stack.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "utils.hpp"

using namespace algorithms;

int test(int n) {
	std::cout << n << std::endl;
	Stack<int> S(n);
	for (int i = 0; i < n; i++) {
		assert(S.StackEmpty() == (i == 0));
		S.Push(i);
	}
	for (int i = n - 1; i >= 0; i--) {
		assert(!S.StackEmpty());
		assert(S.Pop() == i);
	}
	assert(S.StackEmpty());
	return 0;
}

int test2() {
	std::cout << "test2" << std::endl;
	Stack<int> S(5);
	S.Push(1);
	S.Push(2);
	S.Push(3);
	assert(S.Pop() == 3);
	S.Push(4);
	S.Push(5);
	assert(S.Pop() == 5);
	S.MultiPop(2);
	assert(S.Pop() == 1);
	assert(S.StackEmpty());
	S.Push(6);
	S.Push(7);
	S.Push(8);
	assert(S.Pop() == 8);
	S.Push(9);
	S.Push(10);
	assert(S.Pop() == 10);
	S.MultiPop(4);
	assert(S.StackEmpty());
	try {
		S.Pop();
		assert(false);
	} catch (std::invalid_argument& e) {
		assert(std::string(e.what()) == "underflow");
	}
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<int> ns{0, 1, 2, 5, 8, 19, 52, 100};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		test(*n);
	test2();
	return 0;
}
