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

#include "RandomPermute.hpp"
#include "utils.hpp"

#include <cassert>

using namespace algorithms;

int test(size_t n) {
	while (true) {
		std::vector<int> o;
		for (size_t i = 0; i < n; i++)
			o.push_back(i);
		std::vector<int> a(o), b(o);
		PermuteBySorting(a);
		RandomizeInPlace(b);
		output_integers(o);
		output_integers(a);
		output_integers(b);
		assert(o.size() == a.size());
		assert(o.size() == b.size());
		bool flag_oa = false, flag_ob = false, flag_ab = false;
		for (size_t i = 0; i < n; i++) {
			flag_oa = flag_oa || (o[i] != a[i]);
			flag_ob = flag_ob || (o[i] != b[i]);
			flag_ab = flag_ab || (a[i] != b[i]);
		}
		if (n > 2 && (!flag_oa || !flag_ob || !flag_ab))
			continue;
		break;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	test(0);
	test(1);
	test(2);
	test(5);
	test(10);
	test(49);
	test(100);
	return 0;
}
