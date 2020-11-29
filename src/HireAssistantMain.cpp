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

#include "HireAssistant.hpp"

#include "utils.hpp"

using namespace algorithms;

int main(int argc, char *argv[]) {
	int n = get_argv(argc, argv, 1, 10);
	int ci = get_argv(argc, argv, 2, 1);
	int ch = get_argv(argc, argv, 3, 10);
	std::vector<int> abilities;
	Candidate<int>* dummy_candidate = new Candidate<int>(-1, ci, ch, true);
	std::vector<Candidate<int>*> candidates(1, dummy_candidate);
	random_integers(abilities, 0, n - 1, n);
	candidates.reserve(n);
	for (auto i = abilities.begin(); i != abilities.end(); i++)
		candidates.push_back(new Candidate<int>(*i, ci, ch, false));
	output_integers(abilities);
	std::cout << HireAssistant(candidates) << std::endl;
	return 0;
}
