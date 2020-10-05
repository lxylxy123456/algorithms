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

#include "vEB.hpp"
#include "utils.hpp"

#include "RedBlackTree.hpp"
#include <cassert>

using namespace algorithms;

int test(int k, int n) {
	vEB v(k);
	RedBlackTree<size_t> t;
	std::vector<int> actions;
	std::vector<size_t> values;
	random_integers(actions, 0, 6, n);
	random_integers(values, 0lu, v.u - 1, n);
	output_integers(actions);
	output_integers(values);
	for (int i = 0; i < n; i++) {
		size_t x = values[i], y;
		Node<CData<size_t>>* n;
		switch(actions[i]) {
		case 0:	// vEBTreeMember
			assert(v.vEBTreeMember(x) == (t.TreeSearch(x) != t.nil));
			break;
		case 1:	// vEBTreeMinimum
			y = v.vEBTreeMinimum();
			n = t.TreeMinimum();
			if (y == NIL)
				assert(n == t.nil);
			else
				assert(n != t.nil && y == n->data.data);
			break;
		case 2:	// vEBTreeMaximum
			y = v.vEBTreeMaximum();
			n = t.TreeMaximum();
			if (y == NIL)
				assert(n == t.nil);
			else
				assert(n != t.nil && y == n->data.data);
			break;
		case 3:	// vEBTreePredecessor
			y = v.vEBTreePredecessor(x);
			if (y == NIL) {
				n = t.TreeMinimum();
				assert(n == t.nil || n->data.data >= x);
			} else {
				n = t.TreeSearch(y);
				assert(n != t.nil);
				n = t.TreeSuccessor(n);
				assert(n == t.nil || n->data.data >= x);
			}
			break;
		case 4:	// vEBTreeSuccessor
			y = v.vEBTreeSuccessor(x);
			if (y == NIL) {
				n = t.TreeMaximum();
				assert(n == t.nil || n->data.data <= x);
			} else {
				n = t.TreeSearch(y);
				assert(n != t.nil);
				n = t.TreePredecessor(n);
				assert(n == t.nil || n->data.data <= x);
			}
			break;
		case 5:	// vEBTreeInsert
			if (!v.vEBTreeMember(x)) {
				v.vEBTreeInsert(x);
				if (t.TreeSearch(x) == t.nil)
					t.RBInsert(x);
			}
			break;
		case 6:	// vEBTreeDelete
			if (v.vEBTreeMember(x)) {
				v.vEBTreeDelete(x);
				n = t.TreeSearch(x);
				if (n != t.nil)
					t.TreeDelete(n);
			}
			break;
		default:
			assert(0);
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	std::vector<int> ns = {20000, 25000, 100000};
	for (int k = 1; k <= 16; k++)
		for (std::vector<int>::iterator n = ns.begin(); n < ns.end(); n++)
			test(k, *n);
	return 0;
}
