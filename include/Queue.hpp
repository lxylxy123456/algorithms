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

#ifndef ALGORITHMS_QUEUE
#define ALGORITHMS_QUEUE

#include <stdexcept>

namespace algorithms {

template <typename T>
class Queue {
	public:
		Queue(size_t size): head(0), tail(0), length(size), data(new T[size]) {}
		void Enqueue(T x) {
			data[tail++] = x;
			if (tail == length)
				tail = 0;
			if (tail == head)
				throw std::invalid_argument("overflow");
		}
		T Dequeue() {
			if (head == tail)
				throw std::invalid_argument("underflow");
			T& ans = data[head++];
			if (head == length)
				head = 0;
			return ans;
		}
		bool Empty() {
			return head == tail;
		}
		~Queue() { delete [] data; }
	private:
		size_t head, tail, length;
		T* data;
};

}

#endif
