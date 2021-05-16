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

#ifndef ALGORITHMS_VEB
#define ALGORITHMS_VEB

#include <algorithm>

#include "ProtovEB.hpp"

using std::size_t;

namespace algorithms {

class vEB {
	public:
		vEB(std::size_t kk): k(kk), u(1 << k), min(NIL), max(NIL),
						lsqrt_bit(k / 2), lsqrtu(1 << lsqrt_bit),
						usqrt_bit((k - 1) / 2 + 1), usqrtu(1 << usqrt_bit) {
			if (k > 1) {
				summary = new vEB(usqrt_bit);
				cluster = new vEB* [usqrtu];
				for (std::size_t i = 0; i < usqrtu; i++)
					cluster[i] = new vEB(lsqrt_bit);
			}
		}
		// indexing
		std::size_t high(std::size_t x) { return x >> lsqrt_bit; }
		std::size_t low(std::size_t x) { return x & (lsqrtu - 1); }
		std::size_t index(std::size_t x, std::size_t y) { return x << lsqrt_bit | y; }
		// algorithms
		std::size_t vEBTreeMinimum() {
			return min;
		}
		std::size_t vEBTreeMaximum() {
			return max;
		}
		bool vEBTreeMember(std::size_t x) {
			if (x == min || x == max)
				return true;
			else if (k == 1)
				return false;
			else
				return cluster[high(x)]->vEBTreeMember(low(x));
		}
		std::size_t vEBTreeSuccessor(std::size_t x) {
			if (k == 1) {
				if (x == 0 && max == 1)
					return 1;
				else
					return NIL;
			} else if (min != NIL && x < min)
				return min;
			else {
				std::size_t hx = high(x), lx = low(x);
				std::size_t max_low = cluster[hx]->vEBTreeMaximum();
				if (max_low != NIL && lx < max_low) {
					std::size_t offset = cluster[hx]->vEBTreeSuccessor(lx);
					return index(hx, offset);
				} else {
					std::size_t succ_c = summary->vEBTreeSuccessor(hx);
					if (succ_c == NIL)
						return NIL;
					else {
						std::size_t offset = cluster[succ_c]->vEBTreeMinimum();
						return index(succ_c, offset);
					}
				}
			}
		}
		std::size_t vEBTreePredecessor(std::size_t x) {
			if (k == 1) {
				if (x == 1 && min == 0)
					return 0;
				else
					return NIL;
			} else if (max != NIL && x > max)
				return max;
			else {
				std::size_t hx = high(x), lx = low(x);
				std::size_t min_low = cluster[hx]->vEBTreeMinimum();
				if (min_low != NIL && lx > min_low) {
					std::size_t offset = cluster[hx]->vEBTreePredecessor(lx);
					return index(hx, offset);
				} else {
					std::size_t pred_c = summary->vEBTreePredecessor(hx);
					if (pred_c == NIL) {
						if (min != NIL && x > min)
							return min;
						else
							return NIL;
					} else {
						std::size_t offset = cluster[pred_c]->vEBTreeMaximum();
						return index(pred_c, offset);
					}
				}
			}
		}
		void vEBEmptyTreeInsert(std::size_t x) {
			min = x;
			max = x;
		}
		void vEBTreeInsert(std::size_t x) {
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
		void vEBTreeDelete(std::size_t x) {
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
					std::size_t first_c = summary->vEBTreeMinimum();
					x = index(first_c, cluster[first_c]->vEBTreeMinimum());
					min = x;
				}
				cluster[high(x)]->vEBTreeDelete(low(x));
				if (cluster[high(x)]->vEBTreeMinimum() == NIL) {
					summary->vEBTreeDelete(high(x));
					if (x == max) {
						std::size_t summ_max = summary->vEBTreeMaximum();
						if (summ_max == NIL)
							max = min;
						else {
							std::size_t offset = cluster[summ_max]->vEBTreeMaximum();
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
				for (std::size_t i = 0; i < usqrtu; i++)
					delete cluster[i];
				delete [] cluster;
				delete summary;
			}
		}
		std::size_t k, u, min, max, lsqrt_bit, lsqrtu, usqrt_bit, usqrtu;
};

}

#endif
