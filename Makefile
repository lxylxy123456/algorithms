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
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

CXXFLAGS=-Wall -Werror -g -std=c++11 -pthread
VALGRINDFLAGS=--error-exitcode=1 --tool=memcheck --leak-check=full \
				--errors-for-leak-kinds=definite

SOURCES := $(wildcard src/*.cpp)
TARGETS := $(patsubst src/%.cpp,bin/%,$(SOURCES))
DEPENDS := $(patsubst %,%.d,$(TARGETS))
-include $(DEPENDS)

TESTS := $(patsubst bin/%,test/%,$(filter %Test,$(TARGETS)))
VALGRIND := $(patsubst bin/%,valgrind/%,$(filter %Test,$(TARGETS)))

# Memory leak
VALGRIND := $(filter-out valgrind/FibHeapTest,$(VALGRIND))

# Invalid read of size 4
VALGRIND := $(filter-out valgrind/InsertSortTest,$(VALGRIND))

# ???
VALGRIND := $(filter-out valgrind/RabinKarpMatcherTest,$(VALGRIND))

all: $(TARGETS)

test: $(TESTS)

valgrind: $(VALGRIND)

bin:
	mkdir bin

$(TARGETS): bin/%: src/%.cpp bin
	$(CXX) $(CXXFLAGS) -MMD -MF $(patsubst %,%.d,$@) -I include/ -o $@ $<

$(TESTS): test/%: bin/%
	./$^

$(VALGRIND): valgrind/%: bin/%
	# https://stackoverflow.com/a/55130152
	valgrind $(VALGRINDFLAGS) ./$^ > /dev/null
	echo 'Completing' ./$^

clean:
	rm -f $(TARGETS) $(DEPENDS) a.out

