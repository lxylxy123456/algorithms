/* adapted from https://www.ugrad.cs.ubc.ca/~cs221/2017W2/labs/heaps/
 * file lab_heaps.zip
 * download: https://www.ugrad.cs.ubc.ca/~cs221/2017W2/labs/heaps/lab_heaps.zip
 */

#ifndef ALGORITHMS_PRINTTREE
#define ALGORITHMS_PRINTTREE

#include <algorithm>
#include <iostream>
#include <string>

namespace algorithms {

// Curiously recurring template pattern
// You don't actually need to extend this class,
// but here are the functions you need to implement
class String {
	public:
		String() {}
		String(std::string s) {
			data.reserve(s.length());
			for (std::string::iterator i = s.begin(); i != s.end(); i++)
				data.push_back(std::string(1, *i));
		}
		String(size_t s, char c): data(s, std::string(1, c)) {}
		friend std::ostream& operator<< (std::ostream& os, String rhs) {
			for (std::vector<std::string>::iterator i = rhs.data.begin();
				i < rhs.data.end(); i++)
				os << *i;
			return os;
		}
		String& operator+=(std::string rhs) {
			for (std::string::iterator i = rhs.begin(); i < rhs.end(); i++)
				data.push_back(std::string(1, *i));
			return *this;
		}
		size_t size() { return data.size(); }
		size_t length() { return data.size(); }
		std::string& operator[](size_t index) { return data[index]; }
		std::vector<std::string> data;
};

template <class DerivedDescriptor>
class GenericNodeDescriptor
{
	public:
	virtual bool isNull() const = 0;
	virtual String key() const = 0;
	virtual DerivedDescriptor left() const = 0;
	virtual DerivedDescriptor right() const = 0;
};

namespace private_print_functions
{
	template <class NodeDescriptor>
	int getPrintHeight(NodeDescriptor croot);

	template <class NodeDescriptor>
	void printSubtree(NodeDescriptor croot,
			std::vector<String> & output,
			int left,
			int top,
			int curr_width);
}

template <class NodeDescriptor>
void printTree(NodeDescriptor root, std::ostream & out = std::cout)
{
	using namespace private_print_functions;

	// Base case
	if (root.isNull())
	{
		out << "(empty)" << std::endl;
		return;
	}

	// Make a character matrix for outputting the tree onto
	int root_height = getPrintHeight(root);
	int print_matrix_width = (4 << root_height) - 3;
	int print_matrix_height = 2 * root_height + 1;

	// Initialize this matrix to be filled with spaces
	std::vector<String> output(print_matrix_height);
	for (size_t i = 0; i < output.size(); ++i)
		output[i] = String(print_matrix_width + 4, ' '); // + 4 extra room for long things

	// Recursively print each node
	printSubtree(root, output, 0, 0, print_matrix_width);

	// Output the matrix
	for (int row = 0; row < print_matrix_height; ++row)
		out << output[row] << std::endl;
}

namespace private_print_functions
{
	template <class NodeDescriptor>
	int getPrintHeight(NodeDescriptor croot)
	{
		if (croot.isNull())
			return -1;
		int l_height = getPrintHeight(croot.left());
		int r_height = getPrintHeight(croot.right());
		return 1 + std::max(l_height, r_height);
	}


	template <class NodeDescriptor>
	void printSubtree(NodeDescriptor croot, std::vector<String> & output, int left, int top, int curr_width)
	{
		// Convert data to String
		String nodeStr = croot.key();

		// Output data
		int left_start_shift = 1 - (nodeStr.length()-1)/2;
		for (size_t i = 0; i < nodeStr.length() && left + curr_width/2 + i < output[top].length(); i++)
			// 20200907: there is a length limit on the keys. If exceeded a
			// segmentation faults will happen. This check is a temporary
			// workaround that prevents the segfault, but some data will be
			// lost.
			if (left + curr_width/2 + left_start_shift + i < output[top].size())
				output[top][left + curr_width/2 + left_start_shift + i] = nodeStr[i];

		// Calculate / \ offset = 2 ^ height
		int branchOffset = (curr_width+3) >> 3; //(1 << (node->printData - 1));

		// Print left child
		int center = left + curr_width/2;
		int leftcenter = left + (curr_width/2 - 1)/2;
		int rightcenter = left + curr_width/2 + 2 + (curr_width/2 - 1)/2;

		if (!croot.left().isNull())
		{
			int branch_pos = center - branchOffset + 1;
			// draw left upper branch
			for (int pos = center + left_start_shift - 2; pos > branch_pos; pos--)
				output[top][pos] = '_';
			// draw left '/'
			output[top+1][branch_pos] = '/';
			// draw left lower branch
			for (int pos = branch_pos-1; pos > leftcenter + 2; pos--)
				output[top+1][pos] = '_';
			// draw left subtree
			printSubtree(croot.left(), output, left, top+2, curr_width/2 - 1);
		}

		// Print right child
		if (!croot.right().isNull())
		{
			int branch_pos = center + branchOffset + 1;
			// draw right upper branch
			for (int pos = center + left_start_shift + nodeStr.length() + 1; pos < branch_pos; pos++)
				output[top][pos] = '_';
			// draw right '\'
			output[top+1][branch_pos] = '\\';
			// draw right lower branch
			for (int pos = branch_pos+1; pos < rightcenter; pos++)
				output[top+1][pos] = '_';
			// draw right subtree
			printSubtree(croot.right(), output, left + curr_width/2 + 2, top+2, curr_width/2 - 1);
		}
	}
}

}

#endif
