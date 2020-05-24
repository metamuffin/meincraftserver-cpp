CFLAGS := -Wall -Wextra -Wpedantic -std=c99

BUILDDIR ?= $(shell pwd)/../../../build

debug : CFLAGS += -Og -g
release : CFLAGS += -Os

.PHONY: debug release

debug: packets.o
	mv *.o $(BUILDDIR)/

release: packets.o
	mv *.o $(BUILDDIR)/

packets.o: packets.c
	$(CC) $(CFLAGS) -c $< -o $@

