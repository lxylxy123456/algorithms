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

#include "IntervalTree.hpp"
#include "utils.hpp"

#include <cassert>

using namespace algorithms;

void sanity_check(IntervalTree<int>& BT, std::vector<Interval<int>>& its) {
	int n = its.size(), l = 0, u = n;
	std::sort(its.begin(), its.end());
	if (n) {
		l = its[0].low - 2;
		u = its[n - 1].high + 2;
		if (l > u)
			l = u + 1;
	}
	for (int i = l; i < u; i++) {
		bool expected = false;
		for (std::vector<Interval<int>>::iterator j = its.begin();
			j != its.end(); j++)
			expected = expected || *j == i;
		assert((BT.TreeSearch(Interval<int>(i)) == BT.nil) == !expected);
	}
	std::vector<CData<MData<int>>> in_order;
	BT.InorderTreeWalk(in_order);
	for (std::vector<CData<MData<int>>>::iterator i = in_order.begin();
		(i + 1) < in_order.end(); i++)
		assert(i->data.data.low <= (i + 1)->data.data.low);
	std::vector<int> test_data;
	random_integers(test_data, l, u, 2 * n);
	for (std::vector<int>::iterator i = test_data.begin(); i != test_data.end();
		i+=2) {
		Interval<int> it(std::min(*i, *(i + 1)), std::max(*i, *(i + 1)));
		Node<CData<MData<int>>>* searched = BT.TreeSearch(it);
		std::vector<Interval<int>>::iterator found;
		found = std::find(its.begin(), its.end(), it);
		assert((found != its.end()) == (searched != BT.nil));
	}
}

int test(int n) {
	IntervalTree<int> BT;
	std::vector<int> data;
	std::vector<Interval<int>> its;
	if (n) {
		random_integers(data, 0, 3 * n / 2, 2 * n);
		for (std::vector<int>::iterator i = data.begin(); i != data.end();
			i+=2) {
			Interval<int> it(std::min(*i, *(i + 1)), std::max(*i, *(i + 1)));
			its.push_back(it);
			BT.TreeInsert(it);
		}
	}
	BT.print_tree();
	sanity_check(BT, its);
	std::vector<int> rm;
	random_integers(rm, 0, 3 * n / 2, n * 4 + 4);
	for (std::vector<int>::iterator i = rm.begin(); i != rm.end(); i+=2) {
		Interval<int> it(std::min(*i, *(i + 1)), std::max(*i, *(i + 1)));
		std::cout << "rm " << it << std::endl;
		Node<CData<MData<int>>>* searched = BT.TreeSearch(it);
		if (searched != BT.nil) {
			std::vector<Interval<int>>::iterator found = its.end();
			for (found = its.begin(); found != its.end(); found++)
				if (found->low == searched->data.data.data.low &&
					found->high == searched->data.data.data.high)
					break;
			assert(found != its.end());
			BT.TreeDelete(searched);
			its.erase(found);
		}
		sanity_check(BT, its);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	std::cout << "seed = " << random_seed_get() << std::endl;
	test(0);
	test(1);
	test(4);
	test(16);
	test(47);
	test(100);
	std::cout << "\033[0m" << std::endl;
	return 0;
}
