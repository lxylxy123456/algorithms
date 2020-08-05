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

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <string>
#include <sstream>

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

template <typename T>
void input_integers(std::vector<T>& a) {
	std::copy(	std::istream_iterator<T>(std::cin),
				std::istream_iterator<T>(),
				std::insert_iterator<std::vector<T>>(a, a.begin()));
}

template <typename T>
void output_integers(const T& a, const char* sep) {
	std::copy(a.begin(), a.end(),
				std::ostream_iterator<typename T::value_type>(std::cout, sep));
	std::cout << std::endl;
}

template <typename T>
void output_integers(const T& a) {
	output_integers(a, " ");
}

template <typename T>
T get_argv(int argc, char *argv[], int index, T def) {
	if (index < 0 || index >= argc)
		return def;
	T ans;
	std::istringstream(argv[index]) >> ans;
	return ans;
}

template <typename T>
std::string pptr(T p) {
	// print a pointer of type T
	void* vp = static_cast<void*>(p);
	if (vp) {
		std::ostringstream os;
		os << vp;
		return os.str();
	} else
		return "nullptr";
}
#endif
