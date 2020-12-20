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

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "utils.hpp"
#include "print_ptr.hpp"

using namespace algorithms;

class A {
	public:
		A(int data): data(data) {}
		int data;
};

int main(int argc, char *argv[]) {
	{
		A *a1 = nullptr, *a2 = new A(10);
		print_ptr(a1, (A*) nullptr);
		print_ptr(a2, (A*) nullptr);
		std::cout << pptr(a1) << '\t' << pptr(a2) << std::endl;
		delete a2;
	}
	return 0;
}
