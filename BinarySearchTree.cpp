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
#include <cassert>
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
		void TreeInsert(T v) {
			Node<T>* y = nullptr; 
			Node<T>* x = BinaryTree<T>::root; 
			while (x) {
				y = x; 
				if (v < x->data)
					x = x->left; 
				else
					x = x->right; 
			}
			if (!y)
				BinaryTree<T>::root = new Node<T>(v); 
			else if (v < y->data)
				y->left = new Node<T>(v, y); 
			else
				y->right = new Node<T>(v, y); 
		}
		void Transplant(Node<T>* u, Node<T>* v) {
			if (!u->parent)
				BinaryTree<T>::root = v; 
			else if (u == u->parent->left)
				u->parent->left = v; 
			else
				u->parent->right = v; 
			if (v)
				v->parent = u->parent; 
		}
		void TreeDelete(Node<T>* z) {
			if (!z->left)
				Transplant(z, z->right); 
			else if (!z->right)
				Transplant(z, z->left); 
			else {
				Node<T>* y = TreeMinimum(z->right); 
				if (y->parent != z) {
					Transplant(y, y->right); 
					y->right = z->right; 
					y->right->parent = y; 
				}
				Transplant(z, y); 
				y->left = z->left; 
				y->left->parent = y; 
			}
			delete z; 
		}
		~BinarySearchTree() {}
}; 
#endif

#ifdef MAIN_BinarySearchTree
int main(int argc, char *argv[]) {
	BinarySearchTree<int> BT; 
	std::cout << "d: delete" << std::endl; 
	std::cout << "i: insert" << std::endl; 
	std::cout << "s: search" << std::endl; 
	std::cout << "-: minimum" << std::endl; 
	std::cout << "+: maximum" << std::endl; 
	std::cout << "S: successor" << std::endl; 
	std::cout << "P: predecessor" << std::endl; 
	std::cout << "0: preorder tree walk" << std::endl; 
	std::cout << "1: inorder tree walk" << std::endl; 
	std::cout << "2: postorder tree walk" << std::endl; 
	std::cout << "q: quit" << std::endl; 
	Node<int>* var = BT.root; 
	while (true) {
		char c; size_t k; std::vector<int> v; 
		std::cout << ">> "; 
		if (!(std::cin >> c)) {
			std::cout << std::endl; 
			break; 
		}
		if (c == 'q')
			break; 
		switch (c) {
			case 'i': 
				std::cout << "k = "; 
				std::cin >> k; 
				BT.TreeInsert(k); 
				break; 
			case 'd':
				BT.TreeDelete(var); 
				break; 
			case 's':
				std::cout << "k = "; 
				std::cin >> k; 
				var = BT.TreeSearch(k); 
				assert(var == BT.IterativeTreeSearch(k)); 
				std::cout << "var = " << pptr(var) << std::endl; 
				break; 
			case '-':
				std::cout << "min = " << BT.TreeMinimum()->data << std::endl; 
				break; 
			case '+':
				std::cout << "max = " << BT.TreeMaximum()->data << std::endl; 
				break; 
			case 'S':
				var = BT.TreeSuccessor(var); 
				std::cout << "var = " << pptr(var) << std::endl; 
				if (var)
					std::cout << "val = " << var->data << std::endl; 
				break; 
			case 'P':
				var = BT.TreePredecessor(var); 
				std::cout << "var = " << pptr(var) << std::endl; 
				if (var)
					std::cout << "val = " << var->data << std::endl; 
				break; 
			case '0':
				BT.PreorderTreeWalk(v); 
				output_integers(v); 
				v.clear(); 
				break; 
			case '1':
				BT.InorderTreeWalk(v); 
				output_integers(v); 
				v.clear(); 
				break; 
			case '2':
				BT.PostorderTreeWalk(v); 
				output_integers(v); 
				v.clear(); 
				break; 
		}
	}
	return 0; 
}
#endif

