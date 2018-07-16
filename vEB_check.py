import sys, random, pdb
from subprocess import Popen
from datetime import datetime, timedelta

name1 = 'vEB'
name2 = 'ProtovEB'

def generate_data() :
	d = set()
	ans = ''
	u = 65536
	for i in range(random.randint(50000, 60000)) :
		c = random.choice('m-+psid')
		if c == 'm' :
			ans += c + ' '
			if d and random.choice(range(2)) :
				ans += str(random.choice(list(d)))
			else :
				ans += str(random.randrange(u))
		elif c in '-+' :
			ans += c + ' '
		elif c in 'ps' :
			if not d :
				continue
			ans += c + ' '
			ans += str(random.choice(list(d)))
		elif c == 'i' :
			ans += c + ' '
			x = random.randrange(u)
			while x in d :
				x = random.randrange(u)
			ans += str(x)
			d.add(x)
		elif c == 'd' :
			if not d :
				continue
			ans += c + ' '
			x = random.choice(list(d))
			ans += str(x)
			d.remove(x)
		elif c == 'P' :
			ans += c + ' '
		ans += '\n'
	ans += 'q\n'
	return ans

def run(name, data) :
	p = Popen(['./' + name], stdin=-1, stdout=-1, stderr=-1)
	o, e = p.communicate(data.encode())
	assert not e
	return o.decode(); 

def tic() :
	global time
	time = datetime.now()

def toc() :
	global time
	return (datetime.now() - time).total_seconds()

if __name__ == '__main__' :
	Popen(['make', name1, name2]).communicate()
	n = int(sys.argv[1]) if len(sys.argv) > 1 else 128
	print('make complete')
	for i in range(n) :
		tic()
		data = generate_data()
		print('%.6f' % toc(), end='\t')
		tic()
		o1 = run(name1, data)
		print('%.6f' % toc(), end='\t')
		tic()
		o2 = run(name2, data)
		print('%.6f' % toc())
		if o1 != o2 :
			print('error')
			open('/tmp/i', 'w').write(data)
			open('/tmp/o1', 'w').write(o1)
			open('/tmp/o2', 'w').write(o2)
			pdb.set_trace()

