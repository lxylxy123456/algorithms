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
#define MAIN_ProtovEB
#endif

#ifndef FUNC_ProtovEB
#define FUNC_ProtovEB

#include <exception>
#include "utils.h"

const size_t NIL = -1;

class ProtovEB {
	public:
		ProtovEB(size_t kk): k(kk), u(1 << (1 << k)), sqrt_bit(1 << (k - 1)),
							sqrtu(1 << sqrt_bit) {
			if (k) {
				summary = new ProtovEB(k - 1);
				cluster = new ProtovEB* [sqrtu];
				for (size_t i = 0; i < sqrtu; i++)
					cluster[i] = new ProtovEB(k - 1);
			} else {
				A(0) = 0;
				A(1) = 0;
			}
		}
		bool& A(size_t i) {
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
		size_t high(size_t x) { return x >> sqrt_bit; }
		size_t low(size_t x) { return x & (sqrtu - 1); }
		size_t index(size_t x, size_t y) { return x << sqrt_bit | y; }
		// algorithms
		bool ProtovEBMember(size_t x) {
			if (k)
				return cluster[high(x)]->ProtovEBMember(low(x));
			else
				return A(x);
		}
		size_t ProtovEBMinimum() {
			if (k) {
				size_t min_c = summary->ProtovEBMinimum();
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
		size_t ProtovEBMaximum() {
			if (k) {
				size_t min_c = summary->ProtovEBMaximum();
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
		size_t ProtovEBSuccessor(size_t x) {
			if (k) {
				size_t offset = cluster[high(x)]->ProtovEBSuccessor(low(x));
				if (offset != NIL)
					return index(high(x), offset);
				else {
					size_t succ_c = summary->ProtovEBSuccessor(high(x));
					if (succ_c == NIL)
						return NIL;
					else {
						size_t offset = cluster[succ_c]->ProtovEBMinimum();
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
		size_t ProtovEBPredecessor(size_t x) {
			if (k) {
				size_t offset = cluster[high(x)]->ProtovEBPredecessor(low(x));
				if (offset != NIL)
					return index(high(x), offset);
				else {
					size_t succ_c = summary->ProtovEBPredecessor(high(x));
					if (succ_c == NIL)
						return NIL;
					else {
						size_t offset = cluster[succ_c]->ProtovEBMaximum();
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
		void ProtovEBInsert(size_t x) {
			if (k) {
				cluster[high(x)]->ProtovEBInsert(low(x));
				summary->ProtovEBInsert(high(x));
			} else
				A(x) = true;
		}
		bool ProtovEBDelete(size_t x) {
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
				for (size_t i = 0; i < sqrtu; i++)
					delete cluster[i];
				delete [] cluster;
				delete summary;
			}
		}
		size_t k, u, sqrt_bit, sqrtu;
};
#endif

#ifdef MAIN_ProtovEB
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
	const size_t k = get_argv(argc, argv, 1, 4);
	if (k > 4)
		throw std::invalid_argument("k too large");
	ProtovEB Pv(k);
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
				print(Pv.ProtovEBMember(x));
				break;
			case '-':
				print(Pv.ProtovEBMinimum());
				break;
			case '+':
				print(Pv.ProtovEBMaximum());
				break;
			case 'p':
				std::cout << "x = ";
				std::cin >> x;
				print(Pv.ProtovEBPredecessor(x));
				break;
			case 's':
				std::cout << "x = ";
				std::cin >> x;
				print(Pv.ProtovEBSuccessor(x));
				break;
			case 'i':
				std::cout << "x = ";
				std::cin >> x;
				Pv.ProtovEBInsert(x);
				break;
			case 'd':
				std::cout << "x = ";
				std::cin >> x;
				Pv.ProtovEBDelete(x);
				break;
			case 'P':
				for (size_t i = 0; i < Pv.u; i++)
					if (Pv.ProtovEBMember(i))
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

