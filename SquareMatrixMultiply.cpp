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
#define MAIN_SquareMatrixMultiply
#endif

#ifndef FUNC_SquareMatrixMultiply
#define FUNC_SquareMatrixMultiply

#include <cassert>
#include "utils.h"
template <typename T>
class MatrixRow: public std::vector<T> {
	public:
	MatrixRow(): std::vector<T>(std::vector<T>()) {}
	MatrixRow(const std::vector<T>& d): std::vector<T>(d) {}
	MatrixRow(typename std::vector<T>::iterator s, 
				typename std::vector<T>::iterator e): std::vector<T>(s, e) {}
	MatrixRow(size_t c, T T0): std::vector<T>(std::vector<T>(c, T0)) {}
	MatrixRow<T> operator+(const MatrixRow<T> rhs) {
		assert(this->size() == rhs.size()); 
		MatrixRow<T> ans(this->size()); 
		for (size_t i = 0; i < this->size(); i++)
			ans[i] = (*this)[i] + rhs[i]; 
		return ans; 
	}
	friend std::ostream& operator<<(std::ostream& os, const MatrixRow& rhs) {
		for (size_t i = 0; i < rhs.size(); i++)
			os << rhs[i] << ' '; 
		return os; 
	}
	MatrixRow<T> concat_h(MatrixRow<T> rhs) {
		MatrixRow<T> ans(*this); 
		ans.insert(ans.end(), rhs.begin(), rhs.end()); 
		return ans; 
	}
}; 

// 某些被删除的迭代器代码: 见 git doc commit 63373f4c
template <typename T>
class Matrix {
	public:
	Matrix(size_t r, size_t c, std::vector<T> d): rows(r), cols(c) {
		data.reserve(r); 
		typename std::vector<T>::iterator begin = d.begin(), end = begin; 
		for (size_t i = 0; i < r; i++) {
			end = begin + c; 
			data.push_back(MatrixRow<T>(begin, end)); 
			begin += c; 
		}
	}
	Matrix(size_t r, size_t c, T T0): rows(r), cols(c) {
		data.reserve(r); 
		for (size_t i = 0; i < r; i++)
			data.push_back(MatrixRow<T>(c, T0)); 
	}
	Matrix(size_t r, size_t c): rows(r), cols(c) {
		data.reserve(r); 
	}
	friend std::ostream& operator<<(std::ostream& os, const Matrix& rhs) {
		for (size_t i = 0; i < rhs.rows; i++)
			os << rhs.data[i] << std::endl; 
		return os; 
	}
	std::ostream& octave(std::ostream& os) {
		os << '['; 
		for (size_t i = 0; i < rows; i++) {
			os << data[i]; 
			if (i != rows - 1)
				os << ';'; 
		}
		return os << ']' << std::endl; 
	}
	MatrixRow<T>& operator[](size_t index) { return data[index]; }
	bool operator==(const Matrix<T>& rhs) const {
		return data == rhs.data; 
	}
	Matrix<T> operator+(Matrix<T>& rhs) {
		Matrix<T> ans(rows, cols); 
		assert(rows == rhs.rows && cols == rhs.cols); 
		for (size_t i = 0; i < rows; i++) {
			MatrixRow<T> tmp; 
			tmp.reserve(ans.cols); 
			for (size_t j = 0; j < cols; j++)
				tmp.push_back((*this)[i][j] + rhs[i][j]); 
			ans.data.push_back(tmp); 
		}
		return ans; 
	}
	Matrix<T> operator-(Matrix<T>& rhs) {
		Matrix<T> ans(rows, cols); 
		assert(rows == rhs.rows && cols == rhs.cols); 
		for (size_t i = 0; i < rows; i++) {
			MatrixRow<T> tmp; 
			tmp.reserve(ans.cols); 
			for (size_t j = 0; j < cols; j++)
				tmp.push_back((*this)[i][j] - rhs[i][j]); 
			ans.data.push_back(tmp); 
		}
		return ans; 
	}
	Matrix<T> concat_h(Matrix<T> rhs) {
		assert(rows == rhs.rows); 
		Matrix<T> ans(rows, cols + rhs.cols); 
		for (size_t i = 0; i < rows; i++)
			ans.data.push_back(data[i].concat_h(rhs[i])); 
		return ans; 
	}
	Matrix<T> concat_v(Matrix<T> rhs) {
		assert(cols == rhs.cols); 
		Matrix<T> ans(*this); 
		ans.data.insert(ans.data.end(), rhs.data.begin(), rhs.data.end()); 
		ans.rows += rhs.rows; 
		return ans; 
	}
	void add_row(T T0) {
		rows += 1; 
		data.push_back(MatrixRow<T>(cols, T0)); 
	}
	void add_col(T T0) {
		cols += 1; 
		for (size_t i = 0; i < rows; i++)
			data[i].push_back(T0); 
	}
	// members
	size_t rows, cols; 
	std::vector<MatrixRow<T>> data; 
}; 

