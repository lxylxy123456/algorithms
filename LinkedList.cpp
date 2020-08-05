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
#define MAIN_LinkedList
#endif

#ifndef FUNC_LinkedList
#define FUNC_LinkedList

#include "utils.h"

template <typename T>
class Data {
	public:
		Data(void) {}
		Data(T k): key(k) {}
		Data(T k, Data<T>* p, Data<T>* n): key(k), prev(p), next(n) {}
		bool operator==(const Data<T>& rhs) const { return key == rhs.key; }
		bool operator!=(const Data<T>& rhs) const { return key != rhs.key; }
		bool operator==(const T& rhs) const { return key == rhs; }
		bool operator!=(const T& rhs) const { return key != rhs; }
		T key;
		Data<T> *prev, *next;
};

template <typename T>
class LinkedListBase {
	public:
		LinkedListBase(void) {}
		virtual Data<T>* ListSearch(T x) = 0;
		virtual void ListInsert(T x) = 0;
		virtual void ListDelete(Data<T>* x) = 0;
		virtual ~LinkedListBase() {}
};

template <typename T>
class LinkedList: public LinkedListBase<T> {
	public:
		LinkedList(void): head(nullptr) {}
		virtual Data<T>* ListSearch(T x) {
			Data<T>* i = head;
			while (i != nullptr && *i != x)
				i = i->next;
			return i;
		}
		virtual void ListInsert(T x) {
			head = new Data<T>(x, nullptr, head);
			if (head->next)
				head->next->prev = head;
		}
		virtual void ListDelete(Data<T>* x) {
			if (x->next)
				x->next->prev = x->prev;
			if (x->prev)
				x->prev->next = x->next;
			else
				head = x->next;
			delete x;
		}
		virtual ~LinkedList() {
			for (Data<T>* i = head; i != nullptr; ) {
				Data<T>* tmp = i;
				i = i->next;
				delete tmp;
			}
		}
	private:
		Data<T>* head;
};

template <typename T>
class LinkedList_prime: public LinkedListBase<T> {
	public:
		LinkedList_prime(void): nil(new Data<T>()) {
			nil->next=nil;
			nil->prev=nil;
		}
		virtual void ListDelete(Data<T>* x) { ListDelete_prime(x); }
		virtual Data<T>* ListSearch(T x) { return ListSearch_prime(x); }
		virtual void ListInsert(T x) { ListInsert_prime(x); }
		virtual void ListDelete_prime(Data<T>* x) {
			x->next->prev = x->prev;
			x->prev->next = x->next;
			delete x;
		}
		virtual Data<T>* ListSearch_prime(T x) {
			Data<T>* i = nil->next;
			while (i != nil && *i != x)
				i = i->next;
			return i;
		}
		virtual void ListInsert_prime(T x) {
			nil->next = new Data<T>(x, nil, nil->next);
			nil->next->prev = nil->next;
		}
		virtual ~LinkedList_prime() {
			for (Data<T>* i = nil; i != nil; ) {
				Data<T>* tmp = i;
				i = i->next;
				delete tmp;
			}
		}
	private:
		Data<T>* nil;
};
#endif

#ifdef MAIN_LinkedList
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 0);
	LinkedListBase<int>* S;
	if (n)
		S = new LinkedList_prime<int>;
	else
		S = new LinkedList<int>;
	std::cout << "d: delete" << std::endl;
	std::cout << "i: insert" << std::endl;
	std::cout << "s: search" << std::endl;
	std::cout << "q: quit" << std::endl;
	while (true) {
		char c; int x;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		if (c == 'q')
			break;
		std::cout << "x = ";
		std::cin >> x;
		switch (c) {
			case 'i':
				S->ListInsert(x);
				break;
			case 'd':
				S->ListDelete(S->ListSearch(x));
				break;
			case 's':
				std::cout << pptr(S->ListSearch(x)) << std::endl;
				break;
		}
	}
	return 0;
}
#endif

