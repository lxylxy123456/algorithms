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

#ifndef ALGORITHMS_PSQUAREMATRIXMULTIPLY
#define ALGORITHMS_PSQUAREMATRIXMULTIPLY

#include <thread>
#include "utils.h"

#include "MatVec.hpp"

namespace algorithms {


#define SM SubMatrix<T>

template <typename T>
Matrix<T> PSquareMatrixMultiply(Matrix<T>&A, Matrix<T>&B, T T0) {
	Matrix<T> C(A.rows, B.cols, T0);
	parallel_for<size_t>(0, C.rows, [&](size_t i){
		parallel_for<size_t>(0, C.cols, [&](size_t j){
			int& loc = C.data[i][j];
			for(size_t k = 0; k < A.cols; k++) {
				loc += A[i][k] * B[k][j];
			}
		});
	});
	return C;
}

template <typename T>
void PMatrixMultiplyRecursive(SM A, SM B, SM C, T T0) {
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
			Matrix<T> S(c_row, c_col, T0);
			size_t a_mid = c_row / 2; 	// Rows of A & C
			size_t b_mid = c_col / 2; 	// Cols of B & C
			size_t c_mid = a_col / 2; 	// Cols of A & Rows of B
			SM A11(A,     0, c_mid,     0, a_mid);
			SM A12(A, c_mid, a_col,     0, a_mid);
			SM A21(A,     0, c_mid, a_mid, a_row);
			SM A22(A, c_mid, a_col, a_mid, a_row);
			SM B11(B,     0, b_mid,     0, c_mid);
			SM B12(B, b_mid, b_col,     0, c_mid);
			SM B21(B,     0, b_mid, c_mid, b_row);
			SM B22(B, b_mid, b_col, c_mid, b_row);
			SM C11(C,     0, b_mid,     0, a_mid);
			SM C12(C, b_mid, b_col,     0, a_mid);
			SM C21(C,     0, b_mid, a_mid, c_row);
			SM C22(C, b_mid, c_col, a_mid, c_row);
			SM S11(S,     0, b_mid,     0, a_mid);
			SM S12(S, b_mid, b_col,     0, a_mid);
			SM S21(S,     0, b_mid, a_mid, c_row);
			SM S22(S, b_mid, c_col, a_mid, c_row);
			std::thread t1(PMatrixMultiplyRecursive<T>, A11, B11, C11, T0);
			std::thread t2(PMatrixMultiplyRecursive<T>, A12, B21, S11, T0);
			std::thread t3(PMatrixMultiplyRecursive<T>, A11, B12, C12, T0);
			std::thread t4(PMatrixMultiplyRecursive<T>, A12, B22, S12, T0);
			std::thread t5(PMatrixMultiplyRecursive<T>, A21, B11, C21, T0);
			std::thread t6(PMatrixMultiplyRecursive<T>, A22, B21, S21, T0);
			std::thread t7(PMatrixMultiplyRecursive<T>, A21, B12, C22, T0);
			PMatrixMultiplyRecursive(A22, B22, S22, T0);
			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
			t6.join();
			t7.join();
			parallel_for<size_t>(0, c_row, [&](size_t i){
				parallel_for<size_t>(0, c_col, [&](size_t j){
					C.get_elem(i, j) += S[i][j];
				});
			});
	}
}

template <typename T>
Matrix<T> PMatrixMultiplyRecursive(Matrix<T>& A, Matrix<T>& B, T T0) {
	Matrix<T> C(A.rows, B.cols, T0);
	SM A_sub(A), B_sub(B), C_sub(C);
	PMatrixMultiplyRecursive(A_sub, B_sub, C_sub, T0);
	return C;
}

template <typename T>
Matrix<T> PMatAdd(SM A, SM B) {
	size_t a_row = A.rows(), a_col = A.cols();
	size_t b_row = B.rows(), b_col = B.cols();
	assert(a_row == b_row && a_col == b_col);
	Matrix<T> C(a_row, a_col, 0);
	parallel_for<size_t>(0, a_row, [&](size_t i){
		parallel_for<size_t>(0, a_col, [&](size_t j){
			C[i][j] = A.get_elem(i, j) + B.get_elem(i, j);
		});
	});
	return C;
}

template <typename T>
Matrix<T> PMatAdd(Matrix<T> A, Matrix<T> B) {
	return PMatAdd(SM(A), SM(B));
}

template <typename T>
Matrix<T> PMatSub(SM A, SM B) {
	size_t a_row = A.rows(), a_col = A.cols();
	size_t b_row = B.rows(), b_col = B.cols();
	assert(a_row == b_row && a_col == b_col);
	Matrix<T> C(a_row, a_col, 0);
	parallel_for<size_t>(0, a_row, [&](size_t i){
		parallel_for<size_t>(0, a_col, [&](size_t j){
			C[i][j] = A.get_elem(i, j) - B.get_elem(i, j);
		});
	});
	return C;
}

