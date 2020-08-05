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

#include "OptimalBST.hpp"

#include "utils.h"

using namespace algorithms;

#include "BinarySearchTree.hpp"

enum PQ { red, black };

class PQData {
	public:
		PQData(size_t r, size_t d, PQ c): rank(r), data(d), color(c) {}
		bool operator<(const PQData& rhs) const {
			if (rank != rhs.rank)
				return rank < rhs.rank;
			else
				return color < rhs.color;
		}
		friend std::ostream& operator<<(std::ostream& os, const PQData& rhs) {
			if (rhs.color == red)
				return os << "\033[31m" << rhs.data << "\033[0m";
			else
				return os << rhs.data;
		}
		size_t rank, data;
		enum PQ color;
};

class PQNodeDesc {
	public:
		PQNodeDesc(Node<PQData>* p, Node<PQData>* n): node(p), nil(n){}
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
		PQNodeDesc left() { return PQNodeDesc(node->left, nil); }
		PQNodeDesc right() { return PQNodeDesc(node->right, nil); }
		Node<PQData> *node, *nil;
};

void insert_OBST(SIZT_1D& p, SIZT_1D& q, SIZT_2D& root, size_t i, size_t j,
	BinarySearchTree<PQData>& T) {
	if (i == j) {
		T.TreeInsert(PQData(i, q[i], red));
	} else {
		size_t r = root[i][j];
		T.TreeInsert(PQData(r, p[r], black));
		insert_OBST(p, q, root, i, r, T);
		insert_OBST(p, q, root, r + 1, j, T);
	}
}

void print_OBST(SIZT_1D& p, SIZT_1D& q, size_t n, SIZT_2D& root) {
	BinarySearchTree<PQData> T;
	insert_OBST(p, q, root, 0, n, T);
	printTree(PQNodeDesc(T.root, T.nil));
}

int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 8);
	SIZT_1D p, q;
	random_integers<size_t>(p, 1, n, n);
	random_integers<size_t>(q, 1, n, n + 1);
	output_integers(p);
	output_integers(q);
	SIZT_2D root = OptimalBST(p, q, n);
	print_OBST(p, q, n, root);
	return 0;
}
