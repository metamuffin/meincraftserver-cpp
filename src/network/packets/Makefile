CXXFLAGS := -Wall -Wextra -Wpedantic -std=c99

BUILDDIR ?= $(shell pwd)/../../../build

debug : CXXFLAGS += -Og -g
release : CXXFLAGS += -Os

.PHONY: debug release

debug: packets.o
	mv *.o $(BUILDDIR)/

release: packets.o
	mv *.o $(BUILDDIR)/

packets.o: packets.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