template <typename T>
class SubMatrix {
	public:
	SubMatrix(Matrix<T>& dd): data(dd), left(0), right(dd.cols), up(0), 
		down(dd.rows) {}
	SubMatrix(Matrix<T>& dd, size_t l, size_t r, size_t u, size_t d): 
		data(dd), left(l), right(r), up(u), down(d) {}
	SubMatrix(SubMatrix<T> dd, size_t l, size_t r, size_t u, size_t d): 
		data(dd.data), left(dd.left + l), right(dd.left + r), up(dd.up + u), 
		down(dd.up + d) {}
	T& get_elem(size_t i1, size_t i2) const {
		assert(i1 >= 0 && i1 < down - up); 
		assert(i2 >= 0 && i2 < right - left); 
		return data[up + i1][left + i2]; 
	}
	Matrix<T> operator+(SubMatrix<T> rhs) {
		Matrix<T> ans(rows(), cols()); 
		assert(ans.rows == rhs.rows() && ans.cols == rhs.cols()); 
		for (size_t i = 0; i < ans.rows; i++) {
			MatrixRow<T> tmp; 
			tmp.reserve(ans.cols); 
			for (size_t j = 0; j < ans.cols; j++)
				tmp.push_back(get_elem(i, j) + rhs.get_elem(i, j)); 
			ans.data.push_back(tmp); 
		}
		return ans; 
	}
	Matrix<T> operator-(SubMatrix<T> rhs) {
		Matrix<T> ans(rows(), cols()); 
		assert(ans.rows == rhs.rows() && ans.cols == rhs.cols()); 
		for (size_t i = 0; i < ans.rows; i++) {
			MatrixRow<T> tmp; 
			tmp.reserve(ans.cols); 
			for (size_t j = 0; j < ans.cols; j++)
				tmp.push_back(get_elem(i, j) - rhs.get_elem(i, j)); 
			ans.data.push_back(tmp); 
		}
		return ans; 
	}
	size_t rows(void) const { return down - up; }
	size_t cols(void) const { return right - left; }
	// members
	Matrix<T>& data; 
	size_t left, right, up, down; 
}; 

template <typename T>
Matrix<T> SquareMatrixMultiply(Matrix<T>&A, Matrix<T>&B, T T0){
	Matrix<T> C(A.rows, B.cols, T0); 
	for (size_t i = 0; i < C.rows; i++) {
		for(size_t j = 0; j < C.cols; j++) {
			T& loc = C.data[i][j]; 
			for(size_t k = 0; k < A.cols; k++) {
				loc += A[i][k] * B[k][j]; 
			}
		}
	}
	return C; 
}

