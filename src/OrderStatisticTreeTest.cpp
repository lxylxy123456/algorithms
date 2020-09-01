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

#include "OrderStatisticTree.hpp"
#include "utils.hpp"

#include <cassert>

using namespace algorithms;

void sanity_check(OrderStatisticTree<int>& BT, std::vector<int>& data) {
	int n = data.size(), l = 0, u = n;
	if (n) {
		l = data[0] - 2;
		u = data[n - 1] + 2;
	}
	for (int i = l; i < u; i++) {
		bool expected = false;
		for (std::vector<int>::iterator j = data.begin(); j != data.end(); j++)
			expected = expected || *j == i;
		assert((BT.TreeSearch(i) == BT.nil) == !expected);
	}
	std::sort(data.begin(), data.end());
	std::vector<CData<SData<int>>> in_order_cdata;
	BT.InorderTreeWalk(in_order_cdata);
	std::vector<int> in_order;
	for (std::vector<CData<SData<int>>>::iterator i = in_order_cdata.begin();
		i < in_order_cdata.end(); i++)
		in_order.push_back(i->data.data);
	assert(data == in_order);
	for (size_t i = 0; i < data.size(); i++) {
		Node<CData<SData<int>>>* selected = BT.OSSelect(i);
		assert(selected->data.data == data[i]);
		assert(BT.OSRank(selected) == i);
	}
}

int test(int n) {
	OrderStatisticTree<int> BT;
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
		Node<CData<SData<int>>>* searched = BT.TreeSearch(*i);
		if (searched != BT.nil) {
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
	test(0);
	test(1);
	test(4);
	test(16);
	test(47);
	test(100);
	return 0;
}
