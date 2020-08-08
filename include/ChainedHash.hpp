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

#ifndef ALGORITHMS_CHAINEDHASH
#define ALGORITHMS_CHAINEDHASH

#include <cstddef>

#include "LinkedList.hpp"

namespace algorithms {

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

}

#endif
