#!/bin/bash
set -x
mkdir -p valgrind
for i in $(sed 's-valgrind/--' tmp); do
	echo valgrind --error-exitcode=1 --tool=memcheck --leak-check=full \
				--errors-for-leak-kinds=definite bin/$i
	echo $? > valgrind/$i
done

