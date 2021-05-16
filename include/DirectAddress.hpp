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

#ifndef ALGORITHMS_DIRECTADDRESS
#define ALGORITHMS_DIRECTADDRESS

#include <cstddef>

using std::size_t;

namespace algorithms {

template <typename T>
class DirectAddress {
	public:
		DirectAddress(size_t s): size(s), data(new T*[size]) {
			for (size_t i = 0; i < size; i++)
				data[i] = nullptr;
		}
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

}

#endif
