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

#include "Minimum.hpp"
#include "utils.hpp"

#include <cassert>

using namespace algorithms;

int test(int n) {
	std::vector<int> a;
	random_integers(a, 0, n - 1, n);
	output_integers(a);
	std::vector<Value> A;
	A.reserve(n);
	for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++)
		A.push_back(*i);
	Value min1, max1, min2, max2;
	min1 = Minimum(A);
	assert(Value::get_cmp_num() == n - 1);
	max1 = Maximum(A);
	assert(Value::get_cmp_num() == n - 1);
	MinMax(A, min2, max2);
	assert(Value::get_cmp_num() <= n / 2 * 3);
	std::cout << min1 << '\t' << max1 << std::endl;
	std::cout << min2 << '\t' << max2 << std::endl;
	assert(min1 == min2 && max1 == max2);
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<int> ns{1, 2, 5, 8, 19, 52, 100};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		test(*n);
	return 0;
}
