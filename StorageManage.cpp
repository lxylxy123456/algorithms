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
#define MAIN_StorageManage
#endif

#ifndef FUNC_StorageManage
#define FUNC_StorageManage

#include <cassert>
#include <exception>
#include "utils.h"

template <typename T>
class Data {
	public:
		Data(void) {}
		Data(T k): key(k) {}
		Data(size_t n) { next() = n; }
		bool operator==(const Data<T>& rhs) const { return key == rhs.key; }
		bool operator!=(const Data<T>& rhs) const { return key != rhs.key; }
		bool operator==(const T& rhs) const { return key == rhs; }
		bool operator!=(const T& rhs) const { return key != rhs; }
		size_t& next() { return *reinterpret_cast<size_t*>(&key); }
		T key; 
}; 

template <typename T>
class StorageManage {
	public:
		StorageManage(size_t n): data(new Data<T>[n]), len(n), free(1) {
			assert(sizeof(T) >= sizeof(size_t)); 
			for (size_t i = 0; i < n - 1; i++)
				data[i].next() = i + 2; 
			data[n - 1].next() = 0; 
		}
		Data<T>* AllocateObject() {
			if (!free)
				throw std::invalid_argument("out of space"); 
			else {
				size_t x = free - 1; 
				free = data[x].next(); 
				return data + x; 
			}
		}
		void FreeObject(Data<T>* x) {
			x->next() = free; 
			free = x - data + 1; 
		}
		~StorageManage() {
			delete [] data; 
		}
	private:
		Data<T>* data; 
		size_t len, free; 
}; 
#endif

#ifdef MAIN_StorageManage
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 16); 
	StorageManage<long int> S(n); 
	std::vector<Data<long int>*> allocated; 
	std::cout << "a: alloc" << std::endl; 
	std::cout << "f: free" << std::endl; 
	std::cout << "q: quit" << std::endl; 
	while (true) {
		char c; int x; Data<long int>* ans; 
		std::cout << ">> "; 
		if (!(std::cin >> c)) {
			std::cout << std::endl; 
			break; 
		}
		if (c == 'q')
			break; 
		switch (c) {
			case 'a': 
				ans = S.AllocateObject(); 
				allocated.push_back(ans); 
				std::cout << static_cast<void*>(ans) << std::endl; 
				break; 
			case 'f': 
				for (size_t i = 0; i < allocated.size(); i++)
					std::cout << "[" << i << "] = "
							 << static_cast<void*>(allocated[i]) << std::endl; 
				std::cout << "x = "; 
				std::cin >> x; 
				S.FreeObject(allocated[x]); 
				allocated.erase(allocated.begin() + x, allocated.begin() + x+1);
				break; 
		}
	}
	return 0; 
}
#endif

