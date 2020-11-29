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

#ifndef ALGORITHMS_LINKEDLIST
#define ALGORITHMS_LINKEDLIST

namespace algorithms {

template <typename T>
class Element {
	public:
		Element(void) {}
		Element(T k): key(k) {}
		Element(T k, Element<T>* p, Element<T>* n): key(k), prev(p), next(n) {}
		bool operator==(const Element<T>& rhs) const { return key == rhs.key; }
		bool operator!=(const Element<T>& rhs) const { return key != rhs.key; }
		bool operator==(const T& rhs) const { return key == rhs; }
		bool operator!=(const T& rhs) const { return key != rhs; }
		T key;
		Element<T> *prev, *next;
};

template <typename T>
class LinkedListBase {
	public:
		LinkedListBase(void) {}
		virtual Element<T>* ListSearch(T x) = 0;
		virtual void ListInsert(T x) = 0;
		virtual void ListDelete(Element<T>* x) = 0;
		virtual ~LinkedListBase() {}
};

template <typename T>
class LinkedList: public LinkedListBase<T> {
	public:
		LinkedList(void): head(nullptr) {}
		virtual Element<T>* ListSearch(T x) {
			Element<T>* i = head;
			while (i != nullptr && *i != x)
				i = i->next;
			return i;
		}
		virtual void ListInsert(T x) {
			head = new Element<T>(x, nullptr, head);
			if (head->next)
				head->next->prev = head;
		}
		virtual void ListDelete(Element<T>* x) {
			if (x->next)
				x->next->prev = x->prev;
			if (x->prev)
				x->prev->next = x->next;
			else
				head = x->next;
			delete x;
		}
		virtual ~LinkedList() {
			for (Element<T>* i = head; i != nullptr; ) {
				Element<T>* tmp = i;
				i = i->next;
				delete tmp;
			}
		}
	private:
		Element<T>* head;
};

template <typename T>
class LinkedList_prime: public LinkedListBase<T> {
	public:
		LinkedList_prime(void): nil(new Element<T>()) {
			nil->next=nil;
			nil->prev=nil;
		}
		virtual void ListDelete(Element<T>* x) { ListDelete_prime(x); }
		virtual Element<T>* ListSearch(T x) { return ListSearch_prime(x); }
		virtual void ListInsert(T x) { ListInsert_prime(x); }
		virtual void ListDelete_prime(Element<T>* x) {
			x->next->prev = x->prev;
			x->prev->next = x->next;
			delete x;
		}
		virtual Element<T>* ListSearch_prime(T x) {
			Element<T>* i = nil->next;
			while (i != nil && *i != x)
				i = i->next;
			return i;
		}
		virtual void ListInsert_prime(T x) {
			nil->next = new Element<T>(x, nil, nil->next);
			nil->next->next->prev = nil->next;
		}
		virtual ~LinkedList_prime() {
			for (Element<T>* i = nil->next; i != nil; ) {
				Element<T>* tmp = i;
				i = i->next;
				delete tmp;
			}
			delete nil;
		}
	private:
		Element<T>* nil;
};

}

#endif
