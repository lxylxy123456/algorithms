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

#ifndef ALGORITHMS_STORAGEMANAGE
#define ALGORITHMS_STORAGEMANAGE

#include <cassert>
#include <stdexcept>

namespace algorithms {

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

}

#endif
