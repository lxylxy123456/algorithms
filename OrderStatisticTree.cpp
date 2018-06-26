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
#define MAIN_OrderStatisticTree
#endif

#ifndef FUNC_OrderStatisticTree
#define FUNC_OrderStatisticTree

#include <vector>
#include <cassert>
#include "utils.h"
#include "RedBlackTree.cpp"

template <typename T>
class SData {
	// Size Data
	public:
		SData(): size(0) {}
		SData(T d): data(d), size(0) {}
		SData(T d, size_t s): data(d), size(s) {}
		friend bool operator<(T x, const SData<T>& rhs) {
			return x < rhs.data; 
		}
		bool operator<(const SData<T>& rhs) const { return data < rhs.data; }
		bool operator>(const SData<T>& rhs) const { return data > rhs.data; }
		bool operator<=(const SData<T>& rhs) const { return data <= rhs.data; }
		bool operator>=(const SData<T>& rhs) const { return data >= rhs.data; }
		bool operator==(const SData<T>& rhs) const { return data == rhs.data; }
		bool operator!=(const SData<T>& rhs) const { return data != rhs.data; }
		friend std::ostream& operator<<(std::ostream& os, const SData<T>& rhs) {
			return os << rhs.data << '/' << rhs.size; 
		}
		T data; 
		size_t size; 
}; 

template <typename T>
class OrderStatisticTree: public RedBlackTree<SData<T>> {
	public:
		OrderStatisticTree(void) {}
		virtual void LeftRotate(Node<CData<SData<T>>>* x) {
			Node<CData<SData<T>>>* y = x->right; 
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
			y->data.data.size = x->data.data.size; 
			x->data.data.size = x->left->data.data.size + 
								x->right->data.data.size + 1; 
		}
		virtual void RightRotate(Node<CData<SData<T>>>* x) {
			Node<CData<SData<T>>>* y = x->left; 
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
			y->data.data.size = x->data.data.size; 
			x->data.data.size = x->left->data.data.size + 
								x->right->data.data.size + 1; 
		}
		void OSInsert(T d) {
			Node<CData<SData<T>>>* y = this->nil; 
			Node<CData<SData<T>>>* x = this->root; 
			while (x != this->nil) {
				x->data.data.size++; 
				y = x; 
				if (d < x->data.data)
					x = x->left; 
				else
					x = x->right; 
			}
			Node<CData<SData<T>>>* z = new Node<CData<SData<T>>>(
									CData<SData<T>>(SData<T>(d, 1), red), y); 
			if (y == this->nil)
				this->root = z; 
			else if (d < y->data.data)
				y->left = z; 
			else
				y->right = z; 
			z->left = this->nil; 
			z->right = this->nil; 
			RedBlackTree<SData<T>>::RBInsertFixup(z); 
		}
		void UpdateSize(Node<CData<SData<T>>>* x) {
			if (x != this->nil)
				x->data.data.size = x->left->data.data.size + 
									x->right->data.data.size + 1; 
		}
		void OSDelete(Node<CData<SData<T>>>* z) {
			Node<CData<SData<T>>>* x; 
			Node<CData<SData<T>>>* y = z; 
			Color y_original_color = y->data.color; 
			if (z->left == this->nil) {
				x = z->right; 
				RedBlackTree<SData<T>>::RBTransplant(z, z->right); 
			} else if (z->right == this->nil) {
				x = z->left; 
				RedBlackTree<SData<T>>::RBTransplant(z, z->left); 
			} else {
				y = this->TreeMinimum(z->right); 
				y_original_color = y->data.color; 
				x = y->right; 
				if (y->parent == z) {
					x->parent = y; 
					UpdateSize(x); 
				} else {
					RedBlackTree<SData<T>>::RBTransplant(y, y->right); 
					y->right = z->right; 
					y->right->parent = y; 
				}
				RedBlackTree<SData<T>>::RBTransplant(z, y); 
				y->left = z->left; 
				y->left->parent = y; 
				y->data.color = z->data.color; 
			}
			delete z; 
			for (Node<CData<SData<T>>>* i = x; i != this->root;) {
				i = i->parent; 
				UpdateSize(i); 
			}
			if (y_original_color == black)
				RedBlackTree<SData<T>>::RBDeleteFixup(x); 
		}
		void print_tree() {
			printTree(CNodeDescriptor<SData<T>>(this->root, this->nil)); 
		}
		~OrderStatisticTree() { delete this->nil; }
	private:
		void RBInsert(T d); 
		void RBDelete(Node<CData<T>>* z); 
}; 
#endif

#ifdef MAIN_OrderStatisticTree
int main(int argc, char *argv[]) {
	size_t n = get_argv(argc, argv, 1, 0); 
	OrderStatisticTree<int> OS; 
	if (n) {
		std::vector<int> a; 
		random_integers(a, 0, n - 1, n); 
		for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			OS.OSInsert(*i); 
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
	Node<CData<SData<int>>>* var = OS.root; 
	while (true) {
		char c; size_t k; std::vector<CData<SData<int>>> v; 
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
				OS.OSInsert(k); 
				break; 
			case 'd':
				OS.OSDelete(var); 
				break; 
			case 's':
				std::cout << "k = "; 
				std::cin >> k; 
				var = OS.TreeSearch(SData<int>(k)); 
				assert(var == OS.IterativeTreeSearch(SData<int>(k))); 
				std::cout << "var = " << pptr(var) << std::endl; 
				if (var == OS.nil)
					std::cout << "    = nil" << std::endl; 
				break; 
			case '-':
				std::cout << "min = " << OS.TreeMinimum()->data << std::endl; 
				break; 
			case '+':
				std::cout << "max = " << OS.TreeMaximum()->data << std::endl; 
				break; 
			case 'S':
				var = OS.TreeSuccessor(var); 
				std::cout << "var = " << pptr(var) << std::endl; 
				if (var == OS.nil)
					std::cout << "    = nil" << std::endl; 
				else
					std::cout << "val = " << var->data << std::endl; 
				break; 
			case 'P':
				var = OS.TreePredecessor(var); 
				std::cout << "var = " << pptr(var) << std::endl; 
				if (var == OS.nil)
					std::cout << "    = nil" << std::endl; 
				else
					std::cout << "val = " << var->data << std::endl; 
				break; 
			case '0':
				OS.PreorderTreeWalk(v); 
				output_integers(v); 
				v.clear(); 
				break; 
			case '1':
				OS.InorderTreeWalk(v); 
				output_integers(v); 
				v.clear(); 
				break; 
			case '2':
				OS.PostorderTreeWalk(v); 
				output_integers(v); 
				v.clear(); 
				break; 
			case 'p':
				OS.print_tree(); 
				break; 
		}
	}
	return 0; 
}
#endif

