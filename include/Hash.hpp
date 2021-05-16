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

#ifndef ALGORITHMS_HASH
#define ALGORITHMS_HASH

#include <cstddef>

#include "random_integers.hpp"

using std::size_t;

namespace algorithms {

class DivisionHash {
	public:
		DivisionHash(std::size_t mm): m(mm) {}
		std::size_t operator()(std::size_t k) { return k % m; }
		std::size_t m;
};

class MultiplicationHash {
	public:
		MultiplicationHash(std::size_t ww, std::size_t pp, float A):
			w(ww), K(1 << w), p(pp), s(A * K), m(1 << p) {}
		std::size_t operator()(std::size_t k) {
			return ((k * s) & (K - 1)) >> (w - p);
		}
		std::size_t w, K, p, s, m;
};

class UniversalHash {
	public:
		UniversalHash(std::size_t pp, std::size_t mm): p(pp), m(mm) {
			a = random_integer<std::size_t>(1, p - 1);
			b = random_integer<std::size_t>(0, p - 1);
		}
		std::size_t operator()(std::size_t k) {
			return ((a * k + b) % p) % m;
		}
		std::size_t p, m, a, b;
};

}

#endif
