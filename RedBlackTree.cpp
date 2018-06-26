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
#define MAIN_RedBlackTree
#endif

#ifndef FUNC_RedBlackTree
#define FUNC_RedBlackTree

#include <vector>
#include <cassert>
#include "utils.h"
#include "BinarySearchTree.cpp"

enum Color { red, black }; 

template <typename T>
class CData {
	// Colored Data
	public:
		CData(): color(black) {}
		CData(T d): data(d), color(black) {}
		CData(T d, Color c): data(d), color(c) {}
		bool operator<(const CData<T>& rhs) const { return data < rhs.data; }
		bool operator>(const CData<T>& rhs) const { return data > rhs.data; }
		bool operator<=(const CData<T>& rhs) const { return data <= rhs.data; }
		bool operator>=(const CData<T>& rhs) const { return data >= rhs.data; }
		bool operator==(const CData<T>& rhs) const { return data == rhs.data; }
		bool operator!=(const CData<T>& rhs) const { return data != rhs.data; }
		friend std::ostream& operator<<(std::ostream& os, const CData<T>& rhs) {
			if (rhs.color == red)
				return os << "\033[31m" << rhs.data << "\033[0m"; 
			else
				return os << rhs.data; 
		}
		T data; 
		enum Color color; 
}; 

template <typename T>
class CNodeDescriptor {
	public:
		CNodeDescriptor(Node<CData<T>>* p, Node<CData<T>>* n): node(p), nil(n){}
		bool isNull() { return node == nil; }
		String key() {
			std::ostringstream os; 
			os << node->data.data; 
			std::string ans = os.str(); 
			if (node->data.color == black)
				return String(ans); 
			else {
				String ret(ans); 
				ret.data[0] = "\033[31m" + ret.data[0]; 
				ret.data[ret.size() - 1] += "\033[0m"; 
				return ret; 
			}
		}
		CNodeDescriptor<T> left() { 
			return CNodeDescriptor<T>(node->left, nil); 
		}
		CNodeDescriptor<T> right() {
			return CNodeDescriptor<T>(node->right, nil); 
		}
		Node<CData<T>> *node, *nil; 
}; 

template <typename T>
class RedBlackTree: public BinarySearchTree<CData<T>> {
	public:
		RedBlackTree(void): BinarySearchTree<CData<T>>(new Node<CData<T>>()) {}
		virtual void LeftRotate(Node<CData<T>>* x) {
			Node<CData<T>>* y = x->right; 
			x->right = y->left; 
			if (y->left != this->nil)
				y->left->parent = x; 
			y->parent = x->parent; 
			if (x->parent == this->nil)
				this->root = y; 
			else if (x == x->parent->left)
				x->parent->left = y; 
			else
				x->parent->right = y; 
			y->left = x; 
			x->parent = y; 
		}
		virtual void RightRotate(Node<CData<T>>* x) {
			Node<CData<T>>* y = x->left; 
			x->left = y->right; 
			if (y->right != this->nil)
				y->right->parent = x; 
			y->parent = x->parent; 
			if (x->parent == this->nil)
				this->root = y; 
			else if (x == x->parent->left)
				x->parent->left = y; 
			else
				x->parent->right = y; 
			y->right = x; 
			x->parent = y; 
		}
		void RBInsertFixup(Node<CData<T>>* z) {
			while (z->parent->data.color == red) {
				if (z->parent == z->parent->parent->left) {
					Node<CData<T>>* y = z->parent->parent->right; 
					if (y->data.color == red) {
						z->parent->data.color = black; 
						y->data.color = black; 
						z->parent->parent->data.color = red; 
						z = z->parent->parent; 
					} else {
						if (z == z->parent->right) {
							z = z->parent; 
							LeftRotate(z); 
						}
						z->parent->data.color = black; 
						z->parent->parent->data.color = red; 
						RightRotate(z->parent->parent); 
					}
				} else {
					Node<CData<T>>* y = z->parent->parent->left; 
					if (y->data.color == red) {
						z->parent->data.color = black; 
						y->data.color = black; 
						z->parent->parent->data.color = red; 
						z = z->parent->parent; 
					} else {
						if (z == z->parent->left) {
							z = z->parent; 
							RightRotate(z); 
						}
						z->parent->data.color = black; 
						z->parent->parent->data.color = red; 
						LeftRotate(z->parent->parent); 
					}
				}
			}
			this->root->data.color = black; 
		}
		void RBInsert(T d) {
			Node<CData<T>>* y = this->nil; 
			Node<CData<T>>* x = this->root; 
			while (x != this->nil) {
				y = x; 
				if (d < x->data.data)
					x = x->left; 
				else
					x = x->right; 
			}
			Node<CData<T>>* z = new Node<CData<T>>(CData<T>(d, red), y); 
			if (y == this->nil)
				this->root = z; 
			else if (d < y->data.data)
				y->left = z; 
			else
				y->right = z; 
			z->left = this->nil; 
			z->right = this->nil; 
			RBInsertFixup(z); 
		}
		void RBTransplant(Node<CData<T>>* u, Node<CData<T>>* v) {
			if (u->parent == this->nil)
				this->root = v; 
			else if (u == u->parent->left)
				u->parent->left = v; 
			else
				u->parent->right = v; 
			v->parent = u->parent; 
		}
		void RBDeleteFixup(Node<CData<T>>* x) {
			while (x != this->root && x->data.color == black) {
				if (x == x->parent->left) {
					Node<CData<T>>* w = x->parent->right; 
					if (w->data.color == red) {
						w->data.color = black; 
						x->parent->data.color = red; 
						LeftRotate(x->parent); 
						w = x->parent->right; 
					}
					if (w->left->data.color == black && 
						w->right->data.color == black) {
						w->data.color = red; 
						x = x->parent; 
					} else {
						if (w->right->data.color == black) {
							w->left->data.color = black; 
							w->data.color = red; 
							RightRotate(w); 
							w = x->parent->right; 
						}
						w->data.color = x->parent->data.color; 
						x->parent->data.color = black; 
						w->right->data.color = black; 
						LeftRotate(x->parent); 
						x = this->root; 
					}
				} else {
					Node<CData<T>>* w = x->parent->left; 
					if (w->data.color == red) {
						w->data.color = black; 
						x->parent->data.color = red; 
						RightRotate(x->parent); 
						w = x->parent->left; 
					}
					if (w->right->data.color == black && 
						w->left->data.color == black) {
						w->data.color = red; 
						x = x->parent; 
					} else {
						if (w->left->data.color == black) {
							w->right->data.color = black; 
							w->data.color = red; 
							LeftRotate(w); 
							w = x->parent->left; 
						}
						w->data.color = x->parent->data.color; 
						x->parent->data.color = black; 
						w->left->data.color = black; 
						RightRotate(x->parent); 
						x = this->root; 
					}
				}
			}
			x->data.color = black; 
		}
		void RBDelete(Node<CData<T>>* z) {
			Node<CData<T>>* x; 
			Node<CData<T>>* y = z; 
			Color y_original_color = y->data.color; 
			if (z->left == this->nil) {
				x = z->right; 
				RBTransplant(z, z->right); 
			} else if (z->right == this->nil) {
				x = z->left; 
				RBTransplant(z, z->left); 
			} else {
				y = this->TreeMinimum(z->right); 
				y_original_color = y->data.color; 
				x = y->right; 
				if (y->parent == z)
					x->parent = y; 
				else {
					RBTransplant(y, y->right); 
					y->right = z->right; 
					y->right->parent = y; 
				}
				RBTransplant(z, y); 
				y->left = z->left; 
				y->left->parent = y; 
				y->data.color = z->data.color; 
			}
			delete z; 
			if (y_original_color == black)
				RBDeleteFixup(x); 
		}
		void print_tree() {
			printTree(CNodeDescriptor<T>(this->root, this->nil)); 
		}
		~RedBlackTree() { delete this->nil; }
	private:
		void TreeInsert(T v); 
		void TreeDelete(Node<T>* z); 
		void Transplant(Node<T>* u, Node<T>* v); 
}; 
#endif

