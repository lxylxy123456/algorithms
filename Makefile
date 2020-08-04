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

CXXFLAGS=-Wall -g -std=c++11 -pthread

SOURCES_OLD = $(wildcard *.cpp)
TARGETS_OLD = $(SOURCES_OLD:.cpp=)

SOURCES := $(wildcard src/*.cpp)
TARGETS := $(patsubst src/%.cpp,bin/%,$(SOURCES))
DEPENDS := $(patsubst %,%.d,$(TARGETS))
-include $(DEPENDS)

TESTS := $(patsubst bin/%,test/%,$(filter %Test,$(TARGETS)))

all:

ALL: $(TARGETS_OLD) $(TARGETS)

ALL_NEW: $(TARGETS)

test: $(TESTS)

$(TARGETS_OLD): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGETS): bin/%: src/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MF $(patsubst %,%.d,$@) -I include/ -I . -o $@ $<

$(TESTS): test/%: bin/%
	./$^

clean:
	rm -f $(TARGETS_OLD) $(TARGETS) $(DEPENDS) a.out

