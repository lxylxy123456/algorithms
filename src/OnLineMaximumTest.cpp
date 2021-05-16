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

#include "OnLineMaximum.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

bool test_once(std::size_t n, std::size_t k) {
	std::vector<int> c;
	random_integers(c, 0, n * 10 - 1, n);
	output_integers(c);
	int ans = OnLineMaximum(c, k);
	int max = std::max_element(c.begin(), c.end()) - c.begin();
	std::cout << ans << '\t' << c[ans] << std::endl;
	std::cout << max << '\t' << c[max] << std::endl;
	return ans == max;
}

bool test(std::size_t n, std::size_t k, std::size_t t) {
	std::size_t success = 0, total = 0;
	while (true) {
		total++;
		if (test_once(n, k))
			success++;
		// The probability should be at least 1/e. Using 1/3 here.
		std::cout << "t=" << total << " s=" << success << std::endl;
		if (total >= t && success * 3 >= total)
			break;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	test(27, 10, 1000);
	test(271, 100, 1000);
	test(2718, 1000, 100);
	return 0;
}
