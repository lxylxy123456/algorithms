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

#include "Select.hpp"

#include <iostream>
#include <vector>

#include "InsertSort.hpp"
#include "RandomizedSelect.hpp"
#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	std::vector<int> a;
	const std::size_t n = get_argv(argc, argv, 1, 10);
	const std::size_t compute = get_argv(argc, argv, 2, 7);
	random_integers(a, 0, n - 1, n);

	std::size_t i = random_integer<int>(0, n - 1);
	std::vector<int> b(a);

	int ans1, ans2;

	output_integers(a);
	std::cout << i << std::endl;
	if (compute >> 0 & 1) {
		ans1 = RandomizedSelect(a, i);
		std::cout << ans1 << std::endl;
	}
	if (compute >> 1 & 1) {
		ans2 = Select(b, i);
		std::cout << ans2 << std::endl;
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (ans1 == ans2) << std::endl;
	}
	return 0;
}
