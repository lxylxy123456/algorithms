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

# Race condition cannot exist when executed with valgrind
VALGRIND := $(filter-out valgrind/RaceExampleTest,$(VALGRIND))

# VALGRIND_ALL has currently unavailable tests filtered out
VALGRIND_ALL := $(VALGRIND)
VALGRIND_ALL := $(filter-out valgrind/DynamicTableTest,$(VALGRIND_ALL))
VALGRIND_ALL := $(filter-out valgrind/FibTest,$(VALGRIND_ALL))
VALGRIND_ALL := $(filter-out valgrind/HireAssistantTest,$(VALGRIND_ALL))
VALGRIND_ALL := $(filter-out valgrind/IntervalTreeTest,$(VALGRIND_ALL))
VALGRIND_ALL := $(filter-out valgrind/MatVecTest,$(VALGRIND_ALL))
VALGRIND_ALL := $(filter-out valgrind/PSquareMatrixMultiplyTest,$(VALGRIND_ALL))
VALGRIND_ALL := $(filter-out valgrind/RabinKarpMatcherTest,$(VALGRIND_ALL))
VALGRIND_ALL := $(filter-out valgrind/RelabelToFrontTest,$(VALGRIND_ALL))

all: $(TARGETS)

test: $(TESTS)

valgrind: $(VALGRIND_ALL)

bin:
	mkdir bin

$(TARGETS): bin/%: src/%.cpp bin
	$(CXX) $(CXXFLAGS) -MMD -MF $(patsubst %,%.d,$@) -I include/ -o $@ $<

$(TESTS): test/%: bin/%
	./$^

$(VALGRIND): valgrind/%: bin/%
	# https://stackoverflow.com/a/55130152
	valgrind $(VALGRINDFLAGS) ./$^ > /dev/null
	echo valgrind ./$^ Completed

clean:
	rm -f $(TARGETS) $(DEPENDS) a.out

