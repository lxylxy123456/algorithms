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

#include "LCSLength.hpp"

#include <cassert>
#include <sstream>
#include <string>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

bool is_substr(std::vector<char>& sub, std::vector<char>& ori) {
	std::vector<char>::iterator j = sub.begin();
	for (std::vector<char>::iterator i = ori.begin(); i < ori.end(); i++)
		if (j != sub.end() && *i == *j)
			j++;
	return j == sub.end();
}

int test(std::size_t x, std::size_t y, std::size_t n) {
	std::vector<char> X, Y;
	random_integers<char>(X, 'a', 'a' + n, x);
	random_integers<char>(Y, 'a', 'a' + n, y);
	output_integers(X, "");
	output_integers(Y, "");
	std::vector<VECT_SIZT> c = LCSLength(X, Y);
	std::ostringstream os;
	PrintLCS(c, X, x, y, os);
	std::string z = os.str();
	std::vector<char> Z(z.begin(), z.end());
	assert(is_substr(Z, X));
	assert(is_substr(Z, Y));
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	std::vector<int> xys = {1, 4, 16, 19, 20, 47, 100};
	std::vector<int> ns = {0, 1, 4, 16, 19, 20, 25};
	for (std::vector<int>::iterator x = xys.begin(); x < xys.end(); x++)
		for (std::vector<int>::iterator y = xys.begin(); y < xys.end(); y++)
			for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
				test(*x, *y, *n);
	return 0;
}
