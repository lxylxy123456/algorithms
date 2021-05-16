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

#ifndef ALGORITHMS_MAXHEAP
#define ALGORITHMS_MAXHEAP

#include <algorithm>
#include <stdexcept>
#include <vector>

using std::size_t;

namespace algorithms {

inline std::size_t Left(size_t x) { return x * 2 + 1; }

inline std::size_t Right(size_t x) { return x * 2 + 2; }

inline std::size_t Parent(size_t x) { return (x - 1) / 2; }

inline std::size_t Root(size_t x) { return !x; }

template <typename T>
class Heap: public std::vector<T> {
	public:
		Heap(void): std::vector<T>(), heap_size(0) {}
		Heap(std::vector<T>& v): std::vector<T>(v), heap_size(0) {}
		Heap(std::vector<T>& v, std::size_t hs): std::vector<T>(v), heap_size(hs) {}
		void MaxHeapify(std::size_t i) {
			std::size_t l = Left(i), r = Right(i);
			std::size_t largest = i;
			if (l < heap_size && (*this)[l] > (*this)[i])
				largest = l;
			if (r < heap_size && (*this)[r] > (*this)[largest])
				largest = r;
			if (largest != i) {
				std::swap((*this)[largest], (*this)[i]);
				MaxHeapify(largest);
			}
		}
		void BuildMaxHeap() {
			heap_size = std::vector<T>::size();
			for(std::size_t i = heap_size / 2; i-- > 0;)
				MaxHeapify(i);
		}
		void HeapSort() {
			while (heap_size) {
				heap_size--;
				std::swap((*this)[0], (*this)[heap_size]);
				MaxHeapify(0);
			}
		}
		std::size_t heap_size;
};

template <typename T>
class PriorityQueue: public Heap<T> {
	public:
		PriorityQueue(void): Heap<T>() {}
		PriorityQueue(std::vector<T>& v): Heap<T>(v) {}
		PriorityQueue(std::vector<T>& v, std::size_t hs): Heap<T>(v, hs) {}
		T HeapMaximum() {
			return (*this)[0];
		}
		T HeapExtractMax() {
			std::size_t& heap_size = Heap<T>::heap_size;
			if (!heap_size)
				throw std::invalid_argument("heap underflow");
			heap_size--;
			std::swap((*this)[0], (*this)[heap_size]);
			Heap<T>::MaxHeapify(0);
			return (*this)[heap_size];
		}
		void HeapIncreaseKey(std::size_t i, T key) {
			if (key < (*this)[i])
				throw std::invalid_argument("new key is smaller than current");
			(*this)[i] = key;
			while (i != 0 && (*this)[Parent(i)] < (*this)[i]) {
				std::swap((*this)[Parent(i)], (*this)[i]);
				i = Parent(i);
			}
		}
		void MaxHeapInsert(T key) {
			std::size_t& heap_size = Heap<T>::heap_size;
			HeapIncreaseKey(heap_size, key);
			heap_size += 1;
		}
		void BuildMaxHeap_prime() {
			Heap<T>::heap_size = 1;
			for(std::size_t i = 1; i < std::vector<T>::size(); i++)
				MaxHeapInsert((*this)[i]);
		}
};

}

#endif
