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

#include "BTree.hpp"
#include "utils.hpp"

#include <cassert>

using namespace algorithms;

template <typename T>
void btree_walk(BNode<T>* x, std::vector<int>& ans) {
	for (size_t i = 0; i <= x->n; i++) {
		if (!x->leaf)
			btree_walk(x->c[i], ans);
		if (i == x->n)
			break;
		ans.push_back(x->key[i]);
	}
}

void btree_walk(BTree<int>& BT, std::vector<int>& ans) {
	if (!BT.size)
		return;
	btree_walk(BT.root, ans);
}

void sanity_check(BTree<int>& BT, std::vector<int>& data) {
	int n = data.size(), l = 0, u = n;
	if (n) {
		l = data[0] - 2;
		u = data[n - 1] + 2;
	}
	assert(BT.size == data.size());
	std::vector<int> in_order;
	btree_walk(BT, in_order);
	std::sort(data.begin(), data.end());
	assert(data == in_order);
	for (int i = l; i < u; i++) {
		bool expected = false;
		for (std::vector<int>::iterator j = data.begin(); j != data.end(); j++)
			expected = expected || *j == i;
		assert((BT.BTreeSearch(i).first == nullptr) == !expected);
	}
}

int test(size_t n, size_t k) {
	std::cout << "n = " << n << "; k = " << k << std::endl;
	BTree<int> BT(k);
	std::vector<int> data;
	if (n) {
		random_integers(data, 0, 3 * n / 2, n);
		for (std::vector<int>::iterator i = data.begin(); i != data.end(); i++)
			BT.BTreeInsert(*i);
	}
	BT.print_tree(true);
	sanity_check(BT, data);
	std::vector<int> rm;
	random_integers(rm, 0, 3 * n / 2, n * 2 + 2);
	for (std::vector<int>::iterator i = rm.begin(); i != rm.end(); i++) {
		std::cout << "rm " << *i << std::endl;
		std::pair<BNode<int>*, size_t> searched = BT.BTreeSearch(*i);
		if (searched.first != nullptr) {
			BT.BTreeDelete(*i);
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
	std::cout << random_seed_get() << std::endl;
	std::vector<int> ns = {1, 4, 16, 19, 20, 25, 100};
	std::vector<int> ks = {3, 4, 5, 6, 7, 8};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<int>::iterator k = ks.begin(); k < ks.end(); k++)
			test(*n, *k);
	return 0;
}
