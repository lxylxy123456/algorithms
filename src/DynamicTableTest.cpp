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

#include "DynamicTable.hpp"
#include "utils.hpp"

#include <cassert>
#include <vector>

using namespace algorithms;

int test(int n) {
	DynamicTable<int> DT;
	std::vector<int> cmd, v;
	random_integers<int>(cmd, -n, n, n);
	output_integers(cmd);
	for (std::vector<int>::iterator i = cmd.begin(); i < cmd.end(); i++) {
		if (*i > 0) {
			DT.TableInsert(*i);
			v.push_back(*i);
		} else {
			if (DT.num) {
				DT.TableDelete();
				v.pop_back();
			}
		}
		assert(DT.num == v.size());
		for (size_t i = 0; i < DT.num; i++)
			assert((*DT.table)[i] == v[i]);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<int> ns = {1, 4, 16, 19, 20, 25, 100};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		test(*n);
	return 0;
}
