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
#define MAIN_Minimum
#endif

#ifndef FUNC_Minimum
#define FUNC_Minimum

#include "utils.h"

class Value {
	public:
		Value(void) {}
		Value(int v): val(v) {}
		friend std::ostream& operator<<(std::ostream& os, const Value& rhs) {
			return os << rhs.val;
		}
		bool operator==(const Value& rhs) const {
			return val == rhs.val;
		}
		bool operator>(const Value& rhs) const {
			cmp_num++;
			return val > rhs.val;
		}
		bool operator<(const Value& rhs) const {
			cmp_num++;
			return val < rhs.val;
		}
		static int get_cmp_num(void) {
			int ans = cmp_num;
			cmp_num = 0;
			return ans;
		}
	private:
		int val;
		static int cmp_num;
};

int Value::cmp_num = 0;

template <typename T>
T Minimum(std::vector<T>& A) {
	typename std::vector<T>::iterator i = A.begin();
	T min = *i;
	for (i++; i != A.end(); i++)
		if (min > *i)
			min = *i;
	return min;
}

template <typename T>
T Maximum(std::vector<T>& A) {
	typename std::vector<T>::iterator i = A.begin();
	T max = *i;
	for (i++; i != A.end(); i++)
		if (max < *i)
			max = *i;
	return max;
}

template <typename T>
void MinMax(std::vector<T>& A, T& min, T& max) {
	typename std::vector<T>::iterator i = A.begin(), j;
	if (A.size() % 2) {
		min = max = *(i++);
	} else {
		j = i + 1;
		if (*i < *j) {
			min = *i;
			max = *j;
		} else {
			min = *j;
			max = *i;
		}
		i = j + 1;
	}
	while (i != A.end()) {
		j = i + 1;
		if (*i < *j) {
			if (*i < min)
				min = *i;
			if (*j > max)
				max = *j;
		} else {
			if (*j < min)
				min = *j;
			if (*i > max)
				max = *i;
		}
		i = j + 1;
	}
}
#endif

#ifdef MAIN_Minimum
int main(int argc, char *argv[]) {
	std::vector<int> a;
	int n = get_argv(argc, argv, 1, 10);
	random_integers(a, 0, n - 1, n);
	output_integers(a);
	std::vector<Value> A;
	A.reserve(n);
	for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++)
		A.push_back(*i);
	Value min1, max1, min2, max2;
	min1 = Minimum(A);
	std::cout << Value::get_cmp_num() << std::endl;
	max1 = Maximum(A);
	std::cout << Value::get_cmp_num() << std::endl;
	MinMax(A, min2, max2);
	std::cout << Value::get_cmp_num() << std::endl;
	std::cout << min1 << '\t' << max1 << std::endl;
	std::cout << min2 << '\t' << max2 << std::endl;
	std::cout << std::boolalpha << (min1 == min2 && max1 == max2) << std::endl;
	return 0;
}
#endif

