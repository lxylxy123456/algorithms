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

#ifndef MAIN
#define MAIN
#define MAIN_Fib
#endif

#ifndef FUNC_Fib
#define FUNC_Fib

#include <thread>
#include "utils.h"

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
#endif

#ifdef MAIN_Fib
int main(int argc, char *argv[]) {
	std::cout << "n\ta\tb\ta == b" << std::endl;
	for (int i = 1; i < std::max(argc, 2); i++) {
		size_t n = get_argv(argc, argv, i, 10);
		size_t a = Fib(n);
		std::cout << n << '\t' << a << '\t' << std::flush;
		size_t b = PFib(n);
		std::cout << b << '\t';
		std::cout << std::boolalpha << (a == b) << std::endl;
	}
	return 0;
}
#endif

