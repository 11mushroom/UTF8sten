CXX ?= g++
CXXFLAGS ?= -g -Wall
PREFIX ?= /usr
INSTDIR ?= $(PREFIX)/bin
srcdir = src

progfn := prog
progfile := $(progfn)

SRC := $(wildcard *.cpp)

OBJ = $(SRC:.cpp=.o)



.PHONY: clean install uninstall

all: $(progfile)
	@echo "========"
	@echo "| Done |"
	@echo "========"
	@echo ""
	@echo "now you can run"
	@echo "  make install"


$(progfile): prog.o UTF8.o
	$(CXX) $(CXXFLAGS) $^ -o $@

prog.o: prog.cpp UTF8.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

UTF8.o: UTF8.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@

install:
	cp $(progfile) $(INSTDIR)/

uninstall:
	rm $(INSTDIR)/$(progfn)

clean:
	rm $(wildcard *.o) $(progfile)
