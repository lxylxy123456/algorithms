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

#ifndef ALGORITHMS_OPENADDRESS
#define ALGORITHMS_OPENADDRESS

#include <stdexcept>

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
class OpenAddress {
	public:
		OpenAddress(size_t s): size(s), data(new Pair<T>*[size]) {
			for (size_t i = 0; i < s; i++)
				data[i] = nullptr;
		}
		size_t HashInsert(size_t k, T v) {
			for (size_t i = 0; i < size; i++) {
				size_t j = h(k, i);
				if (!data[j]) {
					data[j] = new Pair<T>(k, v);
					return j;
				}
			}
			throw std::invalid_argument("hash table overflow");
		}
		const Pair<T>* HashSearch(T k) {
			for (size_t i = 0; i < size; i++) {
				size_t j = h(k, i);
				if (!data[j])
					break;
				if (*data[j] == k)
					return data[j];
			}
			return nullptr;
		}
		size_t h(size_t k, size_t i) {
			return (k + i) % size;
		}
		~OpenAddress() {
			for (size_t i = 0; i < size; i++)
				if (data[i])
					delete data[i];
			delete [] data;
		}
	private:
		size_t size;
		Pair<T>** data;
};

}

#endif
