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

#include "RedBlackTree.hpp"

#include "utils.hpp"
#include "BinarySearchTree.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	size_t n = get_argv(argc, argv, 1, 0);
	RedBlackTree<int> RB;
	if (n) {
		std::vector<int> a;
		random_integers(a, 0, n - 1, n);
		for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			RB.RBInsert(*i);
	}
	tree_interact<RedBlackTree<int>, CData<int>, int>(RB, "", tf);
	return 0;
}
