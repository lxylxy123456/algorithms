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

#include "MillerRabin.hpp"
#include "utils.hpp"

#include <cassert>

using namespace algorithms;

template <typename T>
int test(T n) {
	std::cout << n << std::endl;
	int tries = 10;
	bool ans = MillerRabin(n, tries);
	bool ans2 = (n % 2 != 0);
	for (T i = 3; i * i <= n; i += 2)
		if (n % i == 0) {
			ans2 = false;
			break;
		}
	if (ans != ans2) {
		do {
			assert(ans && !ans2);
			tries *= 10;
			if (tries <= 0)
				tries = tries % 10 + 1;
			ans = MillerRabin(n, tries);
		} while(ans != ans2);
	}
	return 0;
}

#include <climits>
int main(int argc, char *argv[]) {
	int total = 0, count = 0;
	for (int n = 2; n <= 23170; n += 10) {
		count += test(random_integer<int>(1, n) * 2 + 1);
		total++;
	}
	for (long int n = 2; n <= 303700049; n += 300000) {
		count += test(random_integer<long int>(1, n) * 2 + 1);
		total++;
	}
	for (long int n = 2; n <= 303700049; n += 300000) {
		count += test(random_integer<long long int>(1, n) * 2 + 1);
		total++;
	}
	assert((double) count / total < 0.0055);
	return 0;
}
