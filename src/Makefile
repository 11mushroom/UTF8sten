CXX ?= g++
CXXFLAGS ?= -O3 -g -Wall
PREFIX ?= /usr
INSTDIR ?= $(PREFIX)/bin
srcdir = src

decoderfn := decoder
decoderfile := $(decoderfn)

progfiles := decoder encoder

encoderfn := encoder
encoderfile := $(encoderfn)

SRC := $(wildcard *.cpp)

OBJ = $(SRC:.cpp=.o)



.PHONY: clean install uninstall

all: $(progfiles)
	@echo "========"
	@echo "| Done |"
	@echo "========"
	@echo ""
	@echo "now you can run"
	@echo "  make install"


decoder: decoder.o UTF8.o
	$(CXX) $(CXXFLAGS) $^ -o $@

decoder.o: decoder.cpp UTF8.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

encoder: encoder.o UTF8.o
	$(CXX) $(CXXFLAGS) $^ -o $@

encoder.o: encoder.cpp UTF8.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

UTF8.o: UTF8.cpp UTF8.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

install:
	cp decoder $(INSTDIR)/$(decoderfn)
	cp encoder $(INSTDIR)/$(encoderfn)

uninstall:
	rm $(INSTDIR)/$(decoderfn) $(INSTDIR)/$(encoderfn)

clean:
	rm $(wildcard *.o) $(progfiles)
