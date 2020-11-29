#
#  algorithm - some algorithms in "Introduction to Algorithms", third edition
#  Copyright (C) 2020  lxylxy123456
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
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

import os, re

HEADER_TO_SYMBOL = {
	'algorithm': [
		'std::max', 'std::min', 'std::max_element', 'std::min_element',
		'std::find', 'std::find_if', 'std::find_if_not', 'std::copy',
		'std::sort', 'std::swap',
	],
	'iostream': [
		'std::ostream', 'std::cout', 'std::cin', 'std::boolalpha',
	],
	'string': [
		'std::string',
	],
	'stdexcept': [
		'std::invalid_argument',
	],
	'iterator': [
		'std::istream_iterator', 'std::ostream_iterator',
	],
	'deque': [
		'std::deque',
	],
	'cmath': [
		'abs(', 'pow(', 'log2(',
	],
	'cassert': [
		'assert(',
	],
	'sstream': [
		'std::istringstream', 'std::ostringstream',
	],
	'random': [
		'std::random_device', 'std::mt19937', 'std::uniform_int_distribution',
	],
	'cstddef': [
		'size_t'
	],
	'iomanip': [
		'std::left', 'std::setw',
	],
}

for i in ['map', 'list', 'set', 'unordered_set', 'unordered_map', 'deque',
			'thread', 'vector']:
	HEADER_TO_SYMBOL[i] = ['std::' + i]

HEADER_TO_SYMBOL['map'].append('std::pair')

for f in ('include', 'src'):
	for i in os.listdir(f) :
		a = open(os.path.join(f, i)).read()
		try :
			for j in re.findall('#include <(\w+)>', a) :
				flag = False
				for k in HEADER_TO_SYMBOL[j]:
					if k in a:
						flag = True
				assert flag
		except AssertionError :
			print('in:', os.path.join(f, i))
			print('include:', j)

