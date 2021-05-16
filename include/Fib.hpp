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

#ifndef ALGORITHMS_FIB
#define ALGORITHMS_FIB

#include <thread>

using std::size_t;

namespace algorithms {

size_t Fib(size_t n) {
	if (n <= 1)
		return n;
	else {
		size_t x = Fib(n - 1);
		size_t y = Fib(n - 2);
		return x + y;
	}
}

void PFib(size_t n, size_t* ret) {
	if (n <= 1)
		*ret = n;
	else {
		size_t x, y;
		std::thread t1(PFib, n - 1, &x);
		PFib(n - 2, &y);
		t1.join();
		*ret = x + y;
	}
}

size_t PFib(size_t n) {
	size_t ret;
	PFib(n, &ret);
	return ret;
}

}

#endif
