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

#include "BinarySearchTree.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

void sanity_check(BinarySearchTree<int>& BT, std::vector<int>& data) {
	int n = data.size(), l = 0, u = n;
	if (n) {
		l = data[0] - 2;
		u = data[n - 1] + 2;
	}
	for (int i = l; i < u; i++) {
		bool expected = false;
		for (std::vector<int>::iterator j = data.begin(); j != data.end(); j++)
			expected = expected || *j == i;
		assert(!BT.TreeSearch(i) == !expected);
		assert(BT.TreeSearch(i) == BT.IterativeTreeSearch(i));
	}
	std::sort(data.begin(), data.end());
	std::vector<int> in_order;
	BT.InorderTreeWalk(in_order);
	assert(data == in_order);
	if (n) {
		assert(BT.TreeMinimum()->data == data[0]);
		assert(BT.TreeMaximum()->data == data[data.size() - 1]);
		std::vector<int> successors, predecessors;
		for (Node<int>* i = BT.TreeMinimum(); i; i = BT.TreeSuccessor(i))
			successors.push_back(i->data);
		assert(successors == data);
		for (Node<int>* i = BT.TreeMaximum(); i; i = BT.TreePredecessor(i))
			predecessors.push_back(i->data);
		std::vector<int> rev_pred(predecessors.rbegin(), predecessors.rend());
		assert(rev_pred == data);
	}
}

int test(int n) {
	BinarySearchTree<int> BT;
	std::vector<int> data;
	if (n) {
		random_integers(data, 0, 3 * n / 2, n);
		for (std::vector<int>::iterator i = data.begin(); i != data.end(); i++)
			BT.TreeInsert(*i);
	}
	BT.print_tree();
	sanity_check(BT, data);
	std::vector<int> rm;
	random_integers(rm, 0, 3 * n / 2, n * 2 + 2);
	for (std::vector<int>::iterator i = rm.begin(); i != rm.end(); i++) {
		std::cout << "rm " << *i << std::endl;
		Node<int>* searched = BT.TreeSearch(*i);
		if (searched) {
			BT.TreeDelete(searched);
			std::vector<int>::iterator found;
			found = std::find(data.begin(), data.end(), *i);
			assert(found != data.end());
			data.erase(found);
		}
		sanity_check(BT, data);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	test(0);
	test(1);
	test(4);
	test(16);
	test(47);
	test(100);
	return 0;
}