template <typename T>
void SquareMatrixMultiplyRecursive(SubMatrix<T>& A, SubMatrix<T>& B, 
									SubMatrix<T>& C) {
	size_t a_row = A.rows(), a_col = A.cols(); 
	size_t b_row = B.rows(), b_col = B.cols(); 
	size_t c_row = C.rows(), c_col = C.cols(); 
	assert(a_row == c_row && b_col == c_col && a_col == b_row); 
	switch(a_row * a_col * b_col) {
		case 1: 
			C.get_elem(0, 0) += A.get_elem(0, 0) * B.get_elem(0, 0); 
		case 0:
			return; 
		default: 
			size_t a_mid = c_row / 2; 	// Rows of A & C
			size_t b_mid = c_col / 2; 	// Cols of B & C
			size_t c_mid = a_col / 2; 	// Cols of A & Rows of B
			SubMatrix<T> A11(A,     0, c_mid,     0, a_mid); 
			SubMatrix<T> A12(A, c_mid, a_col,     0, a_mid); 
			SubMatrix<T> A21(A,     0, c_mid, a_mid, a_row); 
			SubMatrix<T> A22(A, c_mid, a_col, a_mid, a_row); 
			SubMatrix<T> B11(B,     0, b_mid,     0, c_mid); 
			SubMatrix<T> B12(B, b_mid, b_col,     0, c_mid); 
			SubMatrix<T> B21(B,     0, b_mid, c_mid, b_row); 
			SubMatrix<T> B22(B, b_mid, b_col, c_mid, b_row); 
			SubMatrix<T> C11(C,     0, b_mid,     0, a_mid); 
			SubMatrix<T> C12(C, b_mid, b_col,     0, a_mid); 
			SubMatrix<T> C21(C,     0, b_mid, a_mid, c_row); 
			SubMatrix<T> C22(C, b_mid, c_col, a_mid, c_row); 
			SquareMatrixMultiplyRecursive(A11, B11, C11); 
			SquareMatrixMultiplyRecursive(A12, B21, C11); 
			SquareMatrixMultiplyRecursive(A11, B12, C12); 
			SquareMatrixMultiplyRecursive(A12, B22, C12); 
			SquareMatrixMultiplyRecursive(A21, B11, C21); 
			SquareMatrixMultiplyRecursive(A22, B21, C21); 
			SquareMatrixMultiplyRecursive(A21, B12, C22); 
			SquareMatrixMultiplyRecursive(A22, B22, C22); 
	}
}

template <typename T>
Matrix<T> SquareMatrixMultiplyRecursive(Matrix<T>& A, Matrix<T>& B, T T0) {
	Matrix<T> C(A.rows, B.cols, T0); 
	SubMatrix<T> A_sub(A), B_sub(B), C_sub(C); 
	SquareMatrixMultiplyRecursive(A_sub, B_sub, C_sub); 
	return C; 
}

template <typename T, T T0>
Matrix<T> SquareMatrixMultiplyStrassen(SubMatrix<T> A, SubMatrix<T> B) {
	size_t a_row = A.rows(), a_col = A.cols(); 
	size_t b_row = B.rows(), b_col = B.cols(); 
	assert(a_col == b_row); 
	switch(a_row * a_col * b_col) {
		case 1: 
			return Matrix<T>(1, 1, A.get_elem(0, 0) * B.get_elem(0, 0)); 
		case 0:
			return Matrix<T>(0, 0); 
		default: 
			size_t a_mid = a_row / 2; 	// Rows of A & C
			size_t b_mid = b_col / 2; 	// Cols of B & C
			size_t c_mid = a_col / 2; 	// Cols of A & Rows of B
			size_t a_end = a_mid * 2; 
			size_t b_end = b_mid * 2; 
			size_t c_end = c_mid * 2; 
			SubMatrix<T> A11(A,     0, c_mid,     0, a_mid); 
			SubMatrix<T> A12(A, c_mid, c_end,     0, a_mid); 
			SubMatrix<T> A21(A,     0, c_mid, a_mid, a_end); 
			SubMatrix<T> A22(A, c_mid, c_end, a_mid, a_end); 
			SubMatrix<T> B11(B,     0, b_mid,     0, c_mid); 
			SubMatrix<T> B12(B, b_mid, b_end,     0, c_mid); 
			SubMatrix<T> B21(B,     0, b_mid, c_mid, c_end); 
			SubMatrix<T> B22(B, b_mid, b_end, c_mid, c_end); 
			Matrix<T> S1 = B12 - B22, S2  = A11 + A12, S3 = A21 + A22, 
				S4 = B21 - B11, S5 = A11 + A22, S6 = B11 + B22, S7 = A12 - A22, 
				S8 = B21 + B22, S9 = A11 - A21, S10 = B11 + B12; 
			Matrix<T> P1 = SquareMatrixMultiplyStrassen<T, T0>(A11, S1 ); 
			Matrix<T> P2 = SquareMatrixMultiplyStrassen<T, T0>(S2 , B22); 
			Matrix<T> P3 = SquareMatrixMultiplyStrassen<T, T0>(S3 , B11); 
			Matrix<T> P4 = SquareMatrixMultiplyStrassen<T, T0>(A22, S4 ); 
			Matrix<T> P5 = SquareMatrixMultiplyStrassen<T, T0>(S5 , S6 ); 
			Matrix<T> P6 = SquareMatrixMultiplyStrassen<T, T0>(S7 , S8 ); 
			Matrix<T> P7 = SquareMatrixMultiplyStrassen<T, T0>(S9 , S10); 
			Matrix<T> C11 = P5 + P4 - P2 + P6; 
			Matrix<T> C12 = P1 + P2; 
			Matrix<T> C21 = P3 + P4; 
			Matrix<T> C22 = P5 + P1 - P3 - P7; 
			Matrix<T> C = (C11.concat_h(C12)).concat_v(C21.concat_h(C22)); 
			if (a_end != a_row) {
				assert(a_end == a_row - 1); 
				C.add_row(T0); 
				for (size_t i = 0; i < b_end; i++)
					for (size_t j = 0; j < c_end; j++)
						C[a_end][i] += A.get_elem(a_end, j) * B.get_elem(j, i); 
				a_end += 1; 
			}
			if (b_end != b_col) {
				assert(b_end == b_col - 1); 
				C.add_col(T0); 
				for (size_t i = 0; i < a_end; i++)
					for (size_t j = 0; j < c_end; j++)
						C[i][b_end] += A.get_elem(i, j) * B.get_elem(j, b_end); 
				b_end += 1; 
			}
			if (c_end != a_col) {
				assert(c_end == a_col - 1); 
				for (size_t i = 0; i < a_end; i++)
					for (size_t j = 0; j < b_end; j++)
						C[i][j] += A.get_elem(i, c_end) * B.get_elem(c_end, j); 
			}
			return C; 
	}
}

