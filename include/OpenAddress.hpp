//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#include "ChainedHash.hpp"

using std::size_t;

namespace algorithms {

template <typename T>
class OpenAddress {
	public:
		OpenAddress(std::size_t s): size(s), data(new Pair<T>*[size]) {
			for (std::size_t i = 0; i < s; i++)
				data[i] = nullptr;
		}
		std::size_t HashInsert(std::size_t k, T v) {
			for (std::size_t i = 0; i < size; i++) {
				std::size_t j = h(k, i);
				if (!data[j]) {
					data[j] = new Pair<T>(k, v);
					return j;
				}
			}
			throw std::invalid_argument("hash table overflow");
		}
		const Pair<T>* HashSearch(T k) {
			for (std::size_t i = 0; i < size; i++) {
				std::size_t j = h(k, i);
				if (!data[j])
					break;
				if (*data[j] == k)
					return data[j];
			}
			return nullptr;
		}
		std::size_t h(std::size_t k, std::size_t i) {
			return (k + i) % size;
		}
		~OpenAddress() {
			for (std::size_t i = 0; i < size; i++)
				if (data[i])
					delete data[i];
			delete [] data;
		}
	private:
		std::size_t size;
		Pair<T>** data;
};

}

#endif
