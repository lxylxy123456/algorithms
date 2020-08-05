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

#include <map>
#include <iomanip>
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
T* AllocateNode(bool l) {
	T* x = new T(l);
	debug > 1 && std::cout << "alloc " << static_cast<void*>(x) << std::endl;
	return x;
}

template <typename T>
void FreeNode(T* x) {
	debug > 1 && std::cout << "free  " << static_cast<void*>(x) << std::endl;
	delete x;
}

template <typename T>
class BNode {
	public:
		BNode(bool l): n(0), key(0), c(0), leaf(l) {}
		BNode<T>* recursive_destruct() {
			if (!leaf)
				for (auto i = c.begin(); i != c.end(); i++)
					FreeNode((*i)->recursive_destruct());
			return this;
		}
		size_t n;
		std::vector<T> key;
		std::vector<BNode<T>*> c;
		bool leaf;
};

template <typename T>
void pop_front(std::vector<T>& x) {
	for (size_t i = 0; i < x.size() - 1; i++)
		x[i] = x[i + 1];
	x.pop_back();
}

template <typename T>
void push_front(std::vector<T>& x, const T& k) {
	x.push_back(k);
	for (size_t i = x.size(); i > 0; i--)
		x[i] = x[i - 1];
	x[0] = k;
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
			BNode<T>* x = AllocateNode<BNode<T>>(true);
			return DiskWrite(x);
		}
		void BTreeSplitChild(BNode<T>* x, size_t i) {
			BNode<T>* y = x->c[i];
			BNode<T>* z = AllocateNode<BNode<T>>(y->leaf);
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
				BNode<T>* s = AllocateNode<BNode<T>>(false);
				root = s;
				s->c.push_back(r);
				BTreeSplitChild(s, 0);
				BTreeInsertNonfull(s, k);
			} else
				BTreeInsertNonfull(r, k);
		}
		void BTreeMergeChild(BNode<T>* x, size_t i) {
			// merge x->key[i] and z = x->c[i + 1] to y = x->c[i]
			// assume y and z are read, assume y.n == z.n == t - 1
			BNode<T> *y = x->c[i], *z = x->c[i + 1];
			y->key.push_back(x->key[i]);
			for (auto j = z->key.begin(); j != z->key.end(); j++)
				y->key.push_back(*j);
			for (auto j = z->c.begin(); j != z->c.end(); j++)
				y->c.push_back(*j);
			y->n = 2 * t - 1;
			DiskWrite(y);
			FreeNode(z);
			for (size_t j = i; j < x->n - 1; j++) {
				x->key[j] = x->key[j + 1];
				x->c[j + 1] = x->c[j + 2];
			}
			x->key.pop_back();
			x->c.pop_back();
			x->n--;
			DiskWrite(x);
		}
		void BTreeRotateLeft(BNode<T>* x, size_t i) {
			// z = x->c[i + 1] ===> x->key[i] ===> y = x->c[i]
			// assume y and z are read
			BNode<T> *y = x->c[i], *z = x->c[i + 1];
			y->key.push_back(x->key[i]);
			x->key[i] = z->key[0];
			pop_front(z->key);
			if (!y->leaf) {
				y->c.push_back(z->c[0]);
				pop_front(z->c);
			}
			y->n++;
			z->n--;
			DiskWrite(x);
			DiskWrite(y);
			DiskWrite(z);
		}
		void BTreeRotateRight(BNode<T>* x, size_t i) {
			// y = x->c[i] ===> x->key[i] ===> z = x->c[i + 1]
			// assume y and z are read
			BNode<T> *y = x->c[i], *z = x->c[i + 1];
			push_front(z->key, x->key[i]);
			x->key[i] = y->key[y->n - 1];
			y->key.pop_back();
			if (!y->leaf) {
				push_front(z->c, y->c[y->n]);
				y->c.pop_back();
			}
			z->n++;
			y->n--;
			DiskWrite(x);
			DiskWrite(y);
			DiskWrite(z);
		}
		T BTreeDeleteMin(BNode<T>* x) {
			if (x->leaf) {	// case 1
				T ans = x->key[0];
				pop_front(x->key);
				x->n--;
				return ans;
			} else {		// case 3
				size_t i = x->n;
				BNode<T>* c = DiskRead(x->c[i]);
				if (c->n == t - 1) {
					if (DiskRead(x->c[i - 1])->n >= t)
						BTreeRotateRight(x, i - 1);
					else			// case 3.b
						BTreeMergeChild(x, --i);
				}
				return BTreeDeleteMin(x->c[i]);
			}
		}
		T BTreeDeleteMax(BNode<T>* x) {
			if (x->leaf) {	// case 1
				T ans = x->key[x->n - 1];
				x->key.pop_back();
				x->n--;
				return ans;
			} else {		// case 3
				size_t i = 0;
				BNode<T>* c = DiskRead(x->c[i]);
				if (c->n == t - 1) {
					if (DiskRead(x->c[i + 1])->n >= t)
						BTreeRotateLeft(x, i);
					else			// case 3.b
						BTreeMergeChild(x, i);
				}
				return BTreeDeleteMax(x->c[i]);
			}
		}
		bool BTreeDelete(BNode<T>* x, const T& k) {
			if (x->leaf) {	// case 1
				bool deleting = false;
				for (size_t i = 0; i < x->n; i++) {
					if (!deleting) {
						if (x->key[i] == k)
							deleting = true;
					}
					if (deleting && i + 1 < x->n) {
						x->key[i] = x->key[i + 1];
					}
				}
				if (deleting) {
					x->key.pop_back();
					x->n--;
				}
				DiskWrite(x);
				return deleting;
			}
			bool k_in_x;
			size_t i;
			for (i = 0; i < x->n; i++) {
				if (x->key[i] == k) {
					k_in_x = true; 		// x->key[i] = k
					break;
				}
				if (x->key[i] > k) {
					k_in_x = false; 	// k in x->c[i]
					break;
				}
			}
			if (k_in_x) {	// case 2
				BNode<T> *y = DiskRead(x->c[i]), *z = DiskRead(x->c[i + 1]);
				if (y->n >= t) {	// case 2.a
					x->key[i] = BTreeDeleteMax(y);
					return true;
				} else if (z->n >= t) {	//  2.b
					x->key[i] = BTreeDeleteMin(z);
					return true;
				} else {				//  2.c
					BTreeMergeChild(x, i);
					return BTreeDelete(y, k);
				}
			} else {		// case 3
				BNode<T>* c = DiskRead(x->c[i]);
				if (c->n == t - 1) {
					if (i < x->n && DiskRead(x->c[i + 1])->n >= t)
						BTreeRotateLeft(x, i);
					else if (i > 0 && DiskRead(x->c[i - 1])->n >= t)
						BTreeRotateRight(x, i - 1);
					else {			// case 3.b
						if (i)
							i--;
						BTreeMergeChild(x, i);
					}
				}
				return BTreeDelete(x->c[i], k);
			}
		}
		bool BTreeDelete(const T& k) {
			bool ans = BTreeDelete(root, k);
			while (!root->n) {
				BNode<T>* ori = root;
				root = DiskRead(root->c[0]);
				FreeNode(ori);
			}
			return ans;
		}
		void print_tree(BNode<T>* x, size_t depth, bool term) {
			const size_t ind = 4;
			const std::string indent(ind * depth, ' ');
			if (!term)
				std::cout << indent << std::string(3, '_') << std::endl;
			for (size_t i = 0; i <= x->n; i++) {
				if (!x->leaf)
					print_tree(x->c[i], depth + 1, term);
				if (i == x->n)
					break;
				std::cout << indent;
				if (term) {
					if (i == 0)
						std::cout << "\033[53m";
					if (i == x->n - 1)
						std::cout << "\033[4m";
				}
				std::cout << std::left << std::setw(ind - 1) << x->key[i];
				if (term)
					std::cout << "\033[0m";
				std::cout << std::endl;
			}
			if (!term)
				std::cout << indent << std::string(3, '^') << std::endl;
		}
		void print_tree(bool term) {
			std::cout << std::endl;
			print_tree(root, 0, term);
			std::cout << std::endl;
		}
		~BTree() { delete root->recursive_destruct(); }
		BNode<T> *root;
		size_t t;
};
#endif

#ifdef MAIN_BTree
int main(int argc, char *argv[]) {
	size_t t = get_argv(argc, argv, 1, 3);
	debug = get_argv(argc, argv, 2, 1);
	BTree<int> BT(t);
	std::cout << "s / S: search" << std::endl;
	std::cout << "i / I: insert" << std::endl;
	std::cout << "d / D: delete" << std::endl;
	std::cout << "p / P: print tree (two styles)" << std::endl;
	std::cout << "q / Q: quit" << std::endl;
	// Generate tree in Page 498, Figure 18.7 (a):
	// 	i10 i11 i13 i14 i15 i1 i3 i7 i4 i5 i16 i18 i19 i24 i25 i26 i20 i21 i22
	// In Figure 18.7: i2 i17 i12 i6
	// In Figure 18.8: d6 d13 d7 d4 d2
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
			case 'd':
			case 'D':
				std::cout << "x = ";
				std::cin >> x;
				std::cout << std::boolalpha << BT.BTreeDelete(x) << std::endl;
				break;
			case 'p':
				BT.print_tree(true);
				break;
			case 'P':
				BT.print_tree(false);
				break;
			case 'q':
			case 'Q':
				return 0;
		}
	}
	return 0;
}
#endif

