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
#define MAIN_IntervalTree
#endif

#ifndef FUNC_IntervalTree
#define FUNC_IntervalTree

#include <vector>
#include <cassert>
#include "utils.h"
#include "RedBlackTree.cpp"

template <typename T>
class Interval {
	public:
		Interval() {}
		Interval(T l): low(l), high(l) {}
		Interval(T l, T h): low(l), high(h) {}
		bool operator<(const Interval<T> rhs) const { return low < rhs.low; }
		bool operator==(const Interval<T> rhs) const {
			return low <= rhs.high && rhs.low <= high; 
		}
		bool operator!=(const Interval<T> rhs) const {
			return low > rhs.high || rhs.low > high; 
		}
		friend std::istream& operator>>(std::istream& is, Interval<T>& rhs) {
			char c; 
			is >> rhs.low >> c >> rhs.high; 
			assert(c == ','); 
			return is; 
		}
		friend std::ostream& operator<<(std::ostream& os, const Interval<T>& r){
			return os << r.low << '~' << r.high; 
		}
		T low, high; 
}; 

template <typename T>
class MData {
	// Size Data
	public:
		MData() {}
		MData(Interval<T> d): data(d), max(d.high) {}
		bool operator<(const MData<T>& rhs) const { return data < rhs.data; }
		bool operator>(const MData<T>& rhs) const { return data > rhs.data; }
		bool operator<=(const MData<T>& rhs) const { return data <= rhs.data; }
		bool operator>=(const MData<T>& rhs) const { return data >= rhs.data; }
		bool operator==(const MData<T>& rhs) const { return data == rhs.data; }
		bool operator!=(const MData<T>& rhs) const { return data != rhs.data; }
		friend std::ostream& operator<<(std::ostream& os, const MData<T>& rhs) {
			return os << rhs.data; 
			// return os << rhs.data << '<' << rhs.max; 
		}
		Interval<T> data; 
		T max; 
}; 

template <typename T>
class AugmentRedBlackTree: public RedBlackTree<T> {
	public:
		AugmentRedBlackTree(void) {}
		virtual void UpdateAttribute(Node<CData<T>>* x) = 0; 
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
			UpdateAttribute(x); 
			UpdateAttribute(y); 
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
			UpdateAttribute(x); 
			UpdateAttribute(y); 
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
			UpdateAttribute(z); 
			for (Node<CData<T>>* i = z; i != this->root;) {
				i = i->parent; 
				UpdateAttribute(i); 
			}
			RedBlackTree<T>::RBInsertFixup(z); 
		}
		void RBDelete(Node<CData<T>>* z) {
			Node<CData<T>>* x; 
			Node<CData<T>>* y = z; 
			Color y_original_color = y->data.color; 
			if (z->left == this->nil) {
				x = z->right; 
				RedBlackTree<T>::RBTransplant(z, z->right); 
			} else if (z->right == this->nil) {
				x = z->left; 
				RedBlackTree<T>::RBTransplant(z, z->left); 
			} else {
				y = this->TreeMinimum(z->right); 
				y_original_color = y->data.color; 
				x = y->right; 
				if (y->parent == z) {
					x->parent = y; 
					UpdateAttribute(x); 
				} else {
					RedBlackTree<T>::RBTransplant(y, y->right); 
					y->right = z->right; 
					y->right->parent = y; 
				}
				RedBlackTree<T>::RBTransplant(z, y); 
				y->left = z->left; 
				y->left->parent = y; 
				y->data.color = z->data.color; 
			}
			delete z; 
			for (Node<CData<T>>* i = x; i != this->root;) {
				i = i->parent; 
				UpdateAttribute(i); 
			}
			if (y_original_color == black)
				RedBlackTree<T>::RBDeleteFixup(x); 
		}
}; 

