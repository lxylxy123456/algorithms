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
#define MAIN_ModLinEquationSolver
#endif

#ifndef FUNC_ModLinEquationSolver
#define FUNC_ModLinEquationSolver

#include "utils.h"

#include "Euclid.cpp"

template <typename T>
void ModularLinearEquationSolver(T a, T b, T n, std::vector<T>& ans) {
	T x, y;
	T d = ExtendedEuclid(a, n, x, y);
	if (b % d == 0) {
		T x0 = x * (b / d) % n;
		ans.reserve(d);
		for (T i = 0; i < d; i++)
			ans.push_back(((x0 + i * (n / d)) % n + n) % n);
	}
}
#endif

#ifdef MAIN_ModLinEquationSolver
int main(int argc, char *argv[]) {
	const size_t nn = get_argv(argc, argv, 1, 4);
	using T = long long int;
    std::random_device rd;
    std::uniform_int_distribution<T> dis(0, 1 << nn);
	T a = get_argv(argc, argv, 2, dis(rd));
	T b = get_argv(argc, argv, 3, dis(rd));
	T n = get_argv(argc, argv, 4, dis(rd));
	std::vector<T> ans;
	ModularLinearEquationSolver(a, b, n, ans);
	std::cout << a << " * x === " << b << " (mod " << n << ")" << std::endl;
	if (ans.size()) {
		std::cout << "x = ";
		output_integers(ans);
	} else
		std::cout << "no solutions" << std::endl;
	return 0;
}
#endif

