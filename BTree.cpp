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
#define MAIN_BTree
#endif

#ifndef FUNC_BTree
#define FUNC_BTree

#include <vector>
#include <map>
#include "utils.h"

size_t debug; 

template <typename T>
T* DiskRead(T* x) {
	debug > 0 && std::cout << "read  " << static_cast<void*>(x) << std::endl; 
	return x; 
}

template <typename T>
T* DiskWrite(T* x) {
	debug > 0 && std::cout << "write " << static_cast<void*>(x) << std::endl; 
	return x; 
}

template <typename T>
class BNode {
	public:
		BNode(bool l): n(0), key(0), c(0), leaf(l) {}
		BNode<T>* recursive_destruct() {
			if (!leaf)
				for (auto i = c.begin(); i != c.end(); i++)
					delete (*i)->recursive_destruct(); 
			return this; 
		}
		size_t n; 
		std::vector<T> key; 
		std::vector<BNode<T>*> c; 
		bool leaf; 
}; 

template <typename T>
BNode<T>* AllocateNode(bool l) {
	BNode<T>* x = new BNode<T>(l); 
	debug > 1 && std::cout << "alloc " << static_cast<void*>(x) << std::endl; 
	return x; 
}

template <typename T>
class BTree {
	public:
		BTree(size_t tt): root(BTreeCreate()), t(tt) {}
		std::pair<BNode<T>*, size_t> BTreeSearch(BNode<T>* x, const T& k) {
			size_t i; 
			for (i = 0; i < x->n && x->key[i] < k; i++); 
			if (i <= x->n && k == x->key[i])
				return std::pair<BNode<T>*, size_t>(x, i); 
			else if (x->leaf)
				return std::pair<BNode<T>*, size_t>(nullptr, 0); 
			else
				return BTreeSearch(DiskRead(x->c[i]), k); 
		}
		std::pair<BNode<T>*, size_t> BTreeSearch(const T& k) {
			return BTreeSearch(root, k); 
		}
		BNode<T>* BTreeCreate() {
			BNode<T>* x = AllocateNode<T>(true); 
			return DiskWrite(x); 
		}
		void BTreeSplitChild(BNode<T>* x, size_t i) {
			BNode<T>* y = x->c[i]; 
			BNode<T>* z = AllocateNode<T>(y->leaf); 
			z->n = t - 1; 
			for (auto j = y->key.begin() + t; j != y->key.end(); j++)
				z->key.push_back(*j); 
			if (!y->leaf)
				for (auto j = y->c.begin() + t; j != y->c.end(); j++)
					z->c.push_back(*j); 
			y->n = t - 1; 
			x->c.push_back(x->c[x->n]); 
			for (size_t j = x->n; j > i + 1; j--)
				x->c[j] = x->c[j - 1]; 
			x->c[i + 1] = z; 
			x->key.push_back(y->key[t - 1]); 	// push back a known legal value
			for (size_t j = x->n; j > i; j--)
				x->key[j] = x->key[j - 1]; 
			x->key[i] = y->key[t - 1]; 
			x->n++; 
			y->key.resize(t - 1); 
			y->c.resize(t); 
			DiskWrite(y); 
			DiskWrite(z); 
			DiskWrite(x); 
		}
		void BTreeInsertNonfull(BNode<T>* x, const T& k) {
			size_t i = x->n; 
			if (x->leaf) {
				x->key.push_back(k); 			// push back a known legal value
				while (i && k < x->key[i - 1]) {
					x->key[i] = x->key[i - 1]; 
					i--; 
				}
				x->key[i] = k; 
				x->n++; 
				DiskWrite(x); 
			} else {
				while (i && k < x->key[i - 1])
					i--; 
				DiskRead(x->c[i]); 
				if (x->c[i]->n == 2 * t - 1) {
					BTreeSplitChild(x, i); 
					if (k > x->key[i])
						i++; 
				}
				BTreeInsertNonfull(x->c[i], k); 
			}
		}
		void BTreeInsert(const T& k) {
			BNode<T>* r = root; 
			if (r->n == 2 * t - 1) {
				BNode<T>* s = AllocateNode<T>(false); 
				root = s; 
				s->c.push_back(r); 
				BTreeSplitChild(s, 0); 
				BTreeInsertNonfull(s, k); 
			} else
				BTreeInsertNonfull(r, k); 
		}
		void print_tree(BNode<T>* x, size_t depth) {
			std::string indent(4 * depth, ' '); 
			std::cout << indent << "___" << std::endl; 
			for (size_t i = 0; i <= x->n; i++) {
				if (!x->leaf)
					print_tree(x->c[i], depth + 1); 
				if (i == x->n)
					break; 
				std::cout << indent << x->key[i] << std::endl; 
			}
			std::cout << indent << "^^^" << std::endl; 
		}
		void print_tree() {
			print_tree(root, 0); 
		}
		~BTree() { delete root->recursive_destruct(); }
		BNode<T> *root; 
		size_t t; 
}; 
#endif

#ifdef MAIN_BTree
int main(int argc, char *argv[]) {
	size_t t = get_argv(argc, argv, 1, 2); 
	debug = get_argv(argc, argv, 2, 1); 
	BTree<int> BT(t); 
	std::cout << "s / S: search" << std::endl; 
	std::cout << "i / I: insert" << std::endl; 
	std::cout << "p / P: print tree" << std::endl; 
	std::cout << "q / Q: quit" << std::endl; 
	while (true) {
		char c; int x; std::pair<BNode<int>*, size_t> search_ans; 
		std::cout << ">> "; 
		if (!(std::cin >> c)) {
			std::cout << std::endl; 
			break; 
		}
		switch (c) {
			case 's': 
			case 'S': 
				std::cout << "x = "; 
				std::cin >> x; 
				search_ans = BT.BTreeSearch(x); 
				std::cout << static_cast<void*>(search_ans.first) << ", "; 
				std::cout << search_ans.second << std::endl; 
				break; 
			case 'i': 
			case 'I': 
				std::cout << "x = "; 
				std::cin >> x; 
				BT.BTreeInsert(x); 
				break; 
			case 'p': 
			case 'P': 
				BT.print_tree(); 
				break; 
			case 'q': 
			case 'Q': 
				return 0; 
		}
	}
	return 0; 
}
#endif

