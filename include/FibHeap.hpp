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

#ifndef ALGORITHMS_FIBHEAP
#define ALGORITHMS_FIBHEAP

#include <exception>
#include "utils.h"

#include "RedBlackTree.hpp"

namespace algorithms {


template <typename T>
class FNode {
	public:
		FNode(T k, FNode<T>* P): key(k), degree(0), p(P), child(nullptr),
								left(nullptr), right(nullptr), mark(false) {}
		FNode<T>* recursive_destruct() {
			while (child)
				delete DLLRemove(child, child)->recursive_destruct();
			return this;
		}
		T key;
		size_t degree;
		FNode<T> *p, *child, *left, *right;
		bool mark;
};

template <typename T>
class FNodeDeg {
	public:
		FNodeDeg(): data(nullptr) {}
		FNodeDeg(FNode<T>* d): data(d) {}
		bool operator<(const FNodeDeg& rhs) const {
			return data->degree < rhs.data->degree;
		}
		bool operator==(const FNodeDeg& rhs) const {
			return data->degree == rhs.data->degree;
		}
		FNode<T>* data;
};

template <typename T>
void DLLInsert(FNode<T>*& root, FNode<T>* x) {
	if (root) {
		x->left = root->left;
		x->left->right = x;
		x->right = root;
		root->left = x;
	} else {
		root = x;
		root->left = root;
		root->right = root;
	}
}

template <typename T>
FNode<T>* DLLRemove(FNode<T>*& root, FNode<T>* x) {
	if (root == root->right)
		root = nullptr;
	else {
		if (root == x)
			root = root->right;
		x->left->right = x->right;
		x->right->left = x->left;
	}
	return x;
}

template <typename T>
class FibHeap {
	public:
		FibHeap() { MakeFibHeap(); }
		void MakeFibHeap() {
			n = 0;
			min = nullptr;
		}
		FNode<T>* FibHeapInsert(const T& k) {
			FNode<T>* x = new FNode<T>(k, nullptr);
			DLLInsert(min, x);
			if (x->key < min->key)
				min = x;
			n++;
			return x;
		}
		FNode<T>* FibHeapMinimum() {
			return min;
		}
		FibHeap<T> FibHeapUnion(FibHeap<T>& rhs) {
			FibHeap<T> H;
			if (min) {
				H.min = min;
				if (rhs.min) {
					FNode<T> *ll = min->left, *rl = rhs.min->left;
					min->left = rl;
					rhs.min->left = ll;
					ll->right = rhs.min;
					rl->right = min;
					if (rhs.min < min)
						H.min = rhs.min;
				}
			} else
				H.min = rhs.min;
			H.n = n + rhs.n;
			MakeFibHeap();
			rhs.MakeFibHeap();
			return H;
		}
		FNode<T>* FibHeapLink(FNode<T>* x, FNode<T>* y) {
			if (x->key > y->key)
				std::swap(x, y);
			DLLInsert(x->child, y);
			x->degree++;
			y->p = x;
			y->mark = false;
			return x;
		}
		void Consolidate() {
			RedBlackTree<FNodeDeg<T>> A;
			while (min) {
				FNode<T>* x = DLLRemove(min, min);
				while (true) {
					Node<CData<FNodeDeg<T>>>* Y = A.TreeSearch(FNodeDeg<T>(x));
					if (Y == A.nil)
						break;
					FNode<T>* y = Y->data.data.data;
					A.RBDelete(Y);
					x = FibHeapLink(x, y);
				}
				A.RBInsert(FNodeDeg<T>(x));
			}
			for (auto i = A.TreeMinimum(); i != A.nil; i = A.TreeSuccessor(i)) {
				FNode<T>* x = i->data.data.data;
				DLLInsert(min, x);
				if (x->key < min->key)
					min = x;
			}
		}
		FNode<T>* FibHeapExtractMin() {
			FNode<T>* z = min;
			if (z) {
				while(z->child) {
					FNode<T>* c = DLLRemove(z->child, z->child);
					DLLInsert(min, c);
					c->p = nullptr;
				}
				DLLRemove(min, z);
				if (min)
					Consolidate();
				n--;
			}
			return z;
		}
		void Cut(FNode<T>* x, FNode<T>* y) {
			DLLRemove(y->child, x);
			y->degree--;
			DLLInsert(min, x);
			x->p = nullptr;
			x->mark = false;
		}
		void CascadingCut(FNode<T>* y) {
			FNode<T>* z = y->p;
			if (z) {
				if (y->mark) {
					Cut(y, z);
					CascadingCut(z);
				} else
					y->mark = true;
			}
		}
		void FibHeapDecreaseKey(FNode<T>* x, T k) {
			if (k > x->key)
				throw std::invalid_argument("new key > current key");
			x->key = k;
			FNode<T>* y = x->p;
			if (y && x->key < y->key) {
				Cut(x, y);
				CascadingCut(y);
			}
			if (x->key < min->key)
				min = x;
		}
		void FibHeapDelete(FNode<T>* x) {
			T minf = min->key - 1;
			if (minf >= min->key)
				throw std::invalid_argument("cannot create minf");
			FibHeapDecreaseKey(x, minf);
			FibHeapExtractMin();
		}
		void print_tree(FNode<T>* x, size_t indent) {
			if (!x) {
				std::cout << std::endl;
				return;
			}
			std::cout << x->key << '\t';
			print_tree(x->child, indent + 1);
			for (FNode<T>* i = x->right; i != x; i = i->right) {
				std::cout << std::string(indent, '\t') << i->key << '\t';
				print_tree(i->child, indent + 1);
			}
		}
		void print_tree() {
			std::cout << std::endl;
			if (min)
				print_tree(min, 0);
			else
				std::cout << "(empty)" << std::endl;
			std::cout << std::endl;
		}
		~FibHeap() {
			while (min)
				delete DLLRemove(min, min)->recursive_destruct();
		}
		FNode<T>* min;
		size_t n;
};

}

#endif
