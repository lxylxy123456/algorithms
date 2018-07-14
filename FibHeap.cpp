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
#define MAIN_FibHeap
#endif

#ifndef FUNC_FibHeap
#define FUNC_FibHeap

#include "utils.h"

template <typename T>
class FNode {
	public:
		FNode(T k, FNode<T>* P): key(k), degree(0), p(P), child(nullptr), 
								left(nullptr), right(nullptr), mark(false) {}
//		FNode<T>* recursive_destruct() {}
		T key; 
		size_t degree; 
		FNode<T> *p, *child, *left, *right; 
		bool mark; 
}; 

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
			if (!min) {
				x->left = x; 
				x->right = x; 
				min = x; 
			} else {
				x->left = min->left; 
				x->right = min; 
				min->left = x; 
				x->left->right = x; 
				if (x->key < min->key)
					min = x; 
			}
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
//		~FibHeap() { if (min) { delete min->recursive_destruct(); } }
		FNode<T>* min; 
		size_t n; 
}; 
#endif

#ifdef MAIN_FibHeap
int main(int argc, char *argv[]) {
	std::vector<FibHeap<int>> FH_list(1); 
	FibHeap<int>* FH = &(FH_list[0]); 
	std::cout << "s: select" << std::endl; 	
	std::cout << "i: insert" << std::endl; 
	std::cout << "m: minimum" << std::endl; 
	std::cout << "u: union" << std::endl; 
//	std::cout << "p: print tree" << std::endl; 
	std::cout << "q: quit" << std::endl; 
	FNode<int>* ptr = nullptr; 
	size_t n = 0; 
	while (true) {
		char c; int x; size_t n2; 
		std::cout << "n   = " << n << std::endl; 
		std::cout << "ptr = " << pptr(ptr) << std::endl; 
		std::cout << ">> "; 
		if (!(std::cin >> c)) {
			std::cout << std::endl; 
			break; 
		}
		switch (c) {
			case 's': 
				std::cout << "n = "; 
				std::cin >> n; 
				if (FH_list.size() <= n)
					FH_list.resize(n + 1); 
				FH = &(FH_list[n]); 
				ptr = FH->min; 
				break; 
			case 'i': 
				std::cout << "x = "; 
				std::cin >> x; 
				ptr = FH->FibHeapInsert(x); 
				break; 
			case 'm': 
				ptr = FH->FibHeapMinimum(); 
				break; 
			case 'u':
				std::cout << "n = "; 
				std::cin >> n2; 
				*FH = FH->FibHeapUnion(FH_list[n2]); 
				break; 
			case 'q': 
				return 0; 
		}
	}
	return 0; 
}
#endif

