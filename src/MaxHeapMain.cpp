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

#include "MaxHeap.hpp"

#include "utils.h"

using namespace algorithms;

int main(int argc, char *argv[]) {
	std::vector<int> data = {4, 16, 10, 14, 7, 9, 3, 2, 8, 1};
	Heap<int> a(data), b;
	PriorityQueue<int> c;
	int n = get_argv(argc, argv, 2, 16);
	switch(get_argv(argc, argv, 1, 0)) {
		case 1:	// test MaxHeapify
			output_integers(a);
			a.MaxHeapify(0);
			output_integers(a);
			break;
		case 2: // test BuildMaxHeap and HeapSort
			random_integers(b, 0, n - 1, n);
			output_integers(b);
			b.BuildMaxHeap();
			output_integers(b);
			b.HeapSort();
			output_integers(b);
			break;
		case 3:	// test PriorityQueue
			for (auto i : data) {
				c.push_back(i);
				c.MaxHeapInsert(i);
			}
			output_integers(c);
			std::cout << "Max == " << c.HeapMaximum() << " == ";
			std::cout << c.HeapExtractMax() << std::endl;
			c.pop_back();
			output_integers(c);
			c.HeapIncreaseKey(c.heap_size - 1, 19);
			output_integers(c);
			c.HeapIncreaseKey(c.heap_size - 1, 11);
			output_integers(c);
			break;
		case 4: // test BuildMaxHeap_prime
			random_integers(b, 0, n - 1, n);
			output_integers(b);
			c = PriorityQueue<int>(b);
			b.BuildMaxHeap();
			c.BuildMaxHeap_prime();
			output_integers(b);
			output_integers(c);
			break;
		default:
			std::cout << "No Action" << std::endl;
			break;
	}
	return 0;
}
