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
		BinarySearchTree(Node<T>* n): BinaryTree<T>(n) {}
		Node<T>* TreeSearch(Node<T>* x, T k) {
			if (x == this->nil || k == x->data)
				return x; 
			if (k < x->data)
				return TreeSearch(x->left, k); 
			else
				return TreeSearch(x->right, k); 
		}
		Node<T>* TreeSearch(T k) {
			return TreeSearch(this->root, k); 
		}
		Node<T>* IterativeTreeSearch(T k) {
			Node<T>* x = this->root; 
			while (x != this->nil && k != x->data) {
				if (k < x->data)
					x = x->left; 
				else
					x = x->right; 
			}
			return x; 
		}
		Node<T>* TreeMinimum(Node<T>* x) {
			if (x != this->nil)
				while (x->left != this->nil)
					x = x->left; 
			return x; 
		}
		Node<T>* TreeMinimum() {
			return TreeMinimum(this->root); 
		}
		Node<T>* TreeMaximum(Node<T>* x) {
			if (x != this->nil)
				while (x->right != this->nil)
					x = x->right; 
			return x; 
		}
		Node<T>* TreeMaximum() {
			return TreeMaximum(this->root); 
		}
		Node<T>* TreeSuccessor(Node<T>* x) {
			if (x->right != this->nil)
				return TreeMinimum(x->right); 
			Node<T>* y = x->parent; 
			while (y != this->nil && x == y->right) {
				x = y; 
				y = x->parent; 
			}
			return y; 
		}
		Node<T>* TreePredecessor(Node<T>* x) {
			if (x->left != this->nil)
				return TreeMaximum(x->left); 
			Node<T>* y = x->parent; 
			while (y != this->nil && x == y->left) {
				x = y; 
				y = x->parent; 
			}
			return y; 
		}
		void TreeInsert(T v) {
			Node<T>* y = this->nil; 
			Node<T>* x = this->root; 
			while (x != this->nil) {
				y = x; 
				if (v < x->data)
					x = x->left; 
				else
					x = x->right; 
			}
			if (y == this->nil)
				this->root = new Node<T>(v); 
			else if (v < y->data)
				y->left = new Node<T>(v, y); 
			else
				y->right = new Node<T>(v, y); 
		}
		void Transplant(Node<T>* u, Node<T>* v) {
			if (u->parent == this->nil)
				this->root = v; 
			else if (u == u->parent->left)
				u->parent->left = v; 
			else
				u->parent->right = v; 
			if (v != this->nil)
				v->parent = u->parent; 
		}
		void TreeDelete(Node<T>* z) {
			if (z->left == this->nil)
				Transplant(z, z->right); 
			else if (z->right == this->nil)
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
	std::cout << "p: print tree" << std::endl; 
	std::cout << "q: quit" << std::endl; 
	Node<int>* var = BT.root; 
	while (true) {
		char c; int k; std::vector<int> v; 
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
			case 'p':
				BT.print_tree(); 
				break; 
		}
	}
	return 0; 
}
#endif

