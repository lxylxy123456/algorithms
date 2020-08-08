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

#include "BinaryTree.hpp"

#include "utils.h"

using namespace algorithms;

int main(int argc, char *argv[]) {
	BinaryTree<int> BT;
	BT.root = new Node<int>(4); 							/*       4       */
	BT.root->left = new Node<int>(2, BT.root); 				/*     /   \     */
	BT.root->left->left = new Node<int>(1, BT.root->left); 	/*   2       6   */
	BT.root->left->right = new Node<int>(3, BT.root->left); /*  / \     / \  */
	BT.root->right = new Node<int>(6, BT.root); 			/* 1   3   5   7 */
	BT.root->right->left = new Node<int>(5, BT.root->right);
	BT.root->right->right = new Node<int>(7, BT.root->right);
	for (int i = 0; i < 3; i++) {
		std::vector<int> ans;
		switch (i) {
			case 0:
				BT.InorderTreeWalk(ans);
				break;
			case 1:
				BT.PreorderTreeWalk(ans);
				break;
			case 2:
				BT.PostorderTreeWalk(ans);
				break;
		}
		output_integers(ans);
	}
	BT.print_tree();
	return 0;
}