#ifdef MAIN_RedBlackTree
int main(int argc, char *argv[]) {
	size_t n = get_argv(argc, argv, 1, 0); 
	RedBlackTree<int> RB; 
	if (n) {
		std::vector<int> a; 
		random_integers(a, 0, n - 1, n); 
		for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			RB.RBInsert(*i); 
	}
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
	Node<CData<int>>* var = RB.root; 
	while (true) {
		char c; size_t k; std::vector<CData<int>> v; 
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
				RB.RBInsert(k); 
				break; 
			case 'd':
				RB.RBDelete(var); 
				break; 
			case 's':
				std::cout << "k = "; 
				std::cin >> k; 
				var = RB.TreeSearch(k); 
				assert(var == RB.IterativeTreeSearch(k)); 
				std::cout << "var = " << pptr(var) << std::endl; 
				if (var == RB.nil)
					std::cout << "    = nil" << std::endl; 
				break; 
			case '-':
				std::cout << "min = " << RB.TreeMinimum()->data << std::endl; 
				break; 
			case '+':
				std::cout << "max = " << RB.TreeMaximum()->data << std::endl; 
				break; 
			case 'S':
				var = RB.TreeSuccessor(var); 
				std::cout << "var = " << pptr(var) << std::endl; 
				if (var == RB.nil)
					std::cout << "    = nil" << std::endl; 
				else
					std::cout << "val = " << var->data << std::endl; 
				break; 
			case 'P':
				var = RB.TreePredecessor(var); 
				std::cout << "var = " << pptr(var) << std::endl; 
				if (var == RB.nil)
					std::cout << "    = nil" << std::endl; 
				else
					std::cout << "val = " << var->data << std::endl; 
				break; 
			case '0':
				RB.PreorderTreeWalk(v); 
				output_integers(v); 
				v.clear(); 
				break; 
			case '1':
				RB.InorderTreeWalk(v); 
				output_integers(v); 
				v.clear(); 
				break; 
			case '2':
				RB.PostorderTreeWalk(v); 
				output_integers(v); 
				v.clear(); 
				break; 
			case 'p':
				RB.print_tree(); 
				break; 
		}
	}
	return 0; 
}
#endif

