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

#include "BinaryTree.hpp"

#include <cassert>
#include <vector>

#include "utils.hpp"

using namespace algorithms;

void test_walk(BinaryTree<int>& BT, std::vector<std::vector<int>> expected) {
	{
		std::vector<int> ans;
		BT.InorderTreeWalk(ans);
		assert(ans == expected[0]);
	}
	{
		std::vector<int> ans;
		BT.PreorderTreeWalk(ans);
		assert(ans == expected[1]);
	}
	{
		std::vector<int> ans;
		BT.PostorderTreeWalk(ans);
		assert(ans == expected[2]);
	}
}

int test0() {
	BinaryTree<int> BT;
	BT.print_tree();
	test_walk(BT, {{}, {}, {}});
	return 0;
}

int test1() {
	BinaryTree<int> BT;
	BT.root = new Node<int>(9);	/* 9 */
	BT.print_tree();
	test_walk(BT, {{9}, {9}, {9}});
	return 0;
}

int test2() {
	BinaryTree<int> BT;
	BT.root = new Node<int>(2);					/*   2   */
	BT.root->left = new Node<int>(1, BT.root);	/*  / \  */
	BT.root->right = new Node<int>(3, BT.root);	/* 1   3 */
	BT.print_tree();
	test_walk(BT, {{1, 2, 3}, {2, 1, 3}, {1, 3, 2}});
	return 0;
}

int test3() {
	BinaryTree<int> BT;
	BT.root = new Node<int>(4);								/*       4       */
	BT.root->left = new Node<int>(2, BT.root);				/*     /   \     */
	BT.root->left->left = new Node<int>(1, BT.root->left);	/*   2       6   */
	BT.root->left->right = new Node<int>(3, BT.root->left);	/*  / \     / \  */
	BT.root->right = new Node<int>(6, BT.root);				/* 1   3   5   7 */
	BT.root->right->left = new Node<int>(5, BT.root->right);
	BT.root->right->right = new Node<int>(7, BT.root->right);
	BT.print_tree();
	test_walk(BT, {
		{1, 2, 3, 4, 5, 6, 7},
		{4, 2, 1, 3, 6, 5, 7},
		{1, 3, 2, 5, 7, 6, 4}});
	delete BT.root->right->right;		/*       4       */
	BT.root->right->right = nullptr;	/*     /   \     */
	BT.print_tree();					/*   2       6   */
	test_walk(BT, {						/*  / \     /    */
		{1, 2, 3, 4, 5, 6},				/* 1   3   5     */
		{4, 2, 1, 3, 6, 5},
		{1, 3, 2, 5, 6, 4}});
	return 0;
}

int main(int argc, char *argv[]) {
	test0();
	test1();
	test2();
	test3();
	return 0;
}
