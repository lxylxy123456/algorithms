#  
#  algorithm - some algorithms in "Introduction to Algorithms", third edition
#  Copyright (C) 2018  lxylxy123456
#  
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Affero General Public License as
#  published by the Free Software Foundation, either version 3 of the
#  License, or (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Affero General Public License for more details.
#  
#  You should have received a copy of the GNU Affero General Public License
#  along with this program.  If not, see <https:#www.gnu.org/licenses/>.
#  

import os, re

for i in os.listdir() :
	if not i.endswith('.cpp') :
		continue
	a = open(i).read()
	try :
		for j in re.findall('#include <(\w+)>', a) :
			if j == 'cassert' :
				assert 'assert(' in a
			elif j == 'algorithm' :
				assert 'std::max_element' in a or 'std::min_element' in a
			elif j == 'cmath' :
				assert 'pow' in a
			elif j == 'iomanip' :
				assert 'std::left' in a
			elif j == 'exception' :
				assert 'std::invalid_argument' in a
			elif j == 'map' :
				assert 'std::map' in a or 'std::pair' in a
			elif j in ['list', 'set', 'unordered_set', 'unordered_map', 
						'deque', 'thread'] :
				assert 'std::' + j in a
			else :
				assert(False)
	except AssertionError :
		print('in:', i)
		print('include:', j)

