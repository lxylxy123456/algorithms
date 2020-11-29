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
		'std::istream', 'std::ostream', 'std::cout', 'std::cin',
		'std::boolalpha', 'std::endl', 'std::flush',
	],
	'string': [
		'std::string',
	],
	'stdexcept': [
		'std::invalid_argument',
	],
	'iterator': [
		'std::istream_iterator', 'std::ostream_iterator',
		'std::insert_iterator',
	],
	'deque': [
		'std::deque',
	],
	'cmath': [
		'abs', 'pow', 'log2',
	],
	'cassert': [
		'assert',
	],
	'sstream': [
		'std::istringstream', 'std::ostringstream',
	],
	'random': [
		'std::random_device', 'std::mt19937', 'std::uniform_int_distribution',
		'std::random_device::result_type',
	],
	'cstddef': [
		'size_t', 'std::size_t',
	],
	'iomanip': [
		'std::left', 'std::setw',
	],
	'numeric': [
		'std::accumulate',
	],
	'type_traits': [
		'std::is_same',
	],
	'map': [
		'std::pair', 'std::map', 'std::multimap',
	],
	'functional': [
		'std::hash',
	],
}

for i in ['list', 'set', 'unordered_set', 'unordered_map', 'deque', 'thread',
			'vector']:
	HEADER_TO_SYMBOL[i] = ['std::' + i]

SYMBOL_TO_HEADER = {}
for k, v in HEADER_TO_SYMBOL.items():
	for i in v:
		assert i not in SYMBOL_TO_HEADER
		SYMBOL_TO_HEADER[i] = k

def all_files():
	for path in ('include', 'src'):
		for name in sorted(os.listdir(path)):
			yield os.path.join(path, name)

def parse_file(pathname):
	content = open(pathname).read()
	lines = content.split('\n')
	state = 0
	splitted_lines = [[], [], []]
	for line in lines:
		if not line:
			pass
		elif line.startswith('#include'):
			assert state in (0, 1)
			state = 1
		else:
			if state == 1:
				state = 2
		splitted_lines[state].append(line)
	pre, include, post = splitted_lines
	assert '\n'.join(pre + include + post) == content
	include_set = set(include).difference({''})
	return pre, include_set, post

if __name__ == '__main__':
	for pathname in all_files():
		parsed = parse_file(pathname)
		a = open(pathname).read()
		actual = set(re.findall('#include <(\w+)>', a))
		expected = set()
		all_symbols = re.findall('[a-zA-Z0-9_:]+', a)
		for k, v in SYMBOL_TO_HEADER.items():
			if k in all_symbols:
				expected.add(v)
		p = actual.difference(expected)
		n = expected.difference(actual).difference({'cstddef'})
		if p or n:
			print('in', pathname)
			for i in sorted(p):
				print('  -', '#include <%s>' % i)
			for i in sorted(n):
				print('  +', '#include <%s>' % i)
		for k in all_symbols:
			if 'std::' in k and k not in SYMBOL_TO_HEADER:
				print('  ?', k)

