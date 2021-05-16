//
//  algorithms - some algorithms in "Introduction to Algorithms", third edition
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

#include <random>
#include <vector>

using std::size_t;

namespace algorithms {

static std::random_device random_dev;
static std::random_device::result_type random_seed(random_dev());
static std::mt19937 random_gen(random_seed);

void random_seed_reset(std::random_device::result_type seed) {
	random_seed = seed;
	random_gen.seed(seed);
}

std::random_device::result_type random_seed_get() {
	return random_seed;
}

template <typename T>
T random_integer(T l, T u) {
	return std::uniform_int_distribution<T>(l, u)(random_gen);
}

template <typename T>
T random_integer(std::uniform_int_distribution<T> dis) {
	return dis(random_gen);
}

void random_integers(std::vector<int>& a, int l, int u, std::size_t size) {
	a.reserve(size);
	std::uniform_int_distribution<int> d(l, u);
	for (std::size_t i = 0; i < size; i++)
		a.push_back(d(random_gen));
}

template <typename T>
void random_integers(std::vector<T>& a, T l, T u, std::size_t size) {
	a.reserve(size);
	std::uniform_int_distribution<T> d(l, u);
	for (std::size_t i = 0; i < size; i++)
		a.push_back(d(random_gen));
}

}

#endif
