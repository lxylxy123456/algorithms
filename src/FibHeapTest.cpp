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

#include "FibHeap.hpp"
#include "utils.hpp"

#include <cassert>

using namespace algorithms;

template <typename T>
FNode<T>* fnode_find(FNode<T>* root, T key) {
	for (FNode<T>* i = root; i; ) {
		if (i->key == key)
			return i;
		FNode<T>* ans = fnode_find(i->child, key);
		if (ans)
			return ans;
		i = i->left;
		if (i == root)
			break;
	}
	return nullptr;
}

int test(int n, int m) {
	std::vector<FibHeap<int>> FH_list(m);
	std::vector<std::vector<int>> V_list(m);
	std::vector<int> actions;
	std::vector<int> indices;
	random_integers(actions, 0, 5, n);
	random_integers(indices, 0, m - 1, n);
	output_integers(actions);
	output_integers(indices);
	for (int i = 0; i < n; i++) {
		FibHeap<int>& FH = FH_list[indices[i]];
		std::vector<int>& V = V_list[indices[i]];
		int x, y;
		FNode<int>* ptr;
		std::vector<int>::iterator itr;
		switch(actions[i]) {
		case 0:	// FibHeapInsert
			x = random_integer<int>(0, n);
			FH.FibHeapInsert(x);
			V.push_back(x);
			break;
		case 1:	// FibHeapMinimum
			ptr = FH.FibHeapMinimum();
			if (ptr) {
				x = ptr->key;
				y = *std::min_element(V.begin(), V.end());
				assert(x == y);
			} else {
				assert(!V.size());
			}
			break;
		case 2:	// FibHeapUnion
			assert(m > 1);
			x = random_integer(0, m - 2);
			if (x >= indices[i])
				x++;
			FH.FibHeapUnion(FH_list[x]);
			V.insert(V.end(), V_list[x].begin(), V_list[x].end());
			V_list[x].clear();
			break;
		case 3:	// FibHeapExtractMin
			ptr = FH.FibHeapExtractMin();
			if (ptr) {
				x = ptr->key;
				itr = std::min_element(V.begin(), V.end());
				y = *itr;
				assert(x == y);
				delete ptr;
				V.erase(itr);
			} else {
				assert(!V.size());
			}
			break;
		case 4:	// FibHeapDecreaseKey
			if (V.size()) {
				itr = V.begin() + random_integer<size_t>(0, V.size() - 1);
				ptr = fnode_find(FH.min, *itr);
				assert(ptr);
				if (*itr > 0) {
					x = random_integer(0, *itr - 1);
					V.erase(itr);
					V.push_back(x);
					FH.FibHeapDecreaseKey(ptr, x);
				}
			} else
				assert(FH.n == 0);
			break;
		case 5:	// FibHeapDelete
			if (V.size()) {
				itr = V.begin() + random_integer<size_t>(0, V.size() - 1);
				ptr = fnode_find(FH.min, *itr);
				assert(ptr);
				V.erase(itr);
				FH.FibHeapDelete(ptr);
			} else
				assert(FH.n == 0);
			break;
		default:
			assert(0);
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<int> ns = {20000, 25000, 100000};
	std::vector<int> ms = {2, 4, 5, 10};
	for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
		for (std::vector<int>::iterator m = ms.begin(); m < ms.end(); m++)
			test(*n, *m);
	return 0;
}
