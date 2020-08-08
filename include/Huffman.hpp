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

#ifndef ALGORITHMS_HUFFMAN
#define ALGORITHMS_HUFFMAN

#define EVENTS std::vector<Event<T>>

#include <vector>
#include "printtree.h"

#include "MaxHeap.hpp"

namespace algorithms {

template <typename T>
class CNode {
	public:
		CNode(T d, size_t f): disp(d), freq(f), left(nullptr), right(nullptr) {}
		CNode(T d, size_t f, CNode<T>* l, CNode<T>* r): disp(d), freq(f),
														left(l), right(r) {}
		friend std::ostream& operator<<(std::ostream& o, const CNode<T>& r) {
			return o << r.disp;
		}
		bool operator<(const CNode<T>& rhs) const { return freq > rhs.freq; }
		bool operator>(const CNode<T>& rhs) const { return freq < rhs.freq; }
		T disp;
		size_t freq;
		CNode<T> *left, *right;
};

template <typename T>
class CNodeDesc {
	public:
		CNodeDesc(CNode<T>* p): node(p) {}
		bool isNull() { return !node; }
		String key() {
			std::ostringstream os;
			if (node->disp)
				os << *node;
			else
				os << node->freq;
			std::string ans = os.str();
			if (node->left)
				return String(ans);
			else {
				String ret(ans);
				ret.data[0] = "\033[31m" + ret.data[0];
				ret.data[ret.size() - 1] += "\033[0m";
				return ret;
			}
		}
		CNodeDesc<T> left() { return CNodeDesc<T>(node->left); }
		CNodeDesc<T> right() { return CNodeDesc<T>(node->right); }
		CNode<T> *node;
};

template <typename T>
CNode<T>* Huffman(std::vector<CNode<T>> C) {
	size_t n = C.size();
	PriorityQueue<CNode<T>> P;
	for (typename std::vector<CNode<T>>::iterator i = C.begin();
		i != C.end(); i++) {
		P.push_back(*i);
		P.MaxHeapInsert(*i);
	}
	for (size_t i = 1; i < n; i++) {
		CNode<T>* x = new CNode<T>(P.HeapExtractMax());
		P.pop_back();
		CNode<T>* y = new CNode<T>(P.HeapExtractMax());
		P.pop_back();
		CNode<T> z('\0', x->freq + y->freq, x, y);
		P.push_back(z);
		P.MaxHeapInsert(z);
	}
	return new CNode<T>(P.HeapMaximum());
}

}

#endif
