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

#ifndef MAIN
#define MAIN
#define MAIN_MaxHeap
#endif

#ifndef FUNC_MaxHeap
#define FUNC_MaxHeap

#include <vector>
#include <exception>
#include "utils.h"

inline size_t Left(size_t x) { return x * 2 + 1; }

inline size_t Right(size_t x) { return x * 2 + 2; }

inline size_t Parent(size_t x) { return (x - 1) / 2; }

inline size_t Root(size_t x) { return !x; }

template <typename T>
class Heap: public std::vector<T> {
	public: 
		Heap(void): std::vector<T>(), heap_size(0) {}
		Heap(std::vector<T>& v): std::vector<T>(v), heap_size(0) {}
		Heap(std::vector<T>& v, size_t hs): std::vector<T>(v), heap_size(hs) {}
		void MaxHeapify(size_t i) {
			size_t l = Left(i), r = Right(i); 
			size_t largest = i; 
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
			for(size_t i = heap_size / 2; i-- > 0;)
				MaxHeapify(i); 
		}
		void HeapSort() {
			while (heap_size) {
				heap_size--; 
				std::swap((*this)[0], (*this)[heap_size]); 
				MaxHeapify(0); 
			}
		}
		size_t heap_size; 
}; 

template <typename T>
class PriorityQueue: public Heap<T> {
	public:
		PriorityQueue(void): Heap<T>() {}
		PriorityQueue(std::vector<T>& v): Heap<T>(v) {}
		PriorityQueue(std::vector<T>& v, size_t hs): Heap<T>(v, hs) {}
		T HeapMaximum() {
			return (*this)[0]; 
		}
		T HeapExtractMax() {
			size_t& heap_size = Heap<T>::heap_size; 
			if (!heap_size)
				throw std::invalid_argument("heap underflow"); 
			heap_size--; 
			std::swap((*this)[0], (*this)[heap_size]); 
			Heap<T>::MaxHeapify(0); 
			return (*this)[heap_size]; 
		}
		void HeapIncreaseKey(size_t i, T key) {
			if (key < (*this)[i])
				throw std::invalid_argument("new key is smaller than current"); 
			(*this)[i] = key; 
			while (i != 0 && (*this)[Parent(i)] < (*this)[i]) {
				std::swap((*this)[Parent(i)], (*this)[i]); 
				i = Parent(i); 
			}
		}
		void MaxHeapInsert(T key) {
			size_t& heap_size = Heap<T>::heap_size; 
			HeapIncreaseKey(heap_size, key); 
			heap_size += 1; 
		}
		void BuildMaxHeap_prime() {
			Heap<T>::heap_size = 1; 
			for(size_t i = 1; i < std::vector<T>::size(); i++)
				MaxHeapInsert((*this)[i]); 
		}
}; 
#endif

#ifdef MAIN_MaxHeap
int main(int argc, char *argv[]) {
	std::vector<int> data = {4, 16, 10, 14, 7, 9, 3, 2, 8, 1}; 
	Heap<int> a(data), b; 
	PriorityQueue<int> c; 
	int n = get_argv(argc, argv, 2, 16); 
	switch(get_argv(argc, argv, 1, 0)) {
		case 1:	// test MaxHeapify
			output_integers(a); 
			a.MaxHeapify(0); 
			output_integers(a); 
			break; 
		case 2: // test BuildMaxHeap and HeapSort
			random_integers(b, 0, n - 1, n); 
			output_integers(b); 
			b.BuildMaxHeap(); 
			output_integers(b); 
			b.HeapSort(); 
			output_integers(b); 
			break; 
		case 3:	// test PriorityQueue
			for (auto i : data) {
				c.push_back(i); 
				c.MaxHeapInsert(i); 
			}
			output_integers(c); 
			std::cout << "Max == " << c.HeapMaximum() << " == "; 
			std::cout << c.HeapExtractMax() << std::endl; 
			c.pop_back(); 
			output_integers(c); 
			c.HeapIncreaseKey(c.heap_size - 1, 19); 
			output_integers(c); 
			c.HeapIncreaseKey(c.heap_size - 1, 11); 
			output_integers(c); 
			break; 
		case 4: // test BuildMaxHeap_prime
			random_integers(b, 0, n - 1, n); 
			output_integers(b); 
			c = PriorityQueue<int>(b); 
			b.BuildMaxHeap(); 
			c.BuildMaxHeap_prime(); 
			output_integers(b); 
			output_integers(c); 
			break; 
		default: 
			std::cout << "No Action" << std::endl; 
			break; 
	}
	return 0; 
}
#endif

