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

import os, re, argparse

HEADER_TO_SYMBOL = {
	'algorithm': [
		'std::max', 'std::min', 'std::max_element', 'std::min_element',
		'std::find', 'std::find_if', 'std::find_if_not', 'std::copy',
		'std::sort', 'std::swap',
	],
	'iostream': [
		'std::istream', 'std::ostream', 'std::cout', 'std::cin', 'std::cerr',
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
		'abs', 'pow', 'log2', 'fabs',
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
			if not name.startswith('tmp'):
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
	if include:
		assert include[-1] == ''
		post.insert(0, include.pop(-1))
	assert '\n'.join(pre + include + post) == content
	return pre, include, post

def refresh_file(pathname, parsed):
	pre, include, post = parsed
	open(pathname, 'w').write('\n'.join(pre + include + post))

def reorder_includes(pathname, includes):
	if not includes:
		return []
	anss = []
	includes = set(includes)
	'' in includes and includes.remove('')
	if pathname.endswith('.cpp'):
		assert pathname.startswith('src/')
		name = pathname[4:-8]
		include_name = '#include "%s.hpp"' % name
		includes.remove(include_name)
		anss.append([include_name])
	i1 = []
	i2 = []
	for i in includes:
		if i.endswith('>'):
			i1.append(i)
		else:
			i2.append(i)
	i1 and anss.append(sorted(i1))
	i2 and anss.append(sorted(i2))
	ans = []
	for i in anss:
		for j in i:
			ans.append(j)
		ans.append('')
	assert ans.pop(-1) == ''
	return ans

def graphviz_escape(s):
	assert '\\\n\t' not in s
	return '"%s"' % s.replace('"', r'\"')

def draw_includes(pathnames):
	include_info = {}
	for pathname in pathnames:
		parsed = parse_file(pathname)
		includes = parsed[1]
		info = []
		for include in includes:
			if not include:
				continue
			header = re.fullmatch('\#include (.+)', include).groups()[0]
			info.append(header)
		name = '"%s"' % os.path.split(pathname)[1]
		include_info[name] = info
	print('digraph G {')
	for name, info in include_info.items():
		for rhs in info:
			if '.cpp' in name:
				continue
			if '<' in rhs:
				continue
			print('\t%s -> %s' % (graphviz_escape(name), graphviz_escape(rhs)))
	print('}')
	# import pdb; pdb.set_trace(); 0/0

def check_includes(pathname, autofix=False):
	exit_stat = 0
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
			exit_stat = 1
			parsed[1].remove('#include <%s>' % i)
		for i in sorted(n):
			print('  +', '#include <%s>' % i)
			exit_stat = 1
			parsed[1].append('#include <%s>' % i)
	for k in all_symbols:
		if 'std::' in k and k not in SYMBOL_TO_HEADER:
			print('  ?', k)
			exit_stat = 1
	parsed_n = (parsed[0], reorder_includes(pathname, parsed[1]), parsed[2])
	if parsed != parsed_n:
		if autofix:
			refresh_file(pathname, parsed_n)
		print('parsed != parsed_n:', pathname)
		exit_stat = 1
	return exit_stat

def main():
	exit_stat = 0
	parser = argparse.ArgumentParser()
	parser.add_argument('-f', '--auto-fix', action='store_true',
						help='automatically add include')
	parser.add_argument('-g', '--graphviz', action='store_true',
						help='draw include relationship in Graphviz')
	args = parser.parse_args()
	if args.graphviz:
		draw_includes(all_files())
	else:
		for pathname in all_files():
			if check_includes(pathname, autofix=args.auto_fix) != 0:
				exit_stat = 1
	return exit_stat

if __name__ == '__main__':
	exit(main())

