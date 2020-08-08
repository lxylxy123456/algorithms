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

#ifndef ALGORITHMS_BINARYTREE
#define ALGORITHMS_BINARYTREE

#include <vector>
#include <sstream>
#include "printtree.h"

namespace algorithms {

template <typename T>
class Node {
	public:
		Node(): left(nullptr), right(nullptr), parent(nullptr) {}
		Node(T d): data(d), left(nullptr), right(nullptr), parent(nullptr) {}
		Node(T d, Node<T>* p): data(d), left(nullptr), right(nullptr),
								parent(p) {}
		Node<T>* recursive_destruct(Node<T>* nil) {
			if (left && left != nil)
				delete left->recursive_destruct(nil);
			if (right && right != nil)
				delete right->recursive_destruct(nil);
			return this;
		}
		T data;
		Node<T> *left, *right, *parent;
};

template <typename T>
class NodeDescriptor {
	public:
		NodeDescriptor(Node<T>* p, Node<T>* n): node(p), nil(n) {}
		bool isNull() { return node == nil; }
		String key() {
			std::ostringstream os;
			os << node->data;
			return String(os.str());
		}
		NodeDescriptor<T> left() { return NodeDescriptor<T>(node->left, nil);}
		NodeDescriptor<T> right() { return NodeDescriptor<T>(node->right, nil);}
		Node<T> *node, *nil;
};

template <typename T>
class BinaryTree {
	public:
		BinaryTree(void): root(nullptr), nil(nullptr) {}
		BinaryTree(Node<T>* n): root(n), nil(n) {}
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
		void print_tree() {
			printTree(NodeDescriptor<T>(root, nil));
		}
		void PostorderTreeWalk(std::vector<T>& v) { PostorderTreeWalk(v, root); }
		~BinaryTree() { if(root) delete root->recursive_destruct(nil); }
		Node<T> *root, *nil;
};

}

#endif
