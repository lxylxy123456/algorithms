import os, sys, re, itertools

def main(name):
	a = name + '.cpp'
	new_cpp = 'src/' + name + '.cpp'
	new_hpp = 'include/' + name + '.hpp'
	cnt = open(a).read().split('\n')
	b = cnt.index('#ifndef MAIN')
	assert cnt[b + 1] == '#define MAIN'
	assert cnt[b + 2] == '#define MAIN_' + name
	assert cnt[b + 3] == '#endif'
	assert cnt[b + 4] == ''
	assert cnt[b + 5] == '#ifndef FUNC_' + name
	assert cnt[b + 6] == '#define FUNC_' + name
	c = cnt.index('#ifdef MAIN_' + name)
	assert cnt[c - 2] == '#endif'
	assert cnt[-3] == '#endif'
	assert cnt[-2] == ''
	assert cnt[-1] == ''
	for index, i in enumerate(cnt):
		if i.startswith('#include') and i.endswith('.cpp"'):
			cnt[index] = i[:-5] + '.hpp"'
	d = list(itertools.compress(itertools.count(), map(lambda x: x.startswith('#include'), cnt)))
	d = sorted(set(d).intersection(range(b + 7, c - 2)))
	cpp = open(new_cpp, 'w')
	hpp = open(new_hpp, 'w')
	for i in cnt[:b]:
		print(i, file=cpp)
		print(i, file=hpp)
	print('#ifndef ALGORITHMS_%s' % (name.upper()), file=hpp)
	print('#define ALGORITHMS_%s' % (name.upper()), file=hpp)
	for i in range(b+7, c-2):
		print(cnt[i], file=hpp)
		if i == max(d) or (max(d) not in range(b + 7, c - 2) and i == b + 7) :
			print('', file=hpp)
			print('namespace algorithms {', file=hpp)
			print('', file=hpp)
	print('#include \"%s.hpp\"' % name, file=cpp)
	print('', file=cpp)
	for i in d:
		print(cnt[i], file=cpp)
	print('', file=cpp)
	print('using namespace algorithms;', file=cpp)
	print('', file=cpp)
	for i in cnt[c+1: -3]:
		print(i, file=cpp)
	print('', file=hpp)
	print('}', file=hpp)
	print('', file=hpp)
	print('#endif', file=hpp)

if __name__ == '__main__':
	for a in sys.argv[1:]:
		assert a.endswith('.cpp')
		name = a[:-4]
		main(name)

