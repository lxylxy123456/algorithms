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
#define MAIN_ChainedHash
#endif

#ifndef FUNC_ChainedHash
#define FUNC_ChainedHash

#include "utils.h"
#include "LinkedList.cpp"

template <typename T>
class Pair {
	public: 
		Pair(size_t k): key(k) {}
		Pair(size_t k, T v): key(k), value(v) {}
		bool operator==(const Pair& rhs) const { return key == rhs.key; }
		bool operator!=(const Pair& rhs) const { return key != rhs.key; }
		size_t key; 
		T value; 
}; 

template <typename T>
class ChainedHash {
	public:
		ChainedHash(size_t s): size(s), data(new LinkedList<Pair<T>>[size]) {}
		void ChainedHashInsert(size_t k, T x) {
			data[h(k)].ListInsert(Pair<T>(k, x)); 
		}
		Data<Pair<T>>* ChainedHashSearch(size_t k) {
			return data[h(k)].ListSearch(k); 
		}
		void ChainedHashDelete(Data<Pair<T>>* p) {
			data[h(p->key.key)].ListDelete(p); 
		}
		size_t h(size_t k) {
			return k % size; 
		}
		~ChainedHash() {
			delete [] data; 
		}
	private:
		size_t size; 
		LinkedList<Pair<T>>* data; 
}; 
#endif

#ifdef MAIN_ChainedHash
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 16); 
	ChainedHash<int> D(n); 
	std::cout << "d: delete" << std::endl; 
	std::cout << "i: insert" << std::endl; 
	std::cout << "s: search" << std::endl; 
	std::cout << "q: quit" << std::endl; 
	while (true) {
		char c; size_t k; int v; 
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
				std::cout << "v = "; 
				std::cin >> v; 
				D.ChainedHashInsert(k, v); 
				break; 
			case 'd': 
				D.ChainedHashDelete(D.ChainedHashSearch(k)); 
				break; 
			case 's':
				Data<Pair<int>>* ans = D.ChainedHashSearch(k); 
				if (ans)
					std::cout << ans->key.key << ": "
							 << ans->key.value << std::endl; 
				else
					std::cout << "nullptr" << std::endl; 
				break; 
		}
	}
	return 0; 
}
#endif

