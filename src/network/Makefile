CXXFLAGS := -Wall -Wextra -Wpedantic -std=c99

INCLUDEDIRS := -I packets/
BUILDDIR ?= $(shell pwd)/../../build

debug : CXXFLAGS += -Og -g
release : CXXFLAGS += -Os

.PHONY: debug release

debug: evloop.o socket_setup.o
	$(MAKE) --directory=packets
	mv *.o $(BUILDDIR)/

release: evloop.o socket_setup.o
	$(MAKE) --directory=packets
	mv *.o $(BUILDDIR)/

evloop.o: evloop.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c $< -o $@

socket_setup.o: socket_setup.c
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c $< -o $@

