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
#define MAIN_vEB
#endif

#ifndef FUNC_vEB
#define FUNC_vEB

#include "utils.h"

const size_t NIL = -1;

class vEB {
	public:
		vEB(size_t kk): k(kk), u(1 << k), min(NIL), max(NIL),
						lsqrt_bit(k / 2), lsqrtu(1 << lsqrt_bit),
						usqrt_bit((k - 1) / 2 + 1), usqrtu(1 << usqrt_bit) {
			if (k > 1) {
				summary = new vEB(usqrt_bit);
				cluster = new vEB* [usqrtu];
				for (size_t i = 0; i < usqrtu; i++)
					cluster[i] = new vEB(lsqrt_bit);
			}
		}
		// indexing
		size_t high(size_t x) { return x >> lsqrt_bit; }
		size_t low(size_t x) { return x & (lsqrtu - 1); }
		size_t index(size_t x, size_t y) { return x << lsqrt_bit | y; }
		// algorithms
		size_t vEBTreeMinimum() {
			return min;
		}
		size_t vEBTreeMaximum() {
			return max;
		}
		bool vEBTreeMember(size_t x) {
			if (x == min || x == max)
				return true;
			else if (k == 1)
				return false;
			else
				return cluster[high(x)]->vEBTreeMember(low(x));
		}
		size_t vEBTreeSuccessor(size_t x) {
			if (k == 1) {
				if (x == 0 && max == 1)
					return 1;
				else
					return NIL;
			} else if (min != NIL && x < min)
				return min;
			else {
				size_t hx = high(x), lx = low(x);
				size_t max_low = cluster[hx]->vEBTreeMaximum();
				if (max_low != NIL && lx < max_low) {
					size_t offset = cluster[hx]->vEBTreeSuccessor(lx);
					return index(hx, offset);
				} else {
					size_t succ_c = summary->vEBTreeSuccessor(hx);
					if (succ_c == NIL)
						return NIL;
					else {
						size_t offset = cluster[succ_c]->vEBTreeMinimum();
						return index(succ_c, offset);
					}
				}
			}
		}
		size_t vEBTreePredecessor(size_t x) {
			if (k == 1) {
				if (x == 1 && min == 0)
					return 0;
				else
					return NIL;
			} else if (max != NIL && x > max)
				return max;
			else {
				size_t hx = high(x), lx = low(x);
				size_t min_low = cluster[hx]->vEBTreeMinimum();
				if (min_low != NIL && lx > min_low) {
					size_t offset = cluster[hx]->vEBTreePredecessor(lx);
					return index(hx, offset);
				} else {
					size_t pred_c = summary->vEBTreePredecessor(hx);
					if (pred_c == NIL) {
						if (min != NIL && x > min)
							return min;
						else
							return NIL;
					} else {
						size_t offset = cluster[pred_c]->vEBTreeMaximum();
						return index(pred_c, offset);
					}
				}
			}
		}
		void vEBEmptyTreeInsert(size_t x) {
			min = x;
			max = x;
		}
		void vEBTreeInsert(size_t x) {
			if (min == NIL)
				vEBEmptyTreeInsert(x);
			else {
				if (x < min)
					std::swap(x, min);
				if (k > 1) {
					if (cluster[high(x)]->vEBTreeMinimum() == NIL) {
						summary->vEBTreeInsert(high(x));
						cluster[high(x)]->vEBEmptyTreeInsert(low(x));
					} else
						cluster[high(x)]->vEBTreeInsert(low(x));
				}
				if (x > max)
					max = x;
			}
		}
		void vEBTreeDelete(size_t x) {
			if (min == max) {
				min = NIL;
				max = NIL;
			} else if (k == 1) {
				if (x == 0)
					min = 1;
				else
					min = 0;
				max = min;
			} else {
				if (x == min) {
					size_t first_c = summary->vEBTreeMinimum();
					x = index(first_c, cluster[first_c]->vEBTreeMinimum());
					min = x;
				}
				cluster[high(x)]->vEBTreeDelete(low(x));
				if (cluster[high(x)]->vEBTreeMinimum() == NIL) {
					summary->vEBTreeDelete(high(x));
					if (x == max) {
						size_t summ_max = summary->vEBTreeMaximum();
						if (summ_max == NIL)
							max = min;
						else {
							size_t offset = cluster[summ_max]->vEBTreeMaximum();
							max = index(summ_max, offset);
						}
					}
				} else if (x == max) {
					max = index(high(x), cluster[high(x)]->vEBTreeMaximum());
				}
			}
		}
		// members
		vEB* summary;
		vEB** cluster;
		~vEB() {
			if (k > 1) {
				for (size_t i = 0; i < usqrtu; i++)
					delete cluster[i];
				delete [] cluster;
				delete summary;
			}
		}
		size_t k, u, min, max, lsqrt_bit, lsqrtu, usqrt_bit, usqrtu;
};
#endif

#ifdef MAIN_vEB
void print(size_t x) {
	if (x == NIL)
		std::cout << "NIL" << std::endl;
	else
		std::cout << x << std::endl;
}

void print(bool x) {
	std::cout << std::boolalpha << x << std::endl;
}

int main(int argc, char *argv[]) {
	const size_t k = get_argv(argc, argv, 1, 16);
	if (k > 16)
		throw std::invalid_argument("k too large");
	vEB Pv(k);
	std::cout << "m: member" << std::endl;
	std::cout << "-: minimum" << std::endl;
	std::cout << "+: maximum" << std::endl;
	std::cout << "p: predecessor" << std::endl;
	std::cout << "s: successor" << std::endl;
	std::cout << "i: insert" << std::endl;
	std::cout << "d: delete" << std::endl;
	std::cout << "P: print all" << std::endl;
	std::cout << "q: quit" << std::endl;
	while (true) {
		char c; size_t x; std::vector<size_t> l;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		switch (c) {
			case 'm':
				std::cout << "x = ";
				std::cin >> x;
				print(Pv.vEBTreeMember(x));
				break;
			case '-':
				print(Pv.vEBTreeMinimum());
				break;
			case '+':
				print(Pv.vEBTreeMaximum());
				break;
			case 'p':
				std::cout << "x = ";
				std::cin >> x;
				print(Pv.vEBTreePredecessor(x));
				break;
			case 's':
				std::cout << "x = ";
				std::cin >> x;
				print(Pv.vEBTreeSuccessor(x));
				break;
			case 'i':
				std::cout << "x = ";
				std::cin >> x;
				Pv.vEBTreeInsert(x);
				break;
			case 'd':
				std::cout << "x = ";
				std::cin >> x;
				Pv.vEBTreeDelete(x);
				break;
			case 'P':
				for (size_t i = 0; i < Pv.u; i++)
					if (Pv.vEBTreeMember(i))
						l.push_back(i);
				output_integers(l);
				break;
			case 'q':
				return 0;
		}
	}
	return 0;
}
#endif

