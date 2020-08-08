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

#ifndef ALGORITHMS_RANDOM_INTEGERS
#define ALGORITHMS_RANDOM_INTEGERS

#include <vector>
#include <random>

namespace algorithms {

void random_integers(std::vector<int>& a, int l, int u, size_t size) {
	a.reserve(size);
    std::random_device rd;
    std::uniform_int_distribution<int> d(l, u);
	for (size_t i = 0; i < size; i++)
		a.push_back(d(rd));
}

template <typename T>
void random_integers(std::vector<T>& a, T l, T u, size_t size) {
	a.reserve(size);
    std::random_device rd;
    std::uniform_int_distribution<T> d(l, u);
	for (size_t i = 0; i < size; i++)
		a.push_back(d(rd));
}

}

#endif