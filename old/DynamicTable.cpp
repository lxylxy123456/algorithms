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
#define MAIN_DynamicTable
#endif

#ifndef FUNC_DynamicTable
#define FUNC_DynamicTable

#include "utils.h"

template <typename T>
class DynamicTable {
	public:
		DynamicTable(): size(0), num(0), table(new std::vector<T>(0)) {}
		void TableInsert(T x) {
			if (!size) {
				delete table;
				table = new std::vector<T>(1);
				size++;
			}
			if (num == size) {
				size *= 2;
				std::vector<T>* nt = new std::vector<T>(size);
				std::copy(table->begin(), table->end(), nt->begin());
				delete table;
				table = nt;
			}
			(*table)[num++] = x;
		}
		T TableDelete() {
			T ans = (*table)[--num];
			if (!num) {
				delete table;
				table = new std::vector<T>(0);
				size = 0;
			}
			if (num * 4 < size) {
				size /= 2;
				std::vector<T>* nt = new std::vector<T>(size);
				std::copy(table->begin(), table->begin() + num, nt->begin());
				delete table;
				table = nt;
			}
			return ans;
		}
		size_t size, num;
		std::vector<T>* table;
};
#endif

#ifdef MAIN_DynamicTable
int main(int argc, char *argv[]) {
	DynamicTable<int> DT;
	std::cout << "i / I: insert" << std::endl;
	std::cout << "q / Q: quit" << std::endl;
	while (true) {
		char c; int x;
		std::cout << "num = " << DT.num << ", size = " << DT.size << std::endl;
		std::cout << ">> ";
		if (!(std::cin >> c)) {
			std::cout << std::endl;
			break;
		}
		switch (c) {
			case 'i':
			case 'I':
				std::cout << "x = ";
				std::cin >> x;
				DT.TableInsert(x);
				break;
			case 'd':
			case 'D':
				std::cout << DT.TableDelete() << std::endl;
				break;
			case 'q':
			case 'Q':
				return 0;
		}
	}
	return 0;
}
#endif

