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
#define MAIN_DirectAddress
#endif

#ifndef FUNC_DirectAddress
#define FUNC_DirectAddress

#include <vector>
#include <exception>
#include "utils.h"

template <typename T>
class DirectAddress {
	public:
		DirectAddress(size_t s): size(s), data(new T*[size]) {}
		T* DirectAddressSearch(size_t k) {
			return data[k]; 
		}
		void DirectAddressInsert(size_t k, T x) {
			if (data[k])
				delete data[k]; 
			data[k] = new T(x); 
		}
		void DirectAddressDelete(size_t k) {
			delete data[k]; 
			data[k] = nullptr; 
		}
		~DirectAddress() {
			for (size_t i = 0; i < size; i++)
				if (data[i])
					delete data[i]; 
			delete [] data; 
		}
	private:
		size_t size; 
		T** data; 
}; 
#endif

#ifdef MAIN_DirectAddress
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 16); 
	DirectAddress<int> D(n); 
	std::cout << "d: delete" << std::endl; 
	std::cout << "i: insert" << std::endl; 
	std::cout << "s: search" << std::endl; 
	std::cout << "q: quit" << std::endl; 
	while (true) {
		char c; size_t k; int x; 
		std::cout << ">> "; 
		if (!(std::cin >> c)) {
			std::cout << std::endl; 
			break; 
		}
		if (c == 'q')
			break; 
		std::cout << "k = "; 
		std::cin >> k; 
		switch (c) {
			case 'i': 
				std::cout << "x = "; 
				std::cin >> x; 
				D.DirectAddressInsert(k, x); 
				break; 
			case 'd': 
				D.DirectAddressDelete(k); 
				break; 
			case 's':
				int* ans = D.DirectAddressSearch(k); 
				if (ans)
					std::cout << *ans << std::endl; 
				else
					std::cout << "nullptr" << std::endl; 
				break; 
		}
	}
	return 0; 
}
#endif

