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

#include "MaxHeap.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "test_utils.hpp"
#include "utils.hpp"

using namespace algorithms;

const std::vector<int> ans1 = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
const std::vector<int> ans2 = {14, 8, 10, 4, 7, 9, 3, 2, 1};
const std::vector<int> ans3 = {19, 14, 10, 8, 7, 9, 3, 2, 4};
const std::vector<int> ans4 = {19, 14, 10, 11, 7, 9, 3, 2, 8};

template <typename T>
bool is_increasing_order(T p, T r) {
	if (p == r)
		return true;
	for (T i = p, j = p + 1; j < r; j++)
		if (*i > *j)
			return false;
	return true;
}

int test(int test_number, int n) {
	std::vector<int> data = {4, 16, 10, 14, 7, 9, 3, 2, 8, 1};
	Heap<int> a(data, data.size()), b;
	PriorityQueue<int> c;
	switch(test_number) {
		case 1:	// test MaxHeapify
			output_integers(a);
			a.MaxHeapify(0);
			output_integers(a);
			assert(a == ans1);
			break;
		case 2: // test BuildMaxHeap and HeapSort
			random_integers(b, 0, n - 1, n);
			output_integers(b);
			b.BuildMaxHeap();
			output_integers(b);
			b.HeapSort();
			output_integers(b);
			assert(is_increasing_order(b.begin(), b.end()));
			break;
		case 3:	// test PriorityQueue
			for (auto i : data) {
				c.push_back(i);
				c.MaxHeapInsert(i);
			}
			output_integers(c);
			assert(c == ans1);
			assert(c.HeapMaximum() == 16);
			assert(c.HeapExtractMax() == 16);
			c.pop_back();
			output_integers(c);
			assert(c == ans2);
			c.HeapIncreaseKey(c.heap_size - 1, 19);
			output_integers(c);
			assert(c == ans3);
			c.HeapIncreaseKey(c.heap_size - 1, 11);
			output_integers(c);
			assert(c == ans4);
			break;
		case 4: // test BuildMaxHeap_prime
			random_integers(b, 0, n - 1, n);
			output_integers(b);
			c = PriorityQueue<int>(b);
			b.BuildMaxHeap();
			c.BuildMaxHeap_prime();
			output_integers(b);
			output_integers(c);
			b.HeapSort();
			output_integers(b);
			assert(is_increasing_order(b.begin(), b.end()));
			c.HeapSort();
			output_integers(c);
			assert(is_increasing_order(c.begin(), c.end()));
			break;
		default:
			std::cout << "No Action" << std::endl;
			break;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	test(1, 0);
	test(3, 0);
	for (int i = 1; i < 100; i = (i + 1) * 2) {
		test(2, i);
		test(4, i);
	}
	return 0;
}
