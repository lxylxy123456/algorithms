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
#define MAIN_TaskSchedule
#endif

#ifndef FUNC_TaskSchedule
#define FUNC_TaskSchedule

#include <algorithm>
#include "utils.h"

#include "Greedy.cpp"

template <typename T>
class Task {
	public:
		Task(size_t i, size_t ddl, T pun): id(i), d(ddl), w(pun) {}
		bool operator<(const Task<T> rhs) const {
			if (d != rhs.d)
				return d < rhs.d; 
			if (w != rhs.w)
				return w > rhs.w; 
			return id < rhs.id; 
		}
		bool operator==(const Task<T> rhs) const { return id == rhs.id; }
		friend std::ostream& operator<<(std::ostream& os, const Task<T> rhs) {
			return os << rhs.id << ',' << rhs.d << ',' << rhs.w; 
		}
		static T get_p(Task<T> x) { return x.w; }
		size_t id; 
		size_t d; 
		T w; 
}; 

template <typename T>
class TaskMatroid: public Matroid<Task<T>> {
	public:
		TaskMatroid(std::set<Task<T>> s): Matroid<Task<T>>(s) {}
		virtual bool I(const std::set<Task<T>>& A) const {
			size_t t = 0; 
			for (auto i = A.begin(); i != A.end(); i++)
				if (i->d <= t++)
					return false; 
			return true; 
		}
}; 

template <typename T>
void TaskSchedule(const TaskMatroid<T>& M, std::vector<Task<T>>& ans) {
	std::set<Task<T>> A; 
	Greedy(M, Task<T>::get_p, A); 
	for (auto i = A.begin(); i != A.end(); i++)
		ans.push_back(*i); 
	for (auto i = M.S.begin(); i != M.S.end(); i++)
		if (A.find(*i) == A.end())
			ans.push_back(*i); 
}
#endif

#ifdef MAIN_TaskSchedule
template <typename T>
T f(Task<T> x) { return x.p; }

int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 7); 
	// prepare data
	std::set<Task<size_t>> S; 
	std::vector<size_t> d, w; 
	random_integers<size_t>(d, 1, n, n); 
	random_integers<size_t>(w, 1, n, n); 
	for (size_t i = 0; i < n; i++)
		S.insert(Task<size_t>(i, d[i], w[i])); 
	TaskMatroid<size_t> M(S); 
	output_integers(M.S, "\t"); 
	// call function
	std::vector<Task<size_t>> ans; 
	TaskSchedule(M, ans); 
	output_integers(ans, "\t"); 
	return 0; 
}
#endif

