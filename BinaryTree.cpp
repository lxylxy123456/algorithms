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
#define MAIN_BinaryTree
#endif

#ifndef FUNC_BinaryTree
#define FUNC_BinaryTree

#include <vector>
#include "utils.h"

template <typename T>
class Node {
	public:
		Node(T d): data(d) {}
		Node(T d, Node* p): data(d), parent(p) {}
		Node<T>* recursive_destruct() {
			if (left)
				delete left->recursive_destruct(); 
			if (right)
				delete right->recursive_destruct(); 
			return this; 
		}
		T data; 
		Node<T> *left, *right, *parent; 
}; 

template <typename T>
class BinaryTree {
	public:
		BinaryTree(void): root(nullptr), nil(nullptr) {}
		void InorderTreeWalk(std::vector<T>& v, Node<T>* x) {
			if (x != nil) {
				InorderTreeWalk(v, x->left); 
				v.push_back(x->data); 
				InorderTreeWalk(v, x->right); 
			}
		}
		void InorderTreeWalk(std::vector<T>& v) { InorderTreeWalk(v, root); }
		void PreorderTreeWalk(std::vector<T>& v, Node<T>* x) {
			if (x != nil) {
				v.push_back(x->data); 
				PreorderTreeWalk(v, x->left); 
				PreorderTreeWalk(v, x->right); 
			}
		}
		void PreorderTreeWalk(std::vector<T>& v) { PreorderTreeWalk(v, root); }
		void PostorderTreeWalk(std::vector<T>& v, Node<T>* x) {
			if (x != nil) {
				PostorderTreeWalk(v, x->left); 
				PostorderTreeWalk(v, x->right); 
				v.push_back(x->data); 
			}
		}
		void PostorderTreeWalk(std::vector<T>& v) { PostorderTreeWalk(v, root); }
		~BinaryTree() { if(root) delete root->recursive_destruct(); }
		Node<T> *root, *nil; 
}; 
#endif

#ifdef MAIN_BinaryTree
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
	return 0; 
}
#endif

