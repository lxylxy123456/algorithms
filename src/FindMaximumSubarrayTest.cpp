//  
//  algorithm - some algorithms in "Introduction to Algorithms", third edition
//  Copyright (C) 2020  lxylxy123456
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

#include "FindMaximumSubarray.hpp"
#include "utils.h"

#include <cassert>

using namespace algorithms;

int test_vector(int n) {
	std::vector<int> a; 
	random_integers(a, -n, n, n); 
	output_integers(a); 
	sinfo<int> ans2 = FindMaximumSubarray(a); 
	sinfo<int> ans1 = FindMaximumSubarray_On<int, 0>(a); 
	assert(ans2.begin == ans1.begin && ans2.end == ans1.end);
	return 0; 
}

int main(int argc, char *argv[]) {
	test_vector(1);
	test_vector(2);
	test_vector(10);
	test_vector(49);
	test_vector(100);
	return 0;
}
