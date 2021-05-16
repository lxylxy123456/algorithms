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

#include "InsertSort.hpp"

#include <vector>

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	std::vector<int> a;
	int n = get_argv(argc, argv, 1, 10);
	random_integers(a, 0, n - 1, n);
	InsertSort(a);
	output_integers(a);
	return 0;
}
