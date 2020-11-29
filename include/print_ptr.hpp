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

#ifndef ALGORITHMS_PRINT_PTR
#define ALGORITHMS_PRINT_PTR

#include <iostream>
#include <sstream>
#include <string>

namespace algorithms {

template <typename T>
std::string pptr(T p) {
	// print a pointer of type T
	void* vp = static_cast<void*>(p);
	if (vp) {
		std::ostringstream os;
		os << vp;
		return os.str();
	} else
		return "nullptr";
}

template <typename T>
void print_ptr(T ptr, T nil) {
	std::cout << "ptr = " << pptr(ptr) << std::endl;
	if (ptr == nil)
		std::cout << "    = nil" << std::endl;
	else
		std::cout << "val = " << ptr->data << std::endl;
}

}

#endif
