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

#include "ModularExponentiation.hpp"
#include "utils.hpp"

#include <cassert>

using namespace algorithms;

template <typename T>
int test(T a, T b, T n) {
	T ans = ModularExponentiation(a, b, n);
	std::cout << a << " ** " << b << " % " << n << " = " << ans << std::endl;
	T ans2 = 1;
	for (T i = 0; i < b; i++)
		ans2 = (ans2 * a) % n;
	assert(ans == ans2);
	return 0;
}

int main(int argc, char *argv[]) {
	for (int n = 2; n <= 46340; n += 10)
		test(random_integer<int>(1, n),
			random_integer<int>(1, n),
			random_integer<int>(1, n));
	for (long int n = 2; n <= 30370004; n += 300000)
		test(random_integer<long int>(1, n),
			random_integer<long int>(1, n),
			random_integer<long int>(1, n));
	for (long int n = 2; n <= 30370004; n += 300000)
		test(random_integer<long long int>(1, n),
			random_integer<long long int>(1, n),
			random_integer<long long int>(1, n));
	return 0;
}
