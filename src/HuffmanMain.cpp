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

#include "Huffman.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "MaxHeap.hpp"
#include "print_tree.hpp"
#include "utils.hpp"

using namespace algorithms;

template <typename NodeType>
class HuffmanNavigator {
	public:
		HuffmanNavigator() {}
		NodeType left(NodeType node) { return node->left; }
		NodeType right(NodeType node) { return node->right; }
		StringLen key(NodeType node) {
			std::ostringstream os;
			if (node->disp)
				os << *node;
			else
				os << node->freq;
			std::string ans = os.str();
			if (node->left)
				return StringLen(ans);
			else
				return StringLen("\033[31m" + ans + "\033[0m", ans.length());
		}
		bool is_nil(NodeType node) { return !node; }
};

int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 6);
	// prepare data
	std::vector<CNode<char>> C;
	std::vector<size_t> freq_list;
	random_integers<size_t>(freq_list, 1, n, n);
	for (size_t i = 0; i < n; i++)
		C.push_back(CNode<char>('a' + i, freq_list[i]));
	output_integers(C, "\t");
	output_integers(freq_list, "\t");
	std::cout << std::endl;
	// call function
	CNode<char>* B = Huffman(C);
	TreePrint(B, HuffmanNavigator<CNode<char>*>());
	return 0;
}
