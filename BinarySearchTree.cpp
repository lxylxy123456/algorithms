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

#ifndef MAIN
#define MAIN
#define MAIN_BinarySearchTree
#endif

#ifndef FUNC_BinarySearchTree
#define FUNC_BinarySearchTree

#include <vector>
#include "utils.h"
#include "BinaryTree.cpp"

template <typename T>
class BinarySearchTree: public BinaryTree<T> {
	public:
		BinarySearchTree(void) {}
		Node<T>* TreeSearch(Node<T>* x, T k) {
			if (!x || k == x->data)
				return x; 
			if (k < x->data)
				return TreeSearch(x->left, k); 
			else
				return TreeSearch(x->right, k); 
		}
		Node<T>* TreeSearch(T k) {
			return TreeSearch(BinaryTree<T>::root, k); 
		}
		Node<T>* IterativeTreeSearch(T k) {
			Node<T>* x = BinaryTree<T>::root; 
			while (x && k != x->data) {
				if (k < x->data)
					x = x->left; 
				else
					x = x->right; 
			}
			return x; 
		}
		Node<T>* TreeMinimum(Node<T>* x) {
			if (x)
				while (x->left)
					x = x->left; 
			return x; 
		}
		Node<T>* TreeMinimum() {
			return TreeMinimum(BinaryTree<T>::root); 
		}
		Node<T>* TreeMaximum(Node<T>* x) {
			if (x)
				while (x->right)
					x = x->right; 
			return x; 
		}
		Node<T>* TreeMaximum() {
			return TreeMaximum(BinaryTree<T>::root); 
		}
		Node<T>* TreeSuccessor(Node<T>* x) {
			if (x->right)
				return TreeMinimum(x->right); 
			Node<T>* y = x->parent; 
			while (y && x == y->right) {
				x = y; 
				y = x->parent; 
			}
			return y; 
		}
		Node<T>* TreePredecessor(Node<T>* x) {
			if (x->left)
				return TreeMaximum(x->left); 
			Node<T>* y = x->parent; 
			while (y && x == y->left) {
				x = y; 
				y = x->parent; 
			}
			return y; 
		}
		~BinarySearchTree() {}
}; 
#endif

#ifdef MAIN_BinarySearchTree
int main(int argc, char *argv[]) {
	BinarySearchTree<int> BT; 
	BT.root = new Node<int>(4); 							/*       4       */
	BT.root->left = new Node<int>(2, BT.root); 				/*     /   \     */
	BT.root->left->left = new Node<int>(1, BT.root->left); 	/*   2       6   */
	BT.root->left->right = new Node<int>(3, BT.root->left); /*  / \     / \  */
	BT.root->right = new Node<int>(6, BT.root); 			/* 1   3   5   7 */
	BT.root->right->left = new Node<int>(5, BT.root->right); 
	BT.root->right->right = new Node<int>(7, BT.root->right); 
	for (int i = 0; i <= 8; i++) {
		Node<int> *ans = BT.TreeSearch(i); 
		std::cout << i << '\t'; 
		std::cout << pptr(ans) << " \t"; 
		std::cout << pptr(BT.IterativeTreeSearch(i)) << " \t"; 
		if (ans) {
			std::cout << pptr(BT.TreeSuccessor(ans)) << " \t"; 
			std::cout << pptr(BT.TreePredecessor(ans)) << " \t"; 
		}
		std::cout << std::endl; 
	}
	std::cout << "min: " << BT.TreeMinimum()->data << std::endl; 
	std::cout << "max: " << BT.TreeMaximum()->data << std::endl; 
	return 0; 
}
#endif