template <typename T>
Matrix<T> PMatSub(Matrix<T> A, Matrix<T> B) {
	return PMatSub(SM(A), SM(B));
}

template <typename T, T T0>
void PMatrixMultiplyStrassen(SM A, SM B, SM CC) {
	size_t a_row = A.rows(), a_col = A.cols();
	size_t b_row = B.rows(), b_col = B.cols();
	assert(a_col == b_row);
	switch(a_row * a_col * b_col) {
		case 1:
			CC.data = Matrix<T>(1, 1, A.get_elem(0, 0) * B.get_elem(0, 0));
			break;
		case 0:
			CC.data = Matrix<T>(0, 0);
			break;
		default:
			size_t a_mid = a_row / 2; 	// Rows of A & C
			size_t b_mid = b_col / 2; 	// Cols of B & C
			size_t c_mid = a_col / 2; 	// Cols of A & Rows of B
			size_t a_end = a_mid * 2;
			size_t b_end = b_mid * 2;
			size_t c_end = c_mid * 2;
			SM A11(A,     0, c_mid,     0, a_mid);
			SM A12(A, c_mid, c_end,     0, a_mid);
			SM A21(A,     0, c_mid, a_mid, a_end);
			SM A22(A, c_mid, c_end, a_mid, a_end);
			SM B11(B,     0, b_mid,     0, c_mid);
			SM B12(B, b_mid, b_end,     0, c_mid);
			SM B21(B,     0, b_mid, c_mid, c_end);
			SM B22(B, b_mid, b_end, c_mid, c_end);
			Matrix<T> S1 = PMatSub(B12, B22);
			Matrix<T> S2 = PMatAdd(A11, A12);
			Matrix<T> S3 = PMatAdd(A21, A22);
			Matrix<T> S4 = PMatSub(B21, B11);
			Matrix<T> S5 = PMatAdd(A11, A22);
			Matrix<T> S6 = PMatAdd(B11, B22);
			Matrix<T> S7 = PMatSub(A12, A22);
			Matrix<T> S8 = PMatAdd(B21, B22);
			Matrix<T> S9 = PMatSub(A11, A21);
			Matrix<T> S10 = B11 + B12;
			Matrix<T> P1(0, 0), P2(P1), P3(P2), P4(P3), P5(P4), P6(P5), P7(P6);
			std::thread
				t1(PMatrixMultiplyStrassen<T, T0>, A11,    SM(S1), SM(P1)),
				t2(PMatrixMultiplyStrassen<T, T0>, SM(S2), B22,    SM(P2)),
				t3(PMatrixMultiplyStrassen<T, T0>, SM(S3), B11,    SM(P3)),
				t4(PMatrixMultiplyStrassen<T, T0>, A22,    SM(S4), SM(P4)),
				t5(PMatrixMultiplyStrassen<T, T0>, SM(S5), SM(S6), SM(P5)),
				t6(PMatrixMultiplyStrassen<T, T0>, SM(S7), SM(S8), SM(P6));
			PMatrixMultiplyStrassen<T, T0>(S9 , S10, P7);
			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
			t6.join();
			Matrix<T> C11 = PMatAdd(PMatSub(PMatAdd(P5, P4), P2), P6);
			Matrix<T> C12 = PMatAdd(P1, P2);
			Matrix<T> C21 = PMatAdd(P3, P4);
			Matrix<T> C22 = PMatSub(PMatSub(PMatAdd(P5, P1), P3), P7);
			Matrix<T>& C = CC.data;
			C = (C11.concat_h(C12)).concat_v(C21.concat_h(C22));
			if (a_end != a_row) {
				assert(a_end == a_row - 1);
				C.add_row(T0);
				parallel_for<size_t>(0, b_end, [&](size_t i){
					for (size_t j = 0; j < c_end; j++)
						C[a_end][i] += A.get_elem(a_end, j) * B.get_elem(j, i);
				});
				a_end += 1;
			}
			if (b_end != b_col) {
				assert(b_end == b_col - 1);
				C.add_col(T0);
				parallel_for<size_t>(0, a_end, [&](size_t i){
					for (size_t j = 0; j < c_end; j++)
						C[i][b_end] += A.get_elem(i, j) * B.get_elem(j, b_end);
				});
				b_end += 1;
			}
			if (c_end != a_col) {
				assert(c_end == a_col - 1);
				parallel_for<size_t>(0, a_end, [&](size_t i){
					for (size_t j = 0; j < b_end; j++)
						C[i][j] += A.get_elem(i, c_end) * B.get_elem(c_end, j);
				});
			}
	}
}

template <typename T, T T0>
Matrix<T> PMatrixMultiplyStrassen(Matrix<T>& A, Matrix<T>& B) {
	Matrix<T> C(A.rows, B.cols, T0);
	PMatrixMultiplyStrassen<T, T0>(SM(A), SM(B), SM(C));
	return C;
}

}

#endif
