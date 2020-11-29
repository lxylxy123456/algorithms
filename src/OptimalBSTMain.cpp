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

#include <iostream>
#include <sstream>
#include <string>

#include "BinarySearchTree.hpp"
#include "utils.hpp"

using namespace algorithms;

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

template <typename NodeType>
class OBSTNavigator {
	public:
		OBSTNavigator(NodeType nil): nil(nil) {}
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
	TreePrint(T.root, OBSTNavigator<Node<PQData>*>(T.nil));
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
