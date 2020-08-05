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

#ifndef ALGORITHMS_STACK
#define ALGORITHMS_STACK

#include <exception>
#include "utils.h"

namespace algorithms {

template <typename T>
class Stack {
	public:
		Stack(size_t size): top(0), data(new T[size]) {}
		bool StackEmpty() { return top == 0; }
		void Push(T x) { data[top++] = x; }
		T Pop() {
			if (StackEmpty())
				throw std::invalid_argument("underflow");
			else
				return data[--top];
		}
		void MultiPop(size_t k) {
			while (!StackEmpty() && k--)
				Pop();
		}
		~Stack() { delete [] data; }
	private:
		size_t top;
		T* data;
};

}

#endif
