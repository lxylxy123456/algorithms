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

#ifndef ALGORITHMS_REDBLACKTREE
#define ALGORITHMS_REDBLACKTREE

#include <iostream>
#include <sstream>
#include <string>

#include "BinarySearchTree.hpp"

namespace algorithms {

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

template <typename NodeType>
class RBTreeNavigator {
	public:
		RBTreeNavigator(NodeType nil): nil(nil) {}
		NodeType left(NodeType node) { return node->left; }
		NodeType right(NodeType node) { return node->right; }
		StringLen key(NodeType node) {
			std::ostringstream os;
			os << node->data.data;
			std::string ans = os.str();
			if (node->data.color == black)
				return StringLen(ans);
			else
				return StringLen("\033[31m" + ans + "\033[0m", ans.length());
		}
		bool is_nil(NodeType node) { return node == nil; }
		NodeType nil;
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
			TreePrint(this->root, RBTreeNavigator<Node<CData<T>>*>(this->nil));
		}
		~RedBlackTree() { if (this->root != this->nil) delete this->nil; }
		// TreeInsert = RBInsert, TreeDelete = RBDelete
		void TreeInsert(T v) { RBInsert(v); }
		void TreeDelete(Node<CData<T>>* z) { RBDelete(z); }
	private:
		void Transplant(Node<T>* u, Node<T>* v);
};

}

#endif