template <typename T, T T0>
Matrix<T> SquareMatrixMultiplyStrassen(SubMatrix<T> A, Matrix<T>& B) {
	return SquareMatrixMultiplyStrassen<T, T0>(A, SubMatrix<T>(B)); 
}

template <typename T, T T0>
Matrix<T> SquareMatrixMultiplyStrassen(Matrix<T>& A, SubMatrix<T> B) {
	return SquareMatrixMultiplyStrassen<T, T0>(SubMatrix<T>(A), B); 
}

template <typename T, T T0>
Matrix<T> SquareMatrixMultiplyStrassen(Matrix<T>& A, Matrix<T>& B) {
	return SquareMatrixMultiplyStrassen<T, T0>(SubMatrix<T>(A), 
												SubMatrix<T>(B)); 
}
#endif

#ifdef MAIN_SquareMatrixMultiply
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 16); 
	const size_t compute = get_argv(argc, argv, 2, 7); 
	std::vector<int> buf_a, buf_b; 
	random_integers(buf_a, 0, n, n * n); 
	random_integers(buf_b, 0, n, n * n); 
	Matrix<int> A(n, n, buf_a); 
	Matrix<int> B(n, n, buf_b); 
	std::cout << A << std::endl; 
	std::cout << B << std::endl; 
	Matrix<int> ans1(A); 
	if (compute >> 0 & 1) {
		std::cout << "SquareMatrixMultiply" << std::endl; 
		ans1 = SquareMatrixMultiply(A, B, 0); 
		std::cout << ans1 << std::endl; 
	}
	if (compute >> 1 & 1) {
		std::cout << "SquareMatrixMultiplyRecursive" << std::endl; 
		Matrix<int> ans2 = SquareMatrixMultiplyRecursive(A, B, 0); 
		std::cout << ans2 << std::endl; 
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (ans1 == ans2) << std::endl; 
	}
	if (compute >> 2 & 1) {
		std::cout << "SquareMatrixMultiplyStrassen" << std::endl; 
		Matrix<int> ans3 = SquareMatrixMultiplyStrassen<int, 0>(A, B); 
		std::cout << ans3 << std::endl; 
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (ans1 == ans3) << std::endl; 
	}
	return 0; 
}
#endif

