//
//  algorithm - some algorithms in "Introduction to Algorithms", third edition
//  Copyright (C) 2020  lxylxy123456
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

#include <cassert>
#include <iostream>
#include <vector>

#include "utils.hpp"

using namespace algorithms;

int test(int n, int ci, int ch) {
	std::vector<int> abilities;
	Candidate<int>* dummy_candidate = new Candidate<int>(-1, ci, ch, true);
	std::vector<Candidate<int>*> candidates(1, dummy_candidate);
	random_integers(abilities, 0, n - 1, n);
	candidates.reserve(n);
	for (auto i = abilities.begin(); i != abilities.end(); i++)
		candidates.push_back(new Candidate<int>(*i, ci, ch, false));
	output_integers(abilities);
	int ans = HireAssistant(candidates);
	std::cout << ans << std::endl;
	if (n > 0 && (ci > 0 || ch > 0))
		assert(ans > 0);
	else
		assert(ans == 0);
	for (std::vector<Candidate<int>*>::iterator i = candidates.begin();
		i < candidates.end(); i++)
		delete *i;
	return 0;
}

int main(int argc, char *argv[]) {
	for (int n = 0; n < 100; n = (n + 1) * 2)
		for (int ci = 0; ci < 10; ci += 5)
			for (int ch = 0; ch < 30; ch += 13)
				test(n, ci, ch);
	return 0;
}
