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

#ifndef ALGORITHMS_PROTOVEB
#define ALGORITHMS_PROTOVEB

#include <stdexcept>

using std::size_t;

namespace algorithms {

const std::size_t NIL = -1;

class ProtovEB {
	public:
		ProtovEB(std::size_t kk): k(kk), u(1 << (1 << k)), sqrt_bit(1 << (k - 1)),
							sqrtu(1 << sqrt_bit) {
			if (k) {
				summary = new ProtovEB(k - 1);
				cluster = new ProtovEB* [sqrtu];
				for (std::size_t i = 0; i < sqrtu; i++)
					cluster[i] = new ProtovEB(k - 1);
			} else {
				A(0) = 0;
				A(1) = 0;
			}
		}
		bool& A(std::size_t i) {
			switch (i) {
				case 0:
					return reinterpret_cast<bool*>(&summary)[0];
				case 1:
					return reinterpret_cast<bool*>(&cluster)[0];
				default:
					throw std::invalid_argument("array out of range");
			}
		}
		// indexing
		std::size_t high(size_t x) { return x >> sqrt_bit; }
		std::size_t low(size_t x) { return x & (sqrtu - 1); }
		std::size_t index(size_t x, size_t y) { return x << sqrt_bit | y; }
		// algorithms
		bool ProtovEBMember(std::size_t x) {
			if (k)
				return cluster[high(x)]->ProtovEBMember(low(x));
			else
				return A(x);
		}
		std::size_t ProtovEBMinimum() {
			if (k) {
				std::size_t min_c = summary->ProtovEBMinimum();
				if (min_c == NIL)
					return NIL;
				else
					return index(min_c, cluster[min_c]->ProtovEBMinimum());
			} else {
				if (A(0))
					return 0;
				else if (A(1))
					return 1;
				else
					return NIL;
			}
		}
		std::size_t ProtovEBMaximum() {
			if (k) {
				std::size_t min_c = summary->ProtovEBMaximum();
				if (min_c == NIL)
					return NIL;
				else
					return index(min_c, cluster[min_c]->ProtovEBMaximum());
			} else {
				if (A(1))
					return 1;
				else if (A(0))
					return 0;
				else
					return NIL;
			}
		}
		std::size_t ProtovEBSuccessor(size_t x) {
			if (k) {
				std::size_t offset = cluster[high(x)]->ProtovEBSuccessor(low(x));
				if (offset != NIL)
					return index(high(x), offset);
				else {
					std::size_t succ_c = summary->ProtovEBSuccessor(high(x));
					if (succ_c == NIL)
						return NIL;
					else {
						std::size_t offset = cluster[succ_c]->ProtovEBMinimum();
						return index(succ_c, offset);
					}
				}
			} else {
				if (x == 0 && A(1))
					return 1;
				else
					return NIL;
			}
		}
		std::size_t ProtovEBPredecessor(size_t x) {
			if (k) {
				std::size_t offset = cluster[high(x)]->ProtovEBPredecessor(low(x));
				if (offset != NIL)
					return index(high(x), offset);
				else {
					std::size_t succ_c = summary->ProtovEBPredecessor(high(x));
					if (succ_c == NIL)
						return NIL;
					else {
						std::size_t offset = cluster[succ_c]->ProtovEBMaximum();
						return index(succ_c, offset);
					}
				}
			} else {
				if (x == 1 && A(0))
					return 0;
				else
					return NIL;
			}
		}
		void ProtovEBInsert(std::size_t x) {
			if (k) {
				cluster[high(x)]->ProtovEBInsert(low(x));
				summary->ProtovEBInsert(high(x));
			} else
				A(x) = true;
		}
		bool ProtovEBDelete(std::size_t x) {
			if (k) {
				if (!cluster[high(x)]->ProtovEBDelete(low(x)))
					if (!summary->ProtovEBDelete(high(x))) {
						return summary->ProtovEBMinimum() != NIL;
					}
				return true;
			} else {
				A(x) = false;
				return A(0) || A(1);
			}
		}
		// members
		ProtovEB* summary; 		// A[0] when u == 2
		ProtovEB** cluster; 	// A[1] when u == 2
		~ProtovEB() {
			if (k) {
				for (std::size_t i = 0; i < sqrtu; i++)
					delete cluster[i];
				delete [] cluster;
				delete summary;
			}
		}
		std::size_t k, u, sqrt_bit, sqrtu;
};

}

#endif
