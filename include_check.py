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
				assert 'std::max_element' in a
			elif j == 'cmath' :
				assert 'pow' in a
			elif j == 'iomanip' :
				assert 'std::left' in a
			elif j == 'exception' :
				assert 'std::invalid_argument' in a
			elif j == 'map' :
				assert 'std::map' in a or 'std::pair' in a
			elif j in ['list', 'set', 'unordered_set', 'unordered_map'] :
				assert 'std::' + j in a
			else :
				assert(False)
	except AssertionError :
		print('in:', i)
		print('include:', j)

