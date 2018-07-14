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
#define MAIN_LCSLength
#endif

#ifndef FUNC_LCSLength
#define FUNC_LCSLength

#define VECT_SIZT std::vector<size_t>

#include "utils.h"

template <typename T>
std::vector<VECT_SIZT> LCSLength(std::vector<T> X, std::vector<T> Y) {
	size_t m = X.size(), n = Y.size(); 
	std::vector<VECT_SIZT> c(m + 1, VECT_SIZT(n + 1, 0)); 
	for (size_t i = 1; i <= m; i++)
		for (size_t j = 1; j <= n; j++) {
			if (X[i - 1] == Y[j - 1])
				c[i][j] = c[i-1][j-1] + 1; 
			else
				c[i][j] = std::max(c[i-1][j], c[i][j-1]); 
		}
	return c; 
}

template <typename T>
void PrintLCS(std::vector<VECT_SIZT>& c, std::vector<T> X, size_t i, size_t j) {
	if (!i || !j)
		return; 
	if (c[i][j] == c[i-1][j-1] + 1) {
		PrintLCS(c, X, i - 1, j - 1); 
		std::cout << X[i - 1]; 
	} else if (c[i][j] == c[i-1][j])
		PrintLCS(c, X, i - 1, j); 
	else
		PrintLCS(c, X, i, j - 1); 
}
#endif

#ifdef MAIN_LCSLength
int main(int argc, char *argv[]) {
	const size_t x = get_argv(argc, argv, 1, 8); 
	const size_t y = get_argv(argc, argv, 2, 9); 
	const size_t n = get_argv(argc, argv, 3, 25); 
	std::vector<char> X, Y; 
	random_integers<char>(X, 'a', 'a' + n, x); 
	random_integers<char>(Y, 'a', 'a' + n, y); 
	output_integers(X, ""); 
	output_integers(Y, ""); 
	std::vector<VECT_SIZT> c = LCSLength(X, Y); 
	PrintLCS(c, X, x, y); 
	std::cout << std::endl; 
	return 0; 
}
#endif