template<typename T>
class IntervalTree: public AugmentRedBlackTree<MData<T>> {
	public: 
		virtual void UpdateAttribute(Node<CData<MData<T>>>* x) {
			if (x != this->nil) {
				T& a = x->data.data.max; 
				a = std::max(x->left->data.data.max, x->right->data.data.max); 
				a = std::max(a, x->data.data.data.high); 
			}
		}
		Node<CData<MData<T>>>* IntervalSearch(Interval<T> i) {
			Node<CData<MData<T>>>* x = this->root; 
			while (x != this->nil && i != x->data.data.data) {
				if (x->left != this->nil && x->left->data.data.max >= i.low)
					x = x->left; 
				else
					x = x->right; 
			}
			return x; 
		}
	private:
		Node<CData<MData<T>>>* TreeSearch(Node<CData<MData<T>>>* x, T k); 
		Node<CData<MData<T>>>* TreeSearch(T k); 
}; 
#endif

#ifdef MAIN_IntervalTree
int main(int argc, char *argv[]) {
	size_t n = get_argv(argc, argv, 1, 0); 
	IntervalTree<int> IT; 
	if (n) {
		std::vector<int> a; 
		random_integers(a, 0, n - 1, 2 * n); 
		for (std::vector<int>::iterator i = a.begin(); i != a.end(); i += 2) {
			std::vector<int>::iterator j = i + 1; 
			IT.RBInsert(Interval<int>(std::min(*i, *j), std::max(*i, *j))); 
		}
	}
	std::cout << "d: delete" << std::endl; 
	std::cout << "i: insert" << std::endl; 
	std::cout << "s: search" << std::endl; 
	std::cout << "R: root" << std::endl; 
	std::cout << "-: minimum" << std::endl; 
	std::cout << "+: maximum" << std::endl; 
	std::cout << "S: successor" << std::endl; 
	std::cout << "P: predecessor" << std::endl; 
	std::cout << "0: preorder tree walk" << std::endl; 
	std::cout << "1: inorder tree walk" << std::endl; 
	std::cout << "2: postorder tree walk" << std::endl; 
	std::cout << "p: print tree" << std::endl; 
	std::cout << "q: quit" << std::endl; 
	Node<CData<MData<int>>>* ptr = IT.root; 
	while (true) {
		char c; Interval<int> k; std::vector<CData<MData<int>>> v; 
		std::cout << ">> "; 
		if (!(std::cin >> c)) {
			std::cout << std::endl; 
			break; 
		}
		if (c == 'q')
			break; 
		switch (c) {
			case 'i': 
				std::cout << "l, h = "; 
				std::cin >> k; 
				IT.RBInsert(k); 
				break; 
			case 'd':
				IT.RBDelete(ptr); 
				break; 
			case 's':
				std::cout << "l, h = "; 
				std::cin >> k; 
				ptr = IT.IntervalSearch(k); 
				print_ptr(ptr, IT.nil); 
				break; 
			case 'R':
				ptr = IT.root; 
				print_ptr(ptr, IT.nil); 
				break; 
			case '-':
				ptr = IT.TreeMinimum(ptr); 
				print_ptr(ptr, IT.nil); 
				break; 
			case '+':
				ptr = IT.TreeMaximum(ptr); 
				print_ptr(ptr, IT.nil); 
				break; 
			case 'S':
				ptr = IT.TreeSuccessor(ptr); 
				print_ptr(ptr, IT.nil); 
				break; 
			case 'P':
				ptr = IT.TreePredecessor(ptr); 
				print_ptr(ptr, IT.nil); 
				break; 
			case '0':
				IT.PreorderTreeWalk(v); 
				output_integers(v); 
				v.clear(); 
				break; 
			case '1':
				IT.InorderTreeWalk(v); 
				output_integers(v); 
				v.clear(); 
				break; 
			case '2':
				IT.PostorderTreeWalk(v); 
				output_integers(v); 
				v.clear(); 
				break; 
			case 'p':
				IT.print_tree(); 
				break; 
		}
	}
	return 0; 
}
#endif

